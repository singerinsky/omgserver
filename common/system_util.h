#ifndef _DAEMON_H_
#define _DAEMON_H_
#include "head.h"

int init_daemon(void);

#define MAIN_FUNCTION int main(int argc,char** argv){\
	init_server_log(argc,argv);\
	if(FLAGS_daemon){\
		init_daemon();\
	}\



#endif
