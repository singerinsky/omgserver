#include "role.h"
#include "gate_server.h"

role_manager* role_manager::_instance;
void game_role::on_timeout(timer_manager* mgr)
{
    LOG(INFO)<<"on time out...";
    _role_timer.set_expired(ServerRun->get_run_ms() + 1000);
    _timer_mgr->add_timer(&_role_timer);
    save_all();
}

void game_role::save_all()
{
    if(_db_conn->is_connected())
    {
        _db_conn->do_data_update(&_role_info,_role_info.get_role_id());
    }
    else
    {
        LOG(ERROR)<<"DB CONNECTION IS NOT CONNECTED"; 
    }
}
