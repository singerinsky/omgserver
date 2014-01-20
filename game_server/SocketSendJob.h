/*
 * SocketSendJob.h
 *
 *  Created on: 2012-7-14
 *      Author: guanlei
 */

#ifndef SOCKETSENDJOB_H_
#define SOCKETSENDJOB_H_

#include "msg.h"
#include "../common/IJob.h"

using namespace omg;

class SocketSendJob:public omg::IJob{

public:
	SocketSendJob(IConnection* pSocketClient){
		this->_client = pSocketClient;
	}


	virtual void ExecuteJob() {
		if (_client != NULL) {
			while (1) {
				MsgBase* msg = _send_queue.dequeue();
				if(msg == NULL){
					timespec ts;
					ts.tv_nsec = 20000000;
					ts.tv_sec = 0;
					nanosleep(&ts,NULL);
					continue;
				}
				int rst = _client->send_data((const char*) msg, msg->msg_size);

				if ((rst == -1)) {
					/*if (msg->msg_type == MSG_TYPE_GTODB_SERVER_MATCH_END) {
						MsgGameToDbServerMatchEnd *tmp_msg =
								(MsgGameToDbServerMatchEnd*) msg;

					}*/
					_send_queue.enqueue(msg);
					usleep(500000);
					continue;
				}/*else{
					if (msg->msg_type == MSG_TYPE_GTODB_SERVER_MATCH_END) {
											MsgGameToDbServerMatchEnd *tmp_msg =
													(MsgGameToDbServerMatchEnd*) msg;
										//	VLOG(0)<<"Success send"<<tmp_msg->mid<<""<<tmp_msg->msg_size<<":"<<rst;
					}else if(msg->msg_type == MSG_TYPE_GTODB_PLAYER_UPDATE){
						MsgGameToDbServerMatchEnd *tmp_msg =
													(MsgGameToDbServerMatchEnd*) msg;
					}
				}*/
				if (msg->msg_type == MSG_TYPE_GTODB_PLAYER_UPDATE) {
					MsgGameToDbServerPlayerUpdate* tmp_msg =
							(MsgGameToDbServerPlayerUpdate*) msg;
					delete tmp_msg;
					msg = NULL;
				} else if (msg->msg_type == MSG_TYPE_GTODB_SERVER_MATCH_END) {
					MsgGameToDbServerMatchEnd *tmp_msg =
							(MsgGameToDbServerMatchEnd*) msg;
					delete tmp_msg;
					msg = NULL;
				}else if(msg->msg_type == MSG_TYPE_GTODB_MATCH_EVENT_WB){
					MsgGameEventDBWB* tmp_msg = (MsgGameEventDBWB*)msg;
					delete tmp_msg;
					msg = NULL;
				}else if(msg->msg_type == MSG_TYPE_GTODB_START_ARENA){
					MsgMatchArenaStartArena* tmp_msg = (MsgMatchArenaStartArena*)msg;
					delete tmp_msg;
					tmp_msg = NULL;
				}
			}
		}
	}

	void add_msg_to_send_queue(MsgBase* msg){
		_send_queue.enqueue(msg);
	}


private:
	IConnection *_client;
	//omg::ConcurrenceQueue<MsgBase,MutexLock,MutexLock>	_send_queue;
	omg::WRQueue<MsgBase,MutexLock>	_send_queue;

};






#endif /* SOCKETSENDJOB_H_ */
