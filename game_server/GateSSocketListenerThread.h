#ifndef _SS_SOCKET_AD_
#define _SS_SOCKET_AD_

#include "../common/IJob.h"
#include "../common/CThreadManage.h"
#include "../net/serversocket.h"
#include "ConnectToGateJob.h"
#include "GateConManager.h"

class GateSSocketListenerThread: public omg::IJob{
public:
	GateSSocketListenerThread(int port,IMsgDispatcher* msg_dis){

		this->_ssocket = new server_socket();
		this->_ssocket->initSocket(port);
		_msg_dis = msg_dis;
	}
	virtual ~GateSSocketListenerThread(){}

	void ExecuteJob(){
		LOG(INFO)<<"Start Listening...";
		if(_ssocket == NULL){
			return;
		}else{
			while(1){
				CSocketClient *client = _ssocket->startListening();
				CConnectToGateJob* conn = new CConnectToGateJob(client,_msg_dis);
				std::string conn_info = client->get_socket_ip_port_info();
				GateConManager::GetInstance()->RegisterGateConnection(conn_info,conn);
				LOG(INFO)<<"网关服务器注册"<<conn_info;
			}
		}
	}	

private:
	server_socket* _ssocket;
	IMsgDispatcher*	_msg_dis;
};

#endif
