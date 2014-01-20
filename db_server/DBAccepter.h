/*
 * DBAccepter.h
 *
 *  Created on: 2014年1月20日
 *      Author: guanlei
 */

#ifndef DBACCEPTER_H_
#define DBACCEPTER_H_
#include "../common/head.h"

class db_accepter: public epoll_accepter {
public:
	db_accepter();
	virtual ~db_accepter();

public:
	virtual int on_connection(int nfd,sockaddr* addr);
};

#endif /* DBACCEPTER_H_ */
