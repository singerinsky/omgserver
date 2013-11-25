#include "../common/head.h"

#include "../common/cmmmo_define.h"
#include "../soccer_ai/move_define.h"
#include "../soccer_ai/action_define.h"
#include "../soccer_ai/event_define.h"
/*
void init_move_define_100(MoveDefine *move_define)
{
    move_define->set_init_player(9);

    AttackOrder *order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(0, 1110), Vector2D(487, 888)));
    order->target_player_id = 10;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(487, 1110),Vector2D(1218, 888)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 770), Vector2D(1950, 330)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_SHOOT);
    move_define->add_order(order);

    move_define->add_final_order();
}

void init_move_define_112(MoveDefine *move_define)
{
	move_define->set_move_id(112);
    move_define->set_init_player(10);

    AttackOrder *order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(0, 770), Vector2D(365, 330)));
    order->target_player_id = 9;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(487, 770),Vector2D(1462, 330)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 770), Vector2D(1950, 330)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_SHOOT);
    move_define->add_order(order);

    move_define->add_final_order();
}

void init_move_define_113(MoveDefine *move_define)
{
    move_define->set_init_player(10);

    AttackOrder *order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(0,770), Vector2D(365,330)));
    order->target_player_id = 9;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 770), Vector2D(1950, 330)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_SHOOT);
    move_define->add_order(order);

    move_define->add_final_order();
}

void init_move_define_114(MoveDefine *move_define)
{
    move_define->set_init_player(9);

    AttackOrder *order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(0, 770), Vector2D(365, 330)));
    order->target_player_id = 8;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(487, 222),Vector2D(1218, 0)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_MOVE);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 444),Vector2D(1950, 666)));
    order->target_player_id = 6;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_DRIBBLE);
    order->target_regions.push_back(SoccerRegion(Vector2D(1706, 222), Vector2D(1950, 0)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 444),Vector2D(1950, 666)));
    order->target_player_id = 6;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_SHOOT);
    move_define->add_order(order);

    move_define->add_final_order();
}

void init_move_define_115(MoveDefine *move_define)
{
    move_define->set_init_player(9);

    AttackOrder *order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(0, 770), Vector2D(365, 330)));
    order->target_player_id = 8;
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(487, 222),Vector2D(975, 0)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1218, 222), Vector2D(1950, 0)));
    move_define->add_order(order); 

    order = new AttackOrder(ORDER_PASS);
    order->target_regions.push_back(SoccerRegion(Vector2D(1584, 770), Vector2D(1950, 330)));
    move_define->add_order(order);

    order = new AttackOrder(ORDER_SHOOT);
    move_define->add_order(order);

    move_define->add_final_order();
}
*/
std::map<int, MoveDefine *> g_move_define_table;
std::map<int, ActionDefine*> g_action_define_table;
std::map<int, EventDefine*> g_event_define_table;
std::map<int, REAL_PLAYER_INFO*> g_all_splayer_data;
struct FormationDefine;
std::map<int ,FormationDefine*> g_card_formation;
/*
void init_move_define(void)
{
    MoveDefine *define = new MoveDefine();
    init_move_define_100(define);
    g_move_define_table[100] = define;
    
    define = new MoveDefine();
    init_move_define_112(define);
    g_move_define_table[112] = define;

    define = new MoveDefine();
    init_move_define_113(define);
    g_move_define_table[113] = define;

    define = new MoveDefine();
    init_move_define_114(define);
    g_move_define_table[114] = define;

    define = new MoveDefine();
    init_move_define_115(define);
    g_move_define_table[115] = define;
}
*/
