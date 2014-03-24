#include "CDBMsgDispatcher.h"

CDBMsgDispatcher::CDBMsgDispatcher() {
    _dispatcher_timer.set_owner(this);
    _timer_mgr = ServerRun->get_timer_mgr();
}

CDBMsgDispatcher::~CDBMsgDispatcher() {

}


bool CDBMsgDispatcher::add_msg_to_queue(CMsgEvent* event ) {
    GameServerClient* client = NULL;
    //	VLOG(1)<<"GET EVENT FROM GAME SERVER"<<event->_msg_type;
    if (event->_msg_type == MSG_TYPE_SERVER_REGISTER)//游戏服务器注册
    {
        MsgServerRegister *msg = (MsgServerRegister*) event->_msg_base;
        VLOG(1)<<"regsiter Server "<<msg->_server_type<<" "<<msg->_index;
        CServerManage::GetInstance()->RegisterServer(msg->_index,client);
        //MsgUpdateGServerInfo* update_msg = new MsgUpdateGServerInfo();
        //update_msg->index = msg->_index;
        //update_msg->server_typ = msg->_server_type;
        //strncpy(update_msg->version,msg->_version,20);
        //CMsgEvent *update_event = new CMsgEvent();
        //update_event->_msg_base = (MsgBase*)update_msg;
        //update_event->_msg_type = update_msg->msg_type;
        //CDBTaskManage::GetInstance()->AddTaskEvent(update_event);

        delete msg;
        event->_msg_base = NULL;
        delete event;
    } else {
        this->_msg_queue.enqueue(event);
    }
    return true;
}

void CDBMsgDispatcher::dispatch_msg() {
    CMsgEvent* event = _msg_queue.dequeue();
    if (event != NULL) {
        int msg_type = event->_msg_type;
        switch (msg_type) {
            case MSG_INIT_MATCH://init match
                {
                    CDBTaskManage::GetInstance()->AddTaskEvent(event);
                }
                break;
            case MSG_TYPE_MATCH_INFO://查询出比赛的数据，发送到gameserver，标记比赛所在的gameserver
                {
                    MsgMatchTeamInfo* msg = (MsgMatchTeamInfo*) event->_msg_base;
                    GameServerClient* server = NULL;
                    /*
#ifdef _DEBUG_SERVER_INFO
VLOG(1)<<"Debug server info...............op1 uid is "<<msg->op1.uid;

if(msg->op1.uid == 28) {
std::string ip = "192.168.91.57";
server = CServerManage::GetInstance()->AddMatchToServerByIp(ip,msg->mid);
} else {
server = CServerManage::GetInstance()->AddNewMatch(msg->mid);
}
#else
server = CServerManage::GetInstance()->AddNewMatch(msg->mid);
#endif
if(server == NULL) {
*/
                    server = CServerManage::GetInstance()->AddNewMatch(msg->mid);
                    //			}
                    if(server != NULL) {
                        int data = server->send_msg((const char*)event->_msg_base,event->_msg_base->msg_size);
                        VLOG(1)<<"SEND MSG"<<data;
                    } else {
                        VLOG(1)<<"NO SUCH GAME SERVE R";
                    }
delete msg;
event->_msg_base = NULL;
delete event;
}break;
case MSG_TYPE_LOGIN_OUT://断开
{
    GameServerClient* client = CServerManage::GetInstance()->GetGameServerBySocketFd(event->_client_id._fd);
    int server_index = client->index;
    CServerManage::GetInstance()->RemoveServer(server_index);
    VLOG(1)<<"游戏服务器"<<event->_client_id._fd<<"断开!!";
    delete event->_msg_base;
    event->_msg_base = NULL;
    delete event;
}
break;
case MSG_TYPE_MATCH_MOVE://通知比赛开始
{
    int mid = ((MsgRunMatch*)event->_msg_base)->mid;
    GameServerClient* server = CServerManage::GetInstance()->GetMatchRunServer(mid);
    if(server!= NULL) {
        server->send_msg((const char*)event->_msg_base,event->_msg_base->msg_size);
    }
}
break;
case MSG_TYPE_GTODB_SERVER_MATCH_END://比赛结束写回数据
{
    CDBTaskManage::GetInstance()->AddTaskEvent(event);
}
break;
case MSG_TYPE_GTODB_PLAYER_UPDATE://比赛球员数据写回
{
    //MsgGameToDbServerPlayerUpdate* msg = (MsgGameToDbServerPlayerUpdate*)event->_msg_base;
    CDBTaskManage::GetInstance()->AddTaskEvent(event);
}
break;
case MSG_TYPE_GTODB_MATCH_EVENT_WB://比赛事件
{
    CDBTaskManage::GetInstance()->AddTaskEvent(event);
}
break;
case MSG_TYPE_GTODB_START_ARENA://开始挑战成功
{
    CDBTaskManage::GetInstance()->AddTaskEvent(event);
}
break;
case MSG_TYPE_UPDATE_GSERVER://更新游戏服务器状态到数据库服务器
{
    CDBTaskManage::GetInstance()->AddTaskEvent(event);
}
break;
default:
{
    LOG(ERROR)<<"unknown msg....";
}

}
} else {
    //	VLOG(1)<<"null msg .....";
    
        do_wait_ms(200);  

}
}

void* CDBMsgDispatcher::on_run() {
    on_timeout(_timer_mgr);

    while (1) {
        ServerRun->run_util_now();
        dispatch_msg();
    }
    return NULL;
}

void CDBMsgDispatcher::on_timeout(timer_manager* timer)
{
    int64_t now = ServerRun->get_run_ms();
    _dispatcher_timer.set_expired(now+1000); 
    int ret;
    if((ret = _timer_mgr->add_timer(&_dispatcher_timer)) != 0 )
    {
        VLOG(1)<<"error add timer"<<ret;
    }
}
