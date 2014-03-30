#include "../common/server_application.h"
#include "server_conns.h"
using namespace omg;

class GateServerGloabl
{
    public:
        bool init();
        static GateServerGloabl* get_instance(){
            if(_instance == NULL)
            {
                _instance = new GateServerGloabl(); 
            }
            return _instance;
        }

    public:
        db_connection* db_conn;
    private:
        static GateServerGloabl* _instance;
        epoll_handler* _handler;
};

#define GlobalServer GateServerGlobal::get_instance()
