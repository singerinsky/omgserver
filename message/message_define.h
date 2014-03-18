#ifndef _MESSAGE_DEFINE_
#define _MESSAGE_DEFINE_


#include "../net/packet.h"
#include "../net/game_packet.h"
#include "../net/message.pb.h"

enum
{
   CS_MSG_SOCCER_PLAYER_REQ = MSG_SOCCER_PLAYER_INFO << 2 |MSG_REQUEST, 
   CS_MSG_SOCCER_PLAYER_REP = MSG_SOCCER_PLAYER_INFO << 2 |MSG_RESPONSE,
};



typedef cs_packet<CS_MSG_SOCCER_PLAYER_REQ,SoccerPlayerInfoRequest> cs_soccer_player_request;
typedef cs_packet<CS_MSG_SOCCER_PLAYER_REP,SoccerPlayerInfoResponse> cs_soccer_player_response;


#endif
