#ifndef _ROLE_H_
#define _ROLE_H_
#include "../common/head.h"
#include "../orm/role_info.h"
#include "../common/timer_manager.h"
#include "server_conns.h"

class game_role
{
    public:
        game_role()
        {
            _role_timer.set_owner(this);
            _role_timer.set_expired(ServerRun->get_run_ms()+10*1000);
        }

        void on_timeout(timer_manager*);
        void save_all();

        role_info& get_role_info_data()
        {
            return _role_info; 
        }

    private:
        role_info _role_info;
        template_timer<game_role,&game_role::on_timeout>  _role_timer;

};

#endif
