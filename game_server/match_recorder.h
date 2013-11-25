#ifndef _MATCH_RECORDER_H_
#define _MATCH_RECORDER_H_

#include "../soccer_ai/vector2d.h"
#include "../soccer_ai/soccer_match.h"
#include "Event.h"

#include "../common/string.h"
#include "player_keyframe.h"
#include "ball_keyframe.h"
#include "match_engine_events.h"
#include "msg.h"

#include <map>

class MatchRecorder
{
    template<class T>class ptr_list : public std::list<T *>
    {
    public:
        typedef T obj_type;

        ~ptr_list(void)
        {
            typename std::list<T *>::iterator iter;
            for (iter = std::list<T *>::begin(); iter != std::list<T *>::end(); ++iter)
            {
                delete *iter;
            }
        }
    };

    typedef ptr_list<BallKeyframe> BallFrameList;
    typedef ptr_list<PlayerKeyframe> PlayerFrameList;
    typedef std::vector<PlayerUseSkill> PlayerSkillVec;
    typedef std::vector<MatchPentlyEvent> MatchPentlyList;

    static const int RECORDER_PLAYER_COUNT = 22;

    BallFrameList _ball_frames;
    PlayerFrameList _players_frames[RECORDER_PLAYER_COUNT];
    PlayerSkillVec	_players_skill_vec;
    MatchPentlyList	_match_pently_list;


    SoccerMatch *_match;
    bool _reverse;
    bool _is_half;
    int _start_time;

    std::vector<MatchBuff> _buff_frames;

    int who_att;
    int move_typ;

    std::vector<MatchEvent> _event_frames;

    std::vector<PlayerRedYellowInj> prcyci;

    std::vector<DefPlayerID> dpid;

    int _penalty_count;  // 点球大战计数器

    std::map<int, PlayerRedYellowInj> _pid_info;

    int _match_end_typ;	//比赛结束的大类型

    int _match_end_sub_typ;	//比赛结束的子类型

    int _match_next_typ;	//下一轮的类型

    int _match_id;

    int _round_id;

    PlayerRedYellowInj _match_end_r_y_i;

    int gk_pid_1;
    int gk_pid_2;

    bool _has_pently_data;

public:
    MatchRecorder(SoccerMatch *match,bool is_first_half,bool reverse)
    	: _match(match)
    {
    	_buff_frames.clear();
    	_event_frames.clear();
        _reverse = reverse;
        who_att = 0;
        prcyci.clear();
        _penalty_count = 0;
        _pid_info.clear();
        dpid.clear();
        set_match_end_r_y_i();
        _is_half = is_first_half;
        _has_pently_data = false;
    }


    void update(void);

    void set_gk_pid(int gk1, int gk2)
    {
        gk_pid_1 = gk1;
        gk_pid_2 = gk2;
    }

    void set_match_end_r_y_i(void)
    {
    	_match_end_r_y_i.red_card = 0;
    	_match_end_r_y_i.yellow_card = 0;
    	_match_end_r_y_i.inj = 0;
    }

    void reset_match_end_red_card(void)
    {
    	_match_end_r_y_i.red_card = 1;
    }

    void reset_match_end_yellow_card(void)
	{
		_match_end_r_y_i.yellow_card = 1;
	}

    void reset_match_end_inj(void)
	{
		_match_end_r_y_i.inj = 1;
	}

    void set_match_id(int mid)
    {
    	_match_id = mid;
    }

    void set_match_round_id(int round_id)
    {
    	_round_id = round_id;
    }

    int get_match_round_id(void)
    {
    	return _round_id;
    }

    void set_pid_info(std::map<int, PlayerRedYellowInj> &pid_info)
    {
    	for (std::map<int, PlayerRedYellowInj>::iterator it = pid_info.begin();
    		 it != pid_info.end(); ++it)
    	{
    		_pid_info.insert(std::map<int, PlayerRedYellowInj>::value_type(it->first, it->second));
    	}
    }

    void set_penalty_count(int i)
    {
    	_penalty_count = i;
    }

    void set_prcyci(PlayerRedYellowInj p)
    {
    	prcyci.push_back(p);
    }

    void set_who_att_move_typ(int flag_add_move_typ, int uid, int mt)
    {
    	if (flag_add_move_typ == 0)
    	{
    		if (mt == 1)
    		{
    			mt = 2;
    		}
    		else if (mt == 2)
    		{
    			mt = 1;
    		}
    	}

    	who_att = uid;
    	move_typ = mt;
    }

    bool has_pently_data(){
    	return this->_has_pently_data;
    }

    MsgMatchPentlyResultData* export_pently_data();

    void add_skill_frames(int time_scale,int skill_id,int pid){
    	PlayerUseSkill skill;
    	skill.pid = pid;
    	skill.skill_id = skill_id;
    	skill.time_scale = time_scale;
    	this->_players_skill_vec.push_back(skill);
    }

    void set_event_frames(int time_scale,int cid, int type, int pid, int op_pid)
    {
    	MatchEvent me;
		me.timescale = time_scale;
		me.type = type;
		me.pid = pid;
		me.cid = cid;
		me.op_pid = op_pid;
    	_event_frames.push_back(me);
    }

    void set_pently_event(std::vector<MatchPentlyEvent>* list){
    	if(list->size() >0){
    		_match_pently_list.assign(list->begin(),list->end());
    		_has_pently_data = true;
    	}
    }

    void set_dpid(int timescale, int pid)
    {
    	DefPlayerID dp(timescale, pid);
    	dpid.push_back(dp);
    }

    void set_buff_frames(std::vector<MatchBuff>::const_iterator cite)
    {
    	MatchBuff mb;
    	mb.mid = cite->mid;
    	mb.round_id = cite->round_id;
    	mb.pid = cite->pid;
    	mb.buff_typ = cite->buff_typ;
    	mb.buff_value = cite->buff_value;
    	mb.op_buff_typ = cite->op_buff_typ;
    	mb.position_id = cite->position_id;
    	_buff_frames.push_back(mb);
    }

    void set_start_time(int start_time)
    {
        _start_time = start_time;
    }

    void set_reverse(bool r)
    {
        _reverse = r;
    }

    bool get_reverse(){
    	return _reverse;
    }

    void set_is_half(bool r)
	{
    	_is_half = r;
	}

    bool is_half(){
    	return _is_half;
    }

    omg::StringBuilder *export_str(void);

    omg::StringBuilder *export_str_player(void);

    omg::StringBuilder *export_str_ball();

    omg::StringBuilder *export_str_event();

    omg::StringBuilder *export_str_skill();

    bool export_event_db(MsgGameEventDBWB&,int);

    int get_start_time(void)
    {
    	return _start_time;
    }

    //更新裁判状态

    int getMatch_end_sub_typ() const
	{
    	return _match_end_sub_typ;
	}

	int getMatch_end_typ() const
	{
		return _match_end_typ;
	}

	int getMatch_next_typ() const
	{
		return _match_next_typ;
	}

	void setMatch_end_sub_typ(int _match_end_sub_typ)
	{
		this->_match_end_sub_typ = _match_end_sub_typ;
	}

	void setMatch_end_typ(int _match_end_typ)
	{
		this->_match_end_typ = _match_end_typ;
	}

	void setMatch_next_typ(int _match_next_typ)
	{
		this->_match_next_typ = _match_next_typ;
	}

private:
    void update_player(int player_id);

    template<typename List, typename Obj>
    void export_item(List &list, Obj *obj, const char *name)
    {
        if (list.empty())
        {
            list.push_back(new typename List::obj_type(_match->time_scale(), obj));
            list.push_back(new typename List::obj_type(_match->time_scale(), obj));

            return;
        }

        typename List::obj_type *p = *(list.rbegin());
        if (p->is_similar(obj))
        {
            p->update_keyframe(_match->time_scale(), obj);
        }
        else
        {
            list.push_back(new typename List::obj_type(_match->time_scale(), obj));
        }
    }

    template<typename Iterator>
    void save_data(Iterator begin, Iterator end, omg::StringBuilder *str, bool reverse ,bool is_half, int flag) const
    {
        Iterator iter = begin;
        Iterator next;

        for (; iter != end;)
        {
            next = iter;
            ++next;

            int time_last = (next == end) ? _match->time_scale() - (*iter)->time_scale() : (*next)->time_scale() - (*iter)->time_scale();
            (*iter)->append_to_buffer(time_last, *str, reverse, is_half, flag);
            iter = next;
        }
    }


};

#endif /* _MATCH_RECORDER_H_ */
