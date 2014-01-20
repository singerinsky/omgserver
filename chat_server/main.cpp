#include "../common/head.h"
#include "../common/daemon.h"
#include "glog/logging.h"
#include "../net/msg.h"
#include "../net/epoll_handler.h"
#include "../net/CSocketMap.h"
#include "../common/CThreadManage.h"
#include "../net/serversocket.h"
#include "CChatMsgDispatcher.h"

DEFINE_bool(daemon,true,"if start not as daemon");


#define CONFIG_FILE "chat_server.xml"

void init_server_log(int argc, char** argv){
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
}

omg::epoll_handler*  epoll_server_thread_start(void* param){
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if(loadFile == false){
		VLOG(1)<<"ERROR LOAD config file!!";
		return NULL;
	}

	TiXmlNode* firstNode = doc.FirstChild("chat_server");
	if(firstNode == NULL){
		VLOG(1)<<"error of xml file";
		exit(1);
	}
	TiXmlElement *ele = firstNode->ToElement();
	const char* ip_buffer = ele->Attribute("ip");
	StringBuffer port_buffer(ele->Attribute("port"));
	int port = atoi(port_buffer.c_str());

	omg::epoll_handler *handler = new omg::epoll_handler();
	handler->init_epoll(EPOLL_SIZE,ip_buffer,port);
	handler->startListening();
	handler->set_msg_dispatcher((CChatMsgDispatcher*)param);
	handler->start(false);
	return handler;		
}

void create_chat_world_by_config(){
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if(loadFile == false){
		VLOG(1)<<"error of load file";
		exit(1);
	}	

	TiXmlElement* root = doc.FirstChildElement("chat_world_list");
	if(!root){
		LOG(ERROR)<<"Error of xml";
		exit(1);
	}
	
	TiXmlNode* world_node = NULL;	
	for(world_node = root->FirstChild("chat_world");world_node != NULL;world_node = root->IterateChildren(world_node)) {
		TiXmlElement *ele = world_node->ToElement();
		StringBuffer id_buffer(ele->Attribute("id"));
		int world_id = atoi(id_buffer.c_str());
		LOG(INFO)<<"World "<<world_id<<" will be created";
	}



}





int main(int argc, char **argv){
	init_server_log(argc, argv);
	if(FLAGS_daemon){
		if(init_daemon() == -1){
			VLOG(0)<<"ERROR OF DAEMON";
		}
	}

	create_chat_world_by_config();

	omg::CThreadManage::BeginPoolThread(4,10);

	CChatMsgDispatcher	*msg_dispatcher = new CChatMsgDispatcher();
	
	msg_dispatcher->start(false);

	omg::epoll_handler *handler = epoll_server_thread_start(msg_dispatcher);
	if(handler == NULL){
		VLOG(1)<<"ERROR OF CREATE EPOLL";
		return -1;
	}
	handler->join();
	return 1;
}
