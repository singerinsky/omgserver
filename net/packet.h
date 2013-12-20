#ifndef _PACKET_MSG_H_
#define _PACKET_MSG_H_

#include "game_packet.h"
#include "../message/message.pb.h"

#pragma pack(1)

#define MSG_REQUEST 1;
#define MSG_REPONSE 2; 

enum
{
    CS_MSG_GET_PLAYER_INFO_REQ = SoccerPlayerInfo<<2 | MSG_REQUEST, 
    CS_MSG_GET_PLAYER_INFO_REP = SoccerPlayerInfo<<2 | MSG_REPONSE, 
};

typedef cs_packet<CS_MSG_GET_PLAYER_INFO_REQ,SoccerPlayerInfoRequest> cs_soccer_player_request;
typedef cs_packet<CS_MSG_GET_PLAYER_INFO_REP,SoccerPlayerInfoResponse> cs_soccer_player_response;


#pragma pack()
#endif
