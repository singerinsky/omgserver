/*
 * DBAccepter.h
 *
 *  Created on: 2014年1月20日
 *      Author: guanlei
 */

#ifndef DBACCEPTER_H_
#define DBACCEPTER_H_

#include "../common/head.h"
#include "../net/epoll_accepter.h"
#include "../net/epoll_handler.h"
#include "../net/IMsgDispatcher.h"

using namespace omg;

class db_accepter: public epoll_accepter {
public:
	db_accepter(omg::epoll_handler* handler,IMsgDispatcher* dispathcer):epoll_accepter(handler,dispathcer)
    {
    }
	virtual ~db_accepter();

public:
	virtual int on_connection(int nfd,sockaddr* addr);
    virtual int on_error(){
        return 1;
    }
};

#endif /* DBACCEPTER_H_ */
