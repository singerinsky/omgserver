#include "../common/head.h"
#include "../common/daemon.h"
#include "glog/logging.h"
#include "../net/msg.h"
#include "../net/epoll_handler.h"
#include "../common/CThreadManage.h"
#include "../net/serversocket.h"
#include "GServer.h"
#include "SSocketListenAdapter.h"
#include "CMsgDispatcher.h"
#include "CGateTimerEventHandler.h"

#define CONFIG_FILE "config/server.xml"

DEFINE_bool(daemon,true,"if start not as daemon");
/*
using google::dense_hash_map;

void test_map(){
	dense_hash_map<int,int> test;
	test.set_empty_key(-1);
	std::map<int,int> map_test;
	VLOG(1)<<"INT";
	for(int i=0;i<100000;i++){
		//test[i] = rand();
		map_test[i] = rand();
	}
	VLOG(1)<<"START";	
	test.find(788);	
	VLOG(1)<<"END";
	map_test.find(788);
	VLOG(1)<<"END";
}
*/

//the gate server info,_port is the client connection port, the _s_port is the port of the server to server side
struct GateServerInfo{
	std::string _ip;
	int			_port;
	int			_s_port;
};

//local gate server info
GateServerInfo	g_gate_server_info;
CMsgDispatcher	*g_msg_dispatcher;
char* public_key;
const char* gm_login_public_key = "guanlei";

void init_server_log(int argc, char** argv){
	
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if(loadFile == false){
		LOG(ERROR)<<"Loading file error ....";
		exit(1);
	}

	TiXmlNode* firstNode = doc.FirstChild("gate_server");
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

omg::Epollhandler*  epoll_server_thread_start(void* param){
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if(loadFile == false){
		VLOG(1)<<"ERROR LOAD config file!!";
		return NULL;
	}

	TiXmlNode* firstNode = doc.FirstChild("gate_server");
	if(firstNode == NULL){
		VLOG(1)<<"error of xml file";
		exit(1);
	}
	TiXmlElement *ele = firstNode->ToElement();
	const char* ip_buffer = ele->Attribute("ip");
	StringBuffer port_buffer(ele->Attribute("port"));
	StringBuffer s_port_buffer(ele->Attribute("s_port"));
	int port = atoi(port_buffer.c_str());
	int s_port = atoi(s_port_buffer.c_str());
	g_gate_server_info._ip = ip_buffer;
	g_gate_server_info._port = port;
	g_gate_server_info._s_port = s_port;


	omg::Epollhandler *handler = new omg::Epollhandler();
	handler->set_msg_dispatcher((CMsgDispatcher*)param);
	handler->init_epoll(EPOLL_SIZE,ip_buffer,port);
	handler->startListening();
	handler->start(false);
	//handler->join();
	return handler;		
}

//start to listening game server to connection 
void server_to_server_start(){
	server_socket *socket = new server_socket();
	socket->initSocket(g_gate_server_info._s_port);
	SSocketListenAdapter *ss = new SSocketListenAdapter(socket,g_msg_dispatcher);
	omg::CThreadManage::AddJob(ss);
}

CMsgDispatcher* msg_dispatcher_thread_start(){
	CMsgDispatcher	*msg_dispatcher = CMsgDispatcher::GetInstance();
	msg_dispatcher->start(false);
	return msg_dispatcher;
}

void msg_recv_thread_start(){
	//CGameRec* rec = new CGameRec();
	//rec->start(false);
}

std::map<std::string,std::string> g_test_player_map;

void load_gameserver_info(){
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if (loadFile == false) {
		LOG(ERROR) << "Loading file error ....";
		exit(1);
	}

	TiXmlNode* firstNode = doc.FirstChild("gate_server");
	if (firstNode == NULL) {
		LOG(ERROR) << "ERROR OF XML FILE";
		exit(1);
	}

	TiXmlElement *ele = firstNode->ToElement();
	public_key = new char[20];
	strcpy(public_key,ele->Attribute("public_key"));
	VLOG(0)<<"Public key"<<public_key;
}
void load_tester_map() {
	TiXmlDocument doc("config_file/tester_map.xml");
	bool loadFile = doc.LoadFile();
	if (loadFile == false) {
		LOG(ERROR)<<"ERROR LOAD config file!!";
		return;
	}

	TiXmlElement* root = doc.FirstChildElement("all");
	if(root != NULL) {
		TiXmlNode* tester = NULL;
		for(tester=root->FirstChild("tester");tester!= NULL;tester=root->IterateChildren(tester)) {
				TiXmlElement* tester_element = tester->ToElement();
				int flag = 0;
				tester_element->QueryIntAttribute("flag",&flag);
				if(flag == 0){
					continue;
				}

				std::string ip;
				ip = tester_element->Attribute("ip");
				std::string name;
				name = tester_element->Attribute("name");
				LOG(INFO)<<"player name"<<ip.c_str()<<":"<<name.c_str();
				g_test_player_map[ip]=name;
			}

		}
	LOG(INFO)<<"SSSSSSSS";
}


int main(int argc, char **argv){
	init_server_log(argc, argv);
	load_gameserver_info();
	if(FLAGS_daemon){
		if(init_daemon() == -1){
			VLOG(0)<<"ERROR OF DAEMON";
		}
	}
	#ifdef _QQ_PLATM_
		VLOG(0)<<"Building in qq platrom....";
	#endif

	#ifdef _MY_DEBUG_
		load_tester_map();
		LOG(INFO)<<"Building in local....";
	#endif

	signal(SIGPIPE,SIG_IGN);
	omg::CThreadManage::BeginPoolThread(4,10);

	CMsgDispatcher* dispatcher = msg_dispatcher_thread_start();
	g_msg_dispatcher = dispatcher;	
	//event thread
	CGateTimerEventHandler *timer_thread = new CGateTimerEventHandler(dispatcher,10);
	omg::CThreadManage::AddJob(timer_thread);
	dispatcher->set_timer_hander(timer_thread);
	//timer_thread->add_arena_event();
//	msg_recv_thread_start();	
	omg::Epollhandler *handler = epoll_server_thread_start(dispatcher);
	if(handler == NULL){
		VLOG(1)<<"ERROR OF CREATE EPOLL";
		return -1;
	}
	//start to server connect
	server_to_server_start();
//	handler->join();
	sleep(3600*24*365);
	return 1;
}
