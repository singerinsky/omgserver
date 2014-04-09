#ifndef _ROLE_H_
#define _ROLE_H_

#include "../orm/role_info.h"
#include "../common/timer_manager.h"

class role
{
    public:
        role()
        {

        }

        void on_timeout(timer_manager*);

    private:
        role_info _role_info;
        template_timer<role,&role::on_timeout>  _role_timer;

};

#endif
