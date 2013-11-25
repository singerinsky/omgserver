/*
 * CGameMsgRecv.cpp
 *
 *  Created on: 2012-3-28
 *      Author: guanlei
 */

#include "CGameMsgRecv.h"

CGameMsgRecv::CGameMsgRecv(GServerInfo* gs) {
	// TODO Auto-generated constructor stub
	_game_server = gs;
}

CGameMsgRecv::~CGameMsgRecv() {
	// TODO Auto-generated destructor stub
}

void CGameMsgRecv::ExecuteJob(){
	CSocketClient* client = _game_server->_c_socket;
	while(1){
		int rst = client->recvData();
		if(rst == 0){
			LOG(ERROR)<<"LOST CONNECTION OF GAME SERVER "<<_game_server->_index;
			CALLServerManage::GetInstance()->UnRegisterServer(_game_server->_index);
			break;
		}
	}
}
