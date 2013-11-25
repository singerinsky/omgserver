/*
 * CGameMsgRecv.h
 *
 *  Created on: 2012-3-28
 *      Author: guanlei
 */

#ifndef CGAMEMSGRECV_H_
#define CGAMEMSGRECV_H_

#include "../common/IJob.h"
#include "../net/client_socket.h"
#include "GServer.h"
#include "CAllServerManage.h"

class CGameMsgRecv: public omg::IJob {
public:
	CGameMsgRecv(GServerInfo* con);
	virtual ~CGameMsgRecv();
	void	ExecuteJob();
private:
	GServerInfo* _game_server;
};

#endif /* CGAMEMSGRECV_H_ */
