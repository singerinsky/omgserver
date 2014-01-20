#include "SSocketListenAdapter.h"
#include "GateGameMsg.h"


bool SSocketListenAdapter::requir_connect_server_info(GServerInfo *pInfo){
	if(pInfo != NULL){
		MsgServerReq msg;
		CSocketClient *socket = pInfo->_c_socket;
		if(socket != NULL){
			if( -1 == socket->send_data((const char*)&msg,msg.msg_size)){
				return false;
			}
		}

	}

	return false;
}
