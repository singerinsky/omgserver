#include "../common/head.h"
#include "../common/system_util.h"
#include "glog/logging.h"
#include "../net/msg.h"
#include "../net/epoll_handler.h"
#include "../common/CThreadManage.h"
#include "../net/serversocket.h"
#include "client_acceptor.h"


using namespace omg;
#define CONFIG_FILE "config/server.xml"

DEFINE_bool(daemon,true,"if start not as daemon");


//the gate server info,_port is the client connection port, the _s_port is the port of the server to server side
struct GateServerInfo{
	std::string _ip;
	int			_port;
	int			_s_port;
};

//local gate server info
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

omg::epoll_handler*  epoll_server_thread_start(){
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

	omg::epoll_handler *handler = new omg::epoll_handler();
	handler->init_epoll(EPOLL_SIZE,10,true);
   
    client_accepter *cp = new client_accepter(handler);
    cp->init(ip_buffer,port);
	int rst = handler->add_event_handler(cp->get_sock_fd(),cp);
	handler->start(false);
    pthread_join(handler->get_thread_id(),NULL);
	return handler;		
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
}


int main(int argc, char **argv){
	init_server_log(argc, argv);
	if(FLAGS_daemon){
		if(init_daemon() == -1){
			VLOG(0)<<"ERROR OF DAEMON";
		}
	}

	#ifdef _MY_DEBUG_
		load_tester_map();
		LOG(INFO)<<"Building in local....";
	#endif

	omg::CThreadManage::BeginPoolThread(4,10);

	omg::epoll_handler *handler = epoll_server_thread_start();
	if(handler == NULL){
		VLOG(1)<<"ERROR OF CREATE EPOLL";
		return -1;
	}
	return 1;
}
