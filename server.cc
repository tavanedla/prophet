#include <iostream>

#include <grpcpp/grpcpp.h>

#include "libs/services.grpc.pb.h"
#include "libs/suspicious_ips.h"
#include "libs/suspicious_users.h"
#include "libs/event_logger.h"
#include "libs/suspicious_events_reader.h"
#include "libs/event_processor.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace prophet;

class ProphetServiceImpl final : public prophet::ProphetService::Service {
  public:
    ProphetServiceImpl(EventProcessor* event_processor,
                       SuspiciousIps* bad_ips,
                       SuspiciousUsers* bad_users,
                       SuspiciousEventsReader* reader)
        : event_processor_(event_processor),
          bad_ips_(bad_ips),
          bad_users_(bad_users),
          reader_(reader) {}

    Status ProcessEvents(ServerContext* context, const ProcessEventsRequest* request,
                        ProcessEventsResponse* response) override {
      for (const auto& e : request->events()) {
        event_processor_->Process(e);
      }
      return Status::OK;
    }

    Status BlockIpRange(ServerContext* context, const BlockIpRangeRequest* request,
                        BlockIpRangeResponse* response) {
      std::cout << "Received block request : " << request->ip_range() << std::endl;
      bad_ips_->AddSuspiciousBlock(request->ip_range());
      return Status::OK;
    }

    Status UnblockIpRange(ServerContext* context, const UnblockIpRangeRequest* request,
                          UnblockIpRangeResponse* response) {
      std::cout << "Received unblock request : " << request->ip_range() << std::endl;
      bad_ips_->RemoveSuspiciousBlock(request->ip_range());
      return Status::OK;
    }

    Status GetSuspiciousEvents(ServerContext* context, const GetSuspiciousEventsRequest* request,
                              GetSuspiciousEventsResponse* response) {
      std::cout << "Received read request\n";
      auto events = reader_->Read(request->number_of_events());
      for (const auto& e : events) {
        *(response->add_suspicious_events()) = e;
      }
      return Status::OK;
    }

  private:
    EventProcessor* event_processor_;
    SuspiciousIps* bad_ips_;
    SuspiciousUsers* bad_users_;
    SuspiciousEventsReader* reader_;
};

void RunServer() {
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;

  std::filesystem::path data_dir("data_dir/");
  std::cout << "Building ips\n";
  SuspiciousIps bad_ips(data_dir);
  
  std::cout << "Building users\n";
  SuspiciousUsers bad_users(data_dir);

  std::cout << "Building reader\n";
  SuspiciousEventsReader reader(data_dir / "bad_events.txt");
  
  std::cout << "Building logger\n";
  EventLogger logger(data_dir / "bad_events.txt");

  std::cout << "Building processor\n";
  EventProcessor processor(&logger, &bad_ips, &bad_users);

  ProphetServiceImpl service(&processor, &bad_ips, &bad_users, &reader);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}