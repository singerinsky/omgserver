#ifndef _SOCKET_RECV_JOB_H_
#define _SOCKET_RECV_JOB_H_
#include "../common/IJob.h"
#include "msg.h"

extern int server_index;
class SocketRecvJob:public omg::IJob{

public:
	SocketRecvJob(CSocketClient* pSocketClient,IMsgDispatcher *msg_dis){
		this->_client = pSocketClient;
		_msg_dispatcher = msg_dis;
	}


	virtual void ExecuteJob()
	{
		if(_client != NULL){
				while(1){
					int	msg_size =_client->recvData();
					if(_client == NULL){
						VLOG(1)<<"error of connect ";
					}
					if(msg_size == 0){
						VLOG(1)<<"与数据服务器断开!";
						reconnect:
						usleep(500000);
						bool rst = _client->connectToServer();
						if(rst == false){
							goto reconnect;
						}else{
							VLOG(1)<<"重新连接数据服务器成功!";
							_client->set_msg_dispatcher(_msg_dispatcher);
							MsgServerRegister msg;
							msg._server_type = 2;
							msg._index = server_index;
							strncpy(msg._version,GAME_SERVER_VERSION,19);
							_client->sendData((const char*)&msg,sizeof(MsgServerRegister));
						}
					}else if(msg_size < 0){
						sleep(1);
						VLOG(1)<<"DATA ERROR FROM GATE SERVER";
					}
				}
			}
	}


private:
	CSocketClient *_client;
	IMsgDispatcher *_msg_dispatcher;

};




#endif
