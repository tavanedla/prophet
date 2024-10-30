#ifndef EVENT_PROCESSOR_
#define EVENT_PROCESSOR_

#include <memory>
#include <string>
#include <vector>

#include "libs/suspicious_ips.h"
#include "libs/suspicious_users.h"
#include "libs/event_logger.h"

#include "libs/services.grpc.pb.h"

namespace prophet {

class EventProcessor {
    public:
        EventProcessor(
            EventLogger* logger, 
            SuspiciousIps* bad_ips, 
            SuspiciousUsers* bad_users);

        void Process(const Event& event);
    
    private:
        EventLogger* event_logger_;
        SuspiciousIps* bad_ips_;
        SuspiciousUsers* bad_users_;
};

}

#endif