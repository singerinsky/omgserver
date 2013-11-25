#ifndef _TELEGRAM_H_
#define _TELEGRAM_H_

#include "../common/head.h"
#include "vector2d.h"
#include "soccer_region.h"

typedef enum
{
    TELE_BALL_KICK,
    TELE_BALL_STOP,
    TELE_BALL_CROSS,
    TELE_BALL_GOAL_FLY,

    TELE_PLAYER_DRIBBLE,
    TELE_PLAYER_SUPPORT,
    TELE_PLAYER_PASS,
    TELE_PLAYER_RECEIVE,
    TELE_PLAYER_PASS_ME,
    TELE_PLAYER_SHOOT,
    TELE_PLAYER_MOVE,
    TELE_PLAYER_AreaDefendState,
    TELE_PLAYER_MIND_ON_PLAYER,
    TELE_PLAYER_MIND_ON_BALL,
    TELE_PLAYER_MARK_PLAYER,
    TELE_PLAYER_MARK_BALL,
    TELE_PLAYER_KICK_OFF,
    TELE_PLAYER_PENALTY,
    TELE_PLAYER_FREE,
    TELE_PLAYER_CROSS,
    TELE_PLAYER_CORNER,
    TELE_PLAYER_CORNOR,

    TELE_FORCE_CROSS, // 强制长传
    TELE_FORCE_SHOOT, // 强制射门
    TELE_PLAYER_RUN,//跑位
    TELE_FORCE_PASS,//强制快速传球

    END_TELE
} TeleType;

struct Telegram
{
    Telegram(uint32_t src_id, uint32_t dest_id, int message);

    ~Telegram(void);

    uint32_t src_id;
    uint32_t dest_id;
    int message;
};

struct BallTelegram: public Telegram
{
    BallTelegram(uint32_t src_id, uint32_t dest_id, int message)
    	: Telegram(src_id, dest_id, message)
    {
    }

    uint32_t speed;
    uint32_t speed_z;
    Vector2D heading;
};

struct PlayerTelegram: public Telegram
{
    PlayerTelegram(uint32_t src_id, uint32_t dest_id, int message)
    	: Telegram(src_id, dest_id, message)
    {
        target_id = 0;
    }

    RegionSet target_regions;
    int target_id;
};

inline Telegram::Telegram(uint32_t src_id, uint32_t dest_id, int message)
{
    this->src_id = src_id;
    this->dest_id = dest_id;
    this->message = message;
}

inline Telegram::~Telegram(void)
{
}

#endif /* _TELEGRAM_H_ */
