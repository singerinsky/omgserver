#include "role.h"

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

}
