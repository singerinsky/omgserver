#ifndef _CONNECTION_TO_GATE_JOB_H_
#define _CONNECTION_TO_GATE_JOB_H_

#include "../common/IJob.h"
#include "../net/client_socket.h"
#include "../net/IMsgDispatcher.h"
#include "msg.h"

class CConnectToGateJob: public omg::IJob{
public:
	CConnectToGateJob(const char* ip,int port,IMsgDispatcher* dispatcher){
		_msg_dispatcher = dispatcher;
		_gate_ip = ip;
		_gate_port = port;
		Init(ip,port);
	}

	CConnectToGateJob(CSocketClient* client,IMsgDispatcher* dispatcher){
		_msg_dispatcher = dispatcher;
		Init(client);
	}

	virtual ~CConnectToGateJob(){
		delete _client;
	}

public:
	void Init(const	char* ip,int port){
		_client = new CSocketClient(_gate_port,_gate_ip.c_str());
		bool rst = _client->connectToServer();	
		if(rst == true){
			_client->set_msg_dispatcher(_msg_dispatcher);
			LOG(INFO)<<"连接网关服务器成功!";
		}
	};

	void Init(CSocketClient*	client){
		_client = client;
		bool	rst = _client->connectToServer();
		if(rst == true){
			_client->set_msg_dispatcher(_msg_dispatcher);
			LOG(INFO)<<"连接网关服务器成功!";
		}else{
			LOG(ERROR)<<"连接网关服务器失败!";
		}
	}

	IConnection* GetConnectionToGateServer(){
		return _client;
	}

	int 	SendMsgToGateServer(MsgBase* pMsg){
		if(_client->connected()){
			return _client->sendData((const char*)pMsg,pMsg->msg_size);
		}
		return -1;
	}

	std::string GetConnectionIpPortStr(){
		return _client->get_socket_ip_port_info();
	}

	bool IsConnected(){
		return	_client->connected();
	}

public:
	virtual void ExecuteJob();
private:
	void RecvFromGateServer();
public:
	void SendToGateServer();

private:
	std::string _gate_ip;
	int			_gate_port;
	CSocketClient* _client;
	IMsgDispatcher* _msg_dispatcher;	
};

#endif
