#ifndef _SERVER_APPLICATION_ 
#define _SERVER_APPLICATION_
#include "time_util.h"
#include "timer_manager.h"
#include <string>
#include "../net/IMsgDispatcher.h"

using namespace omg;
namespace omg{
    class server_application
    {
        public:
            server_application()
            {
                _tick_ms = get_tsc_us()/1000; 
                _timer_mgr.init(get_run_ms(),14);
            }

            int64_t get_run_ms()
            {
                return rdtsc()/_tick_ms;
            }

            timer_manager* get_timer_mgr()
            {
                return &_timer_mgr; 
            }

            static server_application* get_instance()
            {
                if(application == NULL)
                {
                    application = new server_application();
                }
                return application; 
            }

            IMsgDispatcher* get_msg_dispatcher()
            {
                return _msg_dispatcher;
            }
        private:
            int64_t _tick_ms;
            std::string _server_name;
            static server_application* application;
            timer_manager _timer_mgr;
            IMsgDispatcher* _msg_dispatcher;
    };

    #define ServerRun   server_application::get_instance()
}
#endif
