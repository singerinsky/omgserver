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
            _role_timer.set_expired(ServerRun->get_run_ms()+5000);
            _timer_mgr = ServerRun->get_timer_mgr();
            _timer_mgr->add_timer(&_role_timer);
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
        timer_manager* _timer_mgr;

};

class role_manager
{
    public:
        game_role* get_role(int role_id)
        {
            ROLE_ITR itr = _role_map.find(role_id); 
            if(itr == _role_map.end())
            {
                return NULL; 
            }
            return itr->second;
        }

        void  remove_role(int role_id)
        {
            ROLE_ITR itr = _role_map.find(role_id); 
            if(itr == _role_map.end())
            {
                return ; 
            }
            delete itr->second;
            _role_map.erase(itr);
        }

        int   add_role(game_role* role,int role_id)
        {
            game_role* role_old = get_role(role_id); 
            if(role_old != NULL)
            {
                return -1; 
            }
            _role_map[role_id] = role;
            return 1;
        }

        static role_manager* get_instance()
        {
            if(_instance == NULL)
            {
                _instance = new role_manager; 
            }
            return _instance;
        }
    private:
        typedef std::map<int,game_role*> ROLE_MAP;
        typedef std::map<int,game_role*>::iterator ROLE_ITR;
        ROLE_MAP _role_map;
        static role_manager* _instance;
};
#endif
