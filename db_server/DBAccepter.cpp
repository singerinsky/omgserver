/*
 * DBAccepter.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: guanlei
 */

#include "DBAccepter.h"

db_accepter::db_accepter() {
	// TODO Auto-generated constructor stub

}

db_accepter::~db_accepter() {
	// TODO Auto-generated destructor stub
}

int db_accepter::on_connection(int nfd,sockaddr* addr)
{
	LOG(INFO)<<"receive a new connection!";
	return 1;
}
