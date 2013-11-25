#ifndef _CONNECTION_TO_DB_JOB_H_
#define _CONNECTION_TO_DB_JOB_H_

#include "../common/IJob.h"
#include "../common/lock.h"
#include "../common/queue.h"
#include "../net/client_socket.h"
#include "SocketRecvJob.h"
#include "SocketSendJob.h"
#include "../common/CThreadManage.h"
#include "msg.h"

using namespace omg;

extern int server_index;
class CConnectToDB {
public:
	CConnectToDB(const char* ip, int port, IMsgDispatcher* handler) {
		_msg_dispatcher = handler;
		_db_ip = ip;
		_db_port = port;
		Init();
	}
	virtual ~CConnectToDB() {
		delete _client;
	}

public:
	void Init() {
		_client = new CSocketClient(_db_port, _db_ip.c_str());
		bool rst = _client->connectToServer();
		if (rst == true) {
			_client->set_block(true);
			_client->set_connection(true);
			_client->set_msg_dispatcher(_msg_dispatcher);
			VLOG(1)<<"连接数据服务器"<<_db_ip.c_str()<<"成功！";
			_recv_job = new SocketRecvJob(_client,_msg_dispatcher);
			omg::CThreadManage::AddJob(_recv_job);
			_send_job = new SocketSendJob(_client);
			omg::CThreadManage::AddJob(_send_job);
			RegisterDBserver();
		} else {
			VLOG(1)<<"连接数据服务器"<<_db_ip.c_str()<<"失败！";
		}
	}

private:
	void RecvFromDBServer() {

	}

	//register db server
	void RegisterDBserver() {
		MsgServerRegister msg;
		msg._server_type = 2;
		msg._index = server_index;
		strncpy(msg._version,GAME_SERVER_VERSION,19);
		_client->sendData((const char*)&msg,sizeof(msg));
	}
public:
	void SendToDBServer();
	IConnection* GetConnectionToDB() {
		return _client;
	}
	void SendMsg(MsgBase* msg_base) {
		if(msg_base != NULL) {
			_send_job->add_msg_to_send_queue(msg_base);
		}
	}

private:
	std::string _db_ip;
	int _db_port;
	SocketRecvJob* _recv_job;
	SocketSendJob* _send_job;
	CSocketClient* _client;
	IMsgDispatcher* _msg_dispatcher;
};

#endif
