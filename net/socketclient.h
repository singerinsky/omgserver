/*
 * socketclient.h
 *
 *  Created on: 2014年1月24日
 *      Author: guanlei
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_
#include "IConnection.h"
#include <vector>
#include "../common/head.h"

namespace omg {

struct connection_id {
	int _fd;
	int _timestamp;

	bool operator!=(const connection_id& id) {
		return (id._fd != _fd || id._timestamp != _timestamp);
	}

	bool operator==(const connection_id& id) {
		return ((id._fd == _fd) && (id._timestamp == _timestamp));
	}
};

typedef enum {
	CONN_UNCONFIRM = 1, CONN_CONFIRM = 2, CONN_WAITDEL = 3
} CONN_STATE;

class socket_client: public io_handler {
public:
	socket_client();
	virtual ~socket_client();
	virtual int on_read();
	virtual int on_write();
	virtual int on_error();
	const connection_id& get_id() {
		return _conn_id;
	}
	CONN_STATE get_state() {
		return _conn_state;
	}

	int get_socket_fd() {
		return _socket_fd;
	}

    int check_msg_complete(char *data_head,int size);

    int send_packet_msg(packet* p);

private:
	std::vector<char> _recv_buffer;
	std::vector<char> _send_buffer;
	connection_id _conn_id;
	CONN_STATE _conn_state;
	MutexLock _lock;
	epoll_handler* _epoll_handler;
private:
	std::string _ip_str;
	int _epoll_mod;
	int _socket_fd;
	int _port;
	sockaddr_in _sin;
};

} /* namespace omg */

#endif /* SOCKETCLIENT_H_ */
