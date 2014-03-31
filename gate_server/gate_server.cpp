#include "gate_server.h"

GateServerGlobal* GateServerGlobal::_instance;

bool GateServerGlobal::init(epoll_handler* handler)
{
    _handler = handler;
    TiXmlDocument doc("config/server.xml");
    bool loadFile = doc.LoadFile();
    if(loadFile == false){
        LOG(ERROR)<<"ERROR LOAD config file!!";
        exit(-1);
    }

    TiXmlNode* firstNode = doc.FirstChild("db_server");
    if(firstNode == NULL){
        LOG(ERROR)<<"ERROR LOAD config file!!";
        exit(-1);
    }
    TiXmlElement *ele = firstNode->ToElement();
    const char* ip_buffer = ele->Attribute("ip");
    StringBuffer s_port_buffer(ele->Attribute("s_port"));
    int s_port = atoi(s_port_buffer.c_str());
    LOG(INFO)<<"connect to dbserver "<<ip_buffer<<":"<<s_port;
    std::string ip(ip_buffer);
    db_conn = new db_connection(ip,s_port,_handler);
    int conn_rst = db_conn->connect();    
    if(conn_rst !=0)
    {
        db_conn->on_timeout(ServerRun->get_timer_mgr()); 
    }
    db_conn->send_register_message();

    return 1;
}
