#ifndef _SS_SOCKET_AD_
#define _SS_SOCKET_AD_

#include "../common/IJob.h"
#include "../common/CThreadManage.h"
#include "../net/serversocket.h"
#include "CGameMsgRecv.h"
#include "GateGameMsg.h"

class SSocketListenAdapter: public omg::IJob{
public:
	SSocketListenAdapter(server_socket* socket,IMsgDispatcher* msg_dispatcher){
		this->_ssocket = socket;
		this->_msg_dispatcher = msg_dispatcher;
	}
	virtual ~SSocketListenAdapter(){}	

	void ExecuteJob(){
		VLOG(1)<<"Waiting for new accept.....";
		if(_ssocket == NULL){
			return;
		}else{
			GServerInfo* info = new GServerInfo();
			while(1){
				CSocketClient *client = _ssocket->startListening();
				info->_c_socket = client;
				client->set_msg_dispatcher(_msg_dispatcher);
				requir_connect_server_info(info);
				MsgServerReq msg;
				int rst = client->recvData((char*)&msg,msg.msg_size);
				LOG(INFO)<<"  "<<rst<<"  "<<msg._index;
				info->_c_socket = client;
				info->_index = msg._index;	
				CALLServerManage::GetInstance()->RegisterServer(msg._index,info);
				CGameMsgRecv* job =new CGameMsgRecv(info);
				omg::CThreadManage::AddJob(job);
			}
			LOG(INFO)<<" requir server info ....";
		}
	}	

protected:
	bool requir_connect_server_info(GServerInfo *pInfo);
	IMsgDispatcher*	_msg_dispatcher;
private:
	server_socket* _ssocket;

};

#endif
