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
void send_client_login_message(int fd);


int main(int argc,char** argv){
	init_server_log(argc,argv);
	
//	omg::CThreadManage::BeginPoolThread(1);
	int port = 1;
	struct sockaddr_in addr;
	socklen_t len;
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family =	AF_INET;
	addr.sin_port = htons(19999);	
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
            if(is_login == false)
            send_client_login_message(fd);
            is_login =true; 
//            send_soccer_player_info(fd);
			char buffer[1024];
			usleep(500000);
			int recv_size = recv(fd,buffer,1024,0);
            VLOG(1)<<"receive server message for "<<recv_size;
		}
	}else{
		VLOG(1)<<"error connect";
	}
	pthread_exit(NULL);	
	return 1;
}

void send_packet_msg(int fd,packet* info)
{
    char buff[1024];
    int final_size = info->encode(buff,1024); 
    int send_size = send(fd,buff,final_size,0);
    VLOG(2)<<"send data size"<<send_size;
}

void send_soccer_player_info(int fd)
{
    cs_soccer_player_request request;
    request.body.set_player_id(1);
    int size = request.encode_size();
    char* data_buff = new char[size];
    int final_size = request.encode(data_buff,size);
    if(final_size == - 1)VLOG(1)<<"error of encode ";
    int send_size = send(fd,data_buff,final_size,0);
    VLOG(1)<<"send soccer player inf";
}

void send_client_login_message(int fd)
{
    cs_client_login_request request;
    request.body.set_player_id(11);
    request.body.set_player_pwd("nice_body");
    request.body.set_md5_code("md5code");
    send_packet_msg(fd,&request);
    VLOG(1)<<"send client login info";
}



