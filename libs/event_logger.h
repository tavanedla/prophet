#ifndef EVENT_LOGGER_
#define EVENT_LOGGER_

#include <string>

#include "libs/logging.h"
#include "libs/services.grpc.pb.h"

namespace prophet {

class EventLogger {
    public:
        EventLogger(const std::filesystem::path& file_path) : log_(file_path) {}

        void Log(const Event& event) {
            log_.Append(CreateEventLog(event));
        }
    
    private:
        std::string CreateEventLog(const Event& event) {
            return "ip_address : " + event.ip_address() + " , user : " + event.user();
        }

        LogWriter log_;
};

}

#endif