/*
 * CChannel.h
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#ifndef CCHANNEL_H_
#define CCHANNEL_H_

#include "IChannel.h"

class CChannel:public IChannel {
	public:
		CChannel(CHANNEL_ID);
		virtual ~CChannel();
		//添加新的用户到聊天室
		virtual void	AddChater(IChater*);
		//根据用户移除用户到聊天室
		virtual void	RemoveChaterById(CHATER_ID);
		virtual void	RemoveChater(IChater*);
		//发送消息到所有的用户
		virtual void	SendAllMessage(Message*);
		//获取所有的用户的数量
		virtual int		GetChaterNumberInChannel();
		CHANNEL_ID		GetChannelId(){
			return this->_channel_id;
		};

	private:
		typedef std::map<CHATER_ID,IChater*> 			CHATER_MAP;
		typedef std::map<CHATER_ID,IChater*>::iterator 	CHATER_MAP_ITER;
		//频道的玩家表
		CHATER_MAP 									_chater_map;


		typedef std::list<Message*>					MESSAGE_LIST;
		typedef std::list<Message*>::iterator		MESSAGE_ITR;
		//频道的最近消息
		MESSAGE_LIST								_top_message_list;

		//频道的ID
		CHANNEL_ID									_channel_id;


};

#endif /* CCHANNEL_H_ */
