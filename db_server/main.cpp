#include "../common/head.h"
#include "../common/omg_type.h"
#include "../common/system_util.h"
#include "../common/IJob.h"
#include "../net/epoll_handler.h"
#include "../net/serversocket.h"
#include "../net/client_socket.h"
#include "../common/CThreadManage.h"
#include "DBConnectionPool.h"
#include "CWorldEventHandler.h"
#include "DBAccepter.h"
#define my_debug

#define CONFIG_FILE "config/server.xml"
DEFINE_bool(daemon,false,"if start not as daemon");

DBServerInfo g_db_server_info;

void init_server_log(int argc, char** argv){
	
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if(loadFile == false){
		LOG(ERROR)<<"Loading file error ....";
		exit(1);
	}

	TiXmlNode* firstNode = doc.FirstChild("db_server");
	if(firstNode == NULL){
		LOG(ERROR)<<"ERROR OF XML FILE";
		exit(1);
	}

	TiXmlElement *ele = firstNode->ToElement();
	const char* log_info_dir = ele->Attribute("log_info_dir");
	const char* log_error_dir = ele->Attribute("log_error_dir");

	google::SetLogDestination(google::INFO,log_info_dir);
	google::SetLogDestination(google::ERROR,log_error_dir);
}



void load_db_config(){
	TiXmlDocument doc("config/server.xml");
	bool rst = doc.LoadFile();
	if(rst == false){
		VLOG(1)<<"Error of load database server file!!";
		exit(1);
	}

	TiXmlElement *ele = doc.FirstChild("database")->ToElement();
	if(ele != NULL){
		g_db_server_info.data_base_ip = ele->Attribute("data_base_ip");
		ele->QueryIntAttribute("mysql_port",&g_db_server_info.port);
		g_db_server_info.db_name = ele->Attribute("db");
		g_db_server_info.username = ele->Attribute("username");
		g_db_server_info.password = ele->Attribute("password");
		int port = 0;
		ele->QueryIntAttribute("mysql_port",&port);
		g_db_server_info.port =port;
	}
	
	ele = doc.FirstChild("db_server")->ToElement();
	if(ele != NULL){
		g_db_server_info.server_ip = ele->Attribute("ip");
		ele->QueryIntAttribute("s_port",&g_db_server_info.listening_port);
	}
}

int main(int argc,char** argv){

	init_server_log(argc,argv);
	if(FLAGS_daemon){
		init_daemon();
	}

	//载入数据库的连接信息
	load_db_config();

	//init db msg dispatcher
	CDBMsgDispatcher *msg_dispatcher = new CDBMsgDispatcher();

	msg_dispatcher->start(false);
	//初始化epoll_reactor_
	omg::epoll_handler *handler = new omg::epoll_handler();
	handler->init_epoll(EPOLL_SIZE,10,true);
    //初始化接收器
	db_accepter* accepter = new db_accepter(handler);
    accepter->init(g_db_server_info.server_ip.c_str(),g_db_server_info.listening_port);
	int rst = handler->add_event_handler(accepter->get_sock_fd(),accepter);
	handler->set_msg_dispatcher(msg_dispatcher);
	handler->start(false);

    pthread_t thread_id = handler->get_thread_id();

	//初始化数据库连接池,增加处理的线程队列
	omg::CThreadManage::BeginPoolThread(5,10);
	DBConnectionPool *conn= DBConnectionPool::GetInstance();
	for(int i=0;i<5;i++){
		CDBQueryhandlerJob* job = new CDBQueryhandlerJob(conn,msg_dispatcher,i+1);
		CDBTaskManage::GetInstance()->AddProcessThread(job);
		omg::CThreadManage::AddJob(job);
	}
	//开启线程池,启动轮训线程,读取世界的事件
	CWorldEventHandler *world_event = new CWorldEventHandler(conn,msg_dispatcher);
	omg::CThreadManage::AddJob(world_event);

    pthread_join(thread_id,NULL);
}
