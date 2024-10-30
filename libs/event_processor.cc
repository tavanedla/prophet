#include "event_processor.h"

namespace prophet {

EventProcessor::EventProcessor(
    EventLogger* logger, 
    SuspiciousIps* bad_ips, 
    SuspiciousUsers* bad_users)
    : event_logger_(logger),
      bad_ips_(bad_ips),
      bad_users_(bad_users) {}

void EventProcessor::Process(const Event& event) {
    bool bad_user = bad_users_->Contains(event.user());
    bool bad_ip = bad_ips_->Contains(event.ip_address());

    if (bad_user || bad_ip) {
        event_logger_->Log(event);
    }

    if (bad_ip && !bad_user) {
        bad_users_->Add(event.user());
    }

    if (bad_user && !bad_ip) {
        bad_ips_->AddBadIp(event.ip_address());
    }
}

}