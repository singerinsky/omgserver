/*
 * CDBhandlerJob.cpp
 *
 *  Created on: 2012-3-16
 *      Author: root
 */

#include "CDBhandlerJob.h"

CDBQueryhandlerJob::~CDBQueryhandlerJob() {
	// TODO Auto-generated destructor stub
}

void CDBQueryhandlerJob::AddTask(CMsgEvent* event) {
	this->_task_all++;
	this->_msg_queue.enqueue(event);
}

void CDBQueryhandlerJob::ExecuteJob() {
	while(1){
		CMsgEvent* event = _msg_queue.dequeue();
		if (event != NULL) {
			this->_task_processed++;
			if (event->_msg_type == 2000) {//查询比赛双方的信息
				int home_cid, away_cid,mid;
				MsgInitMatch* msg_base = (MsgInitMatch*)event->_msg_base;
				mid = msg_base->mid;
				home_cid = msg_base->cid;
				away_cid = msg_base->op_cid;
				VLOG(1)<<" db query start "<<home_cid<<":"<<away_cid;
				MsgMatchTeamInfo *info = new MsgMatchTeamInfo();
				info->mid = mid;
				info->is_home_in_new_bie = msg_base->is_new_bie;
				info->type = msg_base->match_typ;
				info->need_win = msg_base->need_win;
				info->is_home_all_attack = msg_base->is_home_all_attack;
				info->op1.uid = home_cid;
				info->op2.uid = away_cid;
				info->total_time_scale = msg_base->total_time_scale;
				int npc_player_rat = 100;
				int match_key = 0;
				QueryFixtureInfo(mid,home_cid,away_cid,info->type,npc_player_rat,match_key);
				info->match_key = match_key;
				if(npc_player_rat == 0){
					npc_player_rat = 100;
				}
				info->npc_rate = npc_player_rat;
				//QueryFixtureInfo(mid,home_cid,away_cid);
				int rst1 = QueryMatchOperate(mid,home_cid,info->formation1,info->op1);
				int rst2 = QueryMatchOperate(mid,away_cid,info->formation2,info->op2);
				if((rst1 == -1) || (rst2 == -1)){
					LOG(ERROR)<<"error of match data "<<mid;
					continue;
				}
				if(home_cid < 0){
					ModiferNpcTeamAttribute(info->op1,npc_player_rat);
				}

				if(away_cid < 0){
					ModiferNpcTeamAttribute(info->op2,npc_player_rat);
				}

				CMsgEvent* msg = new CMsgEvent();
				msg->_msg_type = MSG_TYPE_MATCH_INFO;
				msg->_msg_base = info;
				_msg_dispatcher->add_msg_to_queue(msg);
				delete msg_base;
				event->_msg_base = NULL;
			}else if(event->_msg_type == 2010){//比赛信息
				int mid = ((MsgGameToDbServerMatchEnd*)event->_msg_base)->mid;
				UpdateMatchResultInfo(((MsgGameToDbServerMatchEnd*)event->_msg_base));
				UpdateMatchStatus(mid);
				delete (MsgGameToDbServerMatchEnd*)event->_msg_base;
				event->_msg_base = NULL;
			}else if(event->_msg_type == 2013){//球员的属性写回
				MsgGameToDbServerPlayerUpdate* msg = (MsgGameToDbServerPlayerUpdate*)(event->_msg_base);
				UpdatePlayersMatchInfo(msg);
				delete msg;
				event->_msg_base = NULL;
			}else if(event->_msg_type == 2017){
				MsgGameEventDBWB* msg = (MsgGameEventDBWB*)(event->_msg_base);
				WriteBackMatchEvent(msg);
				delete msg;
				event->_msg_base = NULL;
			}else if(event->_msg_type == 2019){
				MsgMatchArenaStartArena *msg = (MsgMatchArenaStartArena*)(event->_msg_base);
				StartArenaMatch(msg);
				delete msg;
				event->_msg_base = NULL;
			}else if(event->_msg_type == 2020){
				MsgUpdateGServerInfo* msg = (MsgUpdateGServerInfo*)(event->_msg_base);
				this->UpdateGServerInfo(msg);
			}
			delete event;
		}else{
			timespec ts;
			ts.tv_nsec = 100000000;
			ts.tv_sec = 0;
			nanosleep(&ts,NULL);
		}

	}
}

void CDBQueryhandlerJob::ModiferNpcTeamAttribute(MsgMoveOperator& msg,int npc_player_rate){

	for(int i=0;i<16;i++){
		MsgPlayerInfo& player = msg.player_info[i];
		double rate = npc_player_rate/100.;
		double rate_2 = rate;
		if (rate_2>100){
			rate_2 = rate_2 - (rate_2 - 100)/1.5;
		}
		for(int attr_index=0;attr_index<19;attr_index++){
			//NPC隐藏属性加成较少
			if (attr_index<8){
				player.attr[attr_index] = player.attr[attr_index]*rate;
			} else {
				player.attr[attr_index] = player.attr[attr_index]*rate_2;
			}

		}
	}
}


void CDBQueryhandlerJob::QueryFixtureInfo(int mid, int& home_cid, int& away_cid,int& type,int& npc_player_rat,int& key) {
	std::ostringstream strbuff;
	strbuff << "select * from c_fixture where mid =";
	strbuff << mid;
	strbuff.clear();
	std::string str = strbuff.str();
	mysqlpp::Query query = _conn->query(str.c_str());
	mysqlpp::StoreQueryResult res = query.store();
	if (res.num_rows() <= 0) {
		LOG(ERROR)<<"No Such match"<<mid;
		return;
	} else {
		home_cid = res[0]["cid"];
		away_cid = res[0]["op_cid"];
		type = res[0]["typ"];
		npc_player_rat = res[0]["npc_player_rat"];
		key = res[0]["match_key"];
	}
}

int CDBQueryhandlerJob::QueryMatchOperate(int mid, int cid, int formation[],
		MsgMoveOperator &op) {
	std::string strbuff;
	strbuff.append("select cid,formation_id,formation_level,tactic_id , is_home_uid ");
	for (int pos = 1; pos <= 16; pos++) {
		char tmp[24];
		snprintf(tmp, 15, ", position_%d", pos);
		strbuff.append(tmp);
	}

	char tmp[256];
	snprintf(tmp, 256, " ,club_level,att_value,def_value,default_att_value,default_def_value,coach_speak,tactic_buff,fitness_coach from match_operating as m  where m.mid=%d and cid=%d",
			mid, cid);
	strbuff.append(tmp);
	mysqlpp::Query query = _conn->query(strbuff.c_str());
	mysqlpp::UseQueryResult res = query.use();
	int count=0;
	while (mysqlpp::Row row = res.fetch_row()) {
		op.uid = row["cid"];
		op.formation_id = row["formation_id"];
		op.formation_level = row["formation_level"];
		op.tactic_id = row["tactic_id"];
		op.club_level = row["club_level"];
		op.att_value = row["att_value"];
		op.def_value = row["def_value"];
		op.default_att_value = row["default_att_value"];
		op.default_def_value = row["default_def_value"];
		op.default_coach_speak = row["coach_speak"];
		op.alias_tactic_plus	= row["tactic_buff"];
		op.fitness_coach		= row["fitness_coach"];
		char tmp[16];
		for (int i = 1; i < 17; i++) {
			snprintf(tmp, 16, "position_%d", i);
			formation[i - 1] = row[tmp];
		}
		count++;
	}
	QueryTeamSkillInfo(cid,op);
	if(count == 0){
		LOG(ERROR)<<"NO PLAYER DATEA.................."<<cid<<":"<<mid;
	}
	for (int i = 0; i < 16; i++) {
		int rst = QueryPlayerAttrInfo(formation[i], op.player_info[i]);
		if(rst == -1){
			LOG(ERROR)<<"No such player in the table p_player_final_attr"<<op.player_info[i].pid<<":"<<cid<<":"<<mid;
			return -1;
		}

		op.player_info[i].pid = formation[i];
		op.player_info[i].pos_index = i+1;
	}
	return 1;
}

int  CDBQueryhandlerJob::QueryPlayerAttrInfo(int pid, MsgPlayerInfo& info) {
	if(pid < 0 ){
		MsgPlayerInfo* tmp_info = CNpcPlayerCache::GetInstance()->QueryPlayerInfo(pid);
		if(tmp_info != NULL){
			memcpy(&info,tmp_info,sizeof(MsgPlayerInfo));
			return 1;
		}
	}
	/*******query player general infomation ******/
	std::ostringstream query_player_cond;
	if(pid > 0){
		query_player_cond<<"SELECT cond,player_name,level,att_value,def_value FROM p_player WHERE pid=";
		query_player_cond<<pid;
	}else{
		query_player_cond<<"SELECT cond,player_name,level,att_value,def_value FROM s_rp_player WHERE pid=";
		query_player_cond<<pid;
	}
	mysqlpp::Query player_info_query = _conn->query(query_player_cond.str().c_str());
	mysqlpp::StoreQueryResult result = player_info_query.store();
	if(result.num_rows() < 1){
		LOG(ERROR)<<"player "<<pid<<" can't found ..";
		GeneralPlayerInfoUnFound(pid,info);
		return 1;
	}else{
		info.cond =  result[0]["cond"];
		if(info.cond < 10){
			info.cond = 60;
		}
		info.level =  result[0]["level"];
		info.att_value =  result[0]["att_value"];
		info.def_value =  result[0]["def_value"];
		const mysqlpp::String name =  result[0]["player_name"];
		memcpy(info.player_name,name.c_str(),20);
	}
	//取属性
	std::ostringstream strbuff;
	if(pid < 0){
		strbuff
			<< "select pid,is_gk,\
			att_gk_save,att_gk_com_def,att_phy,att_creat,att_shoot,att_pass,att_ball_ctrl,att_defend, \
			speed,bounce,strong,aggressive,moves,vision,free_kick,\
			header_accuracy,long_range,penalty,kickoff from  s_rp_player_attr where pid =";
		strbuff<<pid;
	}else{
		strbuff
			<< "select pid,is_gk,\
			att_gk_save,att_gk_com_def,att_phy,att_creat,att_shoot,att_pass,att_ball_ctrl,att_defend, \
			speed,bounce,strong,aggressive,moves,vision,free_kick,\
			header_accuracy,long_range,penalty,kickoff from  p_player_final_attr where pid =";
		strbuff << pid;
	}
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	mysqlpp::StoreQueryResult rst = query.store();
	if (rst.num_rows() < 1) {
		info.attr_numbers = 19;
		info.is_gk = 0;
		for(int i=0;i<19;i++){
			info.attr[i] = 50;
		}
	} else {
		double level_dis = 1.;
		if(pid > 0){
			level_dis = (info.level + 50.)/100.;
		}
		info.attr_numbers = 19;
		info.is_gk = rst[0]["is_gk"];
		info.attr[0] = rst[0]["att_gk_save"];
		info.attr[1] = rst[0]["att_gk_com_def"];
		info.attr[2] = rst[0]["att_phy"];
		info.attr[3] = rst[0]["att_creat"];
		info.attr[4] = rst[0]["att_shoot"];
		info.attr[5] = rst[0]["att_pass"];
		info.attr[6] = rst[0]["att_ball_ctrl"];
		info.attr[7] = rst[0]["att_defend"];
		info.attr[8] = rst[0]["speed"];
		info.attr[9] = rst[0]["bounce"] * level_dis;
		info.attr[10] = rst[0]["strong"] * level_dis;
		info.attr[11] = rst[0]["aggressive"] * level_dis;
		info.attr[12] = rst[0]["moves"] * level_dis;
		info.attr[13] = rst[0]["vision"] * level_dis;
		info.attr[14] = rst[0]["free_kick"] * level_dis;
		info.attr[15] = rst[0]["header_accuracy"] *level_dis;
		info.attr[16] = rst[0]["long_range"] *level_dis;
		info.attr[17] = rst[0]["penalty"] *level_dis;
		info.attr[18] = rst[0]["kickoff"] *level_dis ;
	}

	//取技能
	std::ostringstream query_skill;
	query_skill<<"SELECT * FROM p_player_skill WHERE pid =";
	query_skill<<pid;
	query_skill<<" limit 8";
	query = _conn->query(query_skill.str().c_str());
	size_t count=0;
	if(mysqlpp::StoreQueryResult res = query.store()){
		for(;count<res.num_rows();count++){
			info.player_skills[count].skill_chance = res[count]["chance"];
			info.player_skills[count].skill_id = res[count]["skill_id"];
			info.player_skills[count].skill_level = res[count]["skill_level"];
			if(count >10){
				break;
			}
		}
	}
	info.skill_count = count;
	//取攻防指数,NPC球队里面的球员的PID为负数

	if(pid <0){
		VLOG(1)<<"ADD "<<pid<<"to cache";
		CNpcPlayerCache::GetInstance()->AddPlayerInfoToCache(pid,&info);
	}
	return 1;

}

void CDBQueryhandlerJob::UpdateMatchStatus(int mid){
	char sql[256];
	time_t time1 = 0 ;

	snprintf(sql,256,"update e_user set zeit= %d where mapping_id=%d and typ=3 and flag=0",(int)time1,mid);
	mysqlpp::Query query = _conn->query(sql);
	query.store();

	memset(sql,0,256);
	snprintf(sql,256,"update c_fixture set flag=4 where mid = %d",mid);
	query = _conn->query(sql);
	query.store();
}

void CDBQueryhandlerJob::UpdateMatchResultInfo(MsgGameToDbServerMatchEnd* msg){
	std::ostringstream strbuff;
	strbuff<<"INSERT INTO match_detail (mid,home_cid,away_cid,typ,score_h,score_a,result,possession_rate_h,possession_rate_a"
		",shot_h,shot_a,shot_on_a,shot_on_h,penalty_h,penalty_a,match_statis)VALUES(";
	strbuff<<msg->mid;
	strbuff<<",";
	strbuff<<msg->home_cid;
	strbuff<<",";
	strbuff<<msg->away_cid;
	strbuff<<",";
	strbuff<<msg->typ;
	strbuff<<",";
	strbuff<<msg->home_score;
	strbuff<<",";
	strbuff<<msg->away_score;
	strbuff<<",";
	if((msg->home_score+msg->penlty_h) > (msg->away_score + msg->penlty_a)){
		strbuff<<1;
	}else if((msg->home_score+msg->penlty_h) == (msg->away_score+msg->penlty_a)){
		strbuff<<0;
	}else{
		strbuff<<-1;
	}
	strbuff<<",";
	strbuff<<msg->home_possession;
	strbuff<<",";
	strbuff<<msg->away_possession;
	strbuff<<",";
	strbuff<<msg->shot_h;
	strbuff<<",";
	strbuff<<msg->shot_a;
	strbuff<<",";
	strbuff<<msg->shot_on_a;
	strbuff<<",";
	strbuff<<msg->shot_on_h;
	strbuff<<",";
	strbuff<<msg->penlty_h;
	strbuff<<",";
	strbuff<<msg->penlty_a;
	strbuff<<",'";
	strbuff<<msg->statis_data;
	strbuff<<"'";
	strbuff<<")";
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	query.store();
	LOG(INFO)<<strbuff.str();
}

void CDBQueryhandlerJob::UpdatePlayersMatchInfo(MsgGameToDbServerPlayerUpdate* msg){
	std::ostringstream strbuff;
	strbuff<<"INSERT INTO match_player_detail (mid,pid,player_name,cid,shots,passes,tackles,"
		"match_rating,goals,assist,steals,red_card,yellow_card,inj,app_count,offsides,cond,exp) VALUES";
	strbuff<<msg->data;
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	query.store();
}

void CDBQueryhandlerJob::WriteBackMatchEvent(MsgGameEventDBWB* msg){
	if(msg->event_count == 0)
		return;

	//char* tmp = new char[sizeof(GameEvent)*msg->event_count];
	std::ostringstream strbuff;
	strbuff<<"INSERT INTO match_action(mid,zeit,cid,pid,op_pid,action)values";
	strbuff<<"("<<msg->mid<<","<<msg->event[0].timescale<<","<<msg->event[0].cid<<","<<msg->event[0].pid<<","<<msg->event[0].op_pid<<","<<msg->event[0].type<<")";
	//strbuff<<"("<<msg->mid<<","<<msg->event[1].timescale<<","<<msg->event[1].cid<<","<<msg->event[1].pid<<","<<msg->event[1].op_pid<<","<<msg->event[1].type<<")";

	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	query.store();
}

void CDBQueryhandlerJob::QueryTeamSkillInfo(int cid, MsgMoveOperator& team_op) {
	std::ostringstream strbuff;
	strbuff << "SELECT c_tactic.tactic_id,c_tactic.chance FROM c_tactic WHERE in_use = 1 AND cid=";
	strbuff << cid;
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	mysqlpp::UseQueryResult result = query.use();
	int skill_index = 0;
	while (mysqlpp::Row row = result.fetch_row()) {
		team_op.team_skills[skill_index].tactic_id = row["tactic_id"];
		int chance = row["chance"];
		team_op.team_skills[skill_index].chance = chance;
		skill_index++;
	}
	team_op.team_skill_count = skill_index;

	for(int i=0;i<skill_index;i++){
		int buff = QueryTeamSkillBuff(cid,team_op.team_skills[i].tactic_id);
		team_op.team_skills[i].chance += buff*100;
	}

}

int CDBQueryhandlerJob::QueryTeamSkillBuff(int cid,int tactic_id){
	std::ostringstream stdbuff;
	stdbuff<<"SELECT buff FROM c_tactic_buff WHERE cid =";
	stdbuff<<cid;
	stdbuff<<" AND tactic_id =";
	stdbuff<<tactic_id;
	VLOG(1)<<stdbuff.str().c_str();
	mysqlpp::Query query = _conn->query(stdbuff.str().c_str());
	mysqlpp::UseQueryResult result = query.use();	
	while(mysqlpp::Row row = result.fetch_row()){
		return row["buff"];
	}
	return 0;
}
//INSERT INTO  e_user  (typ,flag,uid,target_id,zeit) values (2,0,$uid,$op_uid,$zeit);
void CDBQueryhandlerJob::StartArenaMatch(MsgMatchArenaStartArena* msg){
	std::ostringstream strbuff;
	strbuff<<"INSERT INTO e_user(typ,flag,uid,target_id,mapping_id,zeit)VALUES(2,0,";
	strbuff<<msg->home_cid;
	strbuff<<",";
	strbuff<<msg->away_cid;
	strbuff<<",";
	strbuff<<msg->key;
	strbuff<<",";
	time_t zeit= 0;
	strbuff<<zeit;
	strbuff<<")";
	LOG(INFO)<<"arena key"<<msg->key;
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	mysqlpp::StoreQueryResult rst = query.store();
}

void CDBQueryhandlerJob::UpdateGServerInfo(MsgUpdateGServerInfo* msg){
	std::ostringstream strbuff;
	strbuff<<"SELECT * FROM match_server_info WHERE server_index=";
	strbuff<<msg->index;
	mysqlpp::Query query = _conn->query(strbuff.str().c_str());
	mysqlpp::StoreQueryResult rst = query.store();
	if (rst.num_rows() >0 ) {
		std::ostringstream del_str;
		del_str<<"delete from match_server_info where server_index =";
		del_str<<msg->index;
		mysqlpp::Query del_query = _conn->query(del_str.str().c_str());
		del_query.store();
	}
	std::ostringstream insert_buff;
	insert_buff<<"INSERT INTO match_server_info(server_index,server_typ,server_version,last_update_version)values(";
	insert_buff<<msg->index;
	insert_buff<<",";
	insert_buff<<msg->server_typ;
	insert_buff<<",'";
	insert_buff<<msg->version;
	insert_buff<<"'";
	insert_buff<<",";
	insert_buff<<time(NULL);
	insert_buff<<")";
	mysqlpp::Query insert_query = _conn->query(insert_buff.str().c_str());
	insert_query.exec();
}

void CDBQueryhandlerJob::GeneralPlayerInfoUnFound(int pid, MsgPlayerInfo& info){
	info.cond = 80;
	info.level =  20;
	info.att_value =  400;
	info.def_value =  400;
	const mysqlpp::String name("神秘人");
	memcpy(info.player_name,name.c_str(),20);

	info.attr_numbers = 19;
	info.is_gk = 0;
	for(int i=0;i<19;i++){
		info.attr[i] = 50;
	}
	info.skill_count = 0;
}


