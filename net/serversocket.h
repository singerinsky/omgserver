/*
 * serversocket.h
 *
 *  Created on: 2012-2-7
 *      Author: gl
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "../common/head.h"
#include "../net/client_socket.h"



class server_socket {
public:
	server_socket();
	virtual ~server_socket();

public:
	bool initSocket(int port);
	CSocketClient* startListening();

private:
	int _fd;
};

#endif /* SERVERSOCKET_H_ */
