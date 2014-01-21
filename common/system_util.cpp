#include "system_util.h"

int init_daemon(void)
{
    pid_t pid;
    /* parent exits , child continues */
    if((pid = fork()) < 0)
        return -1;
    else if(pid != 0)
        exit(0);

    setsid(); /* become session leader */
    // Ensure future opens won't allocate controlling TTYs
    struct sigaction sa ;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN; 
    sigemptyset(&sa.sa_mask); 
    if (sigaction(SIGHUP, &sa, NULL) < 0) return -1 ;

    if( (pid = fork() ) < 0 ) return -1 ;
    else if(pid != 0 )  _exit(0) ;

//    if((chdir("/")!=0) ) return -1 ;


    return 0;
}

void do_wait_ms(int ms)
{
    if(ms <= 0 )return;
  	timespec ts;
    ts.tv_nsec = (ms%1000)*1000000;
	ts.tv_sec = ms/1000;
        
    pselect(0,NULL,NULL,NULL,&ts,NULL);
}

