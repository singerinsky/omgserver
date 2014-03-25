#include "../common/head.h"
#include "../net/msg.h"
#include <sys/socket.h>
#include <sys/types.h>
#include "stdio.h"
#include "string.h"

#include "string.h"
#include "../net/msg.h"
#include "../net/client_socket.h"
#include "TestJob.h"
#include "../common/CThreadManage.h"
#include "../message/message_define.h"

void init_server_log(int argc, char** argv){
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
}

void send_soccer_player_info(int fd);


int main(int argc,char** argv){
	init_server_log(argc,argv);
	
//	omg::CThreadManage::BeginPoolThread(1);
	int port = 1;
	struct sockaddr_in addr;
	socklen_t len;
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family =	AF_INET;
	addr.sin_port = htons(29999);	
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
//	TestJob *pjob = new TestJob();
//	omg::CThreadManage::AddJob(pjob);
	
//	omg::CThreadManage::AddJob(pjob);
	int fd = socket(AF_INET,SOCK_STREAM,0);

	int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);
	VLOG(1)<<"ssss";
	if(fd != -1){
		int rest = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
		printf("%d",rest);
		bool is_login = false;
		while(1){
			struct MsgLogin msg_login;
			msg_login.mid = 10;
			msg_login.uid = 1;
            msg_login.zeit = time(NULL);
			if(is_login == false){
				///send(fd,(const char*)&msg_login,msg_login.msg_size,0);
				is_login = true;
			}
            send_soccer_player_info(fd);
			struct MsgAlive msg_live;
			int msg_len = sizeof(MsgAlive);
			char* buff = (char*)malloc(msg_len);
			int i=0;
			msg_live.player_id = 111;
            msg_live.zeit = time(NULL);
			memcpy(buff,&msg_live,msg_len);
			VLOG(1)<<"SEND MSG...";
		//snprintf(buff,sizeof(buff),"send message%d",i);
//			int len = send(fd,buff,msg_len,0);
			VLOG(1)<<"SEND MSG";
			char buffer[1024];
			usleep(10000*500);
			recv(fd,buffer,1024,0);
			VLOG(1)<<"Server time is "<<((MsgAlive*)buffer)->zeit;
		}
	}else{
		VLOG(1)<<"error connect";
	}
	pthread_exit(NULL);	
	return 1;
}

void send_soccer_player_info(int fd)
{
    cs_soccer_player_request request;
    request.body.set_player_id(1);
    int size = request.encode_size();
    VLOG(1)<<"ENCODE SIZE "<<size;
    char* data_buff = new char[size];
    int final_size = request.encode(data_buff,size);
    if(final_size == - 1)VLOG(1)<<"error of encode ";
    VLOG(1)<<"FINAL ENCODE SIZE"<<final_size;
    int send_size = send(fd,data_buff,final_size,0);

    VLOG(1)<<"SEND SIZE "<<send_size;



}





