#include "../common/head.h"
#include "../common/omg_type.h"
#include "../common/daemon.h"
#include "../net/serversocket.h"
#include "../net/client_socket.h"
#include "../common/CThreadManage.h"
#include "./FlexSecurityBox.h"


DEFINE_int32(index,0,"server index");

struct SERVER_INFO{
	std::string ip;
	int port;
};

bool load_config(SERVER_INFO &info){
	TiXmlDocument doc("./server.xml"); 
	bool rst = doc.LoadFile();
	if(!rst){
		VLOG(1)<<"Load server config failed..";
		return false;
	}

	TiXmlElement* ele = doc.FirstChildElement("sercurity_server");
	if(ele != NULL){
		info.ip = ele->Attribute("ip");	
		info.port = atoi(ele->Attribute("port"));
		return true;
	}else{
		return false;
	}
	
}



//初始化日志系统
void init_server_log(int argc, char** argv){
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	google::SetStderrLogging(google::INFO);
	google::LogToStderr();
}

SERVER_INFO g_server_info;
int main(int argc,char** argv){
	//begin pool threadpool

	init_server_log(argc, argv);
	if(init_daemon() == -1)	{
	   VLOG(2)<<"error of init daemon...";
	   return -1;
	}
	bool rst = load_config(g_server_info);
	if(!rst){
		exit(1);
	}

	load_config(g_server_info);
	LOG(INFO)<<"Server Start listening in"<<g_server_info.ip.c_str()<<":"<<g_server_info.port;
 	FlexSecurityBox flexsecuritybox(g_server_info.ip.c_str(),g_server_info.port);
          if (!flexsecuritybox.Open() )
          {
                LOG(INFO)<<"Init secuerty server ......";  
		exit(-1);
          }
          else
        flexsecuritybox.DoWork();
}
