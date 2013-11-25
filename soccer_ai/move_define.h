#ifndef _MOVE_TYPE_H_
#define _MOVE_TYPE_H_

#include <list>
#include "attack_order.h"
#include "../common/rand_generator.h"
using namespace std;

template<class T>
class Template_Factory
{
public:
	static T *create_instance()
	{
		return new T();
	}
};

class MoveDefine
{

friend class Template_Factory<MoveDefine>;
protected:
    MoveDefine(void) {}

public:
    MoveDefine(const MoveDefine &m)
    {
		_card_id = m.get_move_id();
        _init_player = m._init_player;
        _move_typ = m.get_move_typ();
        _current_order_index = 1;
        List::const_iterator it;
        for (it = m._list.begin(); it != m._list.end(); ++it)
        {
            AttackOrder *ao = *it;
            if (ao == NULL)
            {
                add_final_order();
            }
            else
            {
                AttackOrder *o = new AttackOrder(*ao);
                add_order(o);
            }
        }
    }

    ~MoveDefine(void);

    void add_order(AttackOrder *order)
    {
        _list.push_back(order);
        _list_bak.push_back(order);
    }

    void add_order_in_front(AttackOrder *order)
    {
    	_list.push_front(order);
    	_list_bak.push_back(order);
    }

    void add_final_order(void)
    {
        _list.push_back(NULL);
    }

    void reset(void)
    {
        while (true)
        {
            if (pop() == NULL)
            {
                return;
            }
        }

        ListIter iter;
        for (iter = _list_bak.begin(); iter != _list_bak.end(); ++iter)
        {
            if (*iter)
            {
                delete *iter;
            }
        }

    }

    SoccerRegion get_region(int pos)
    {
        SoccerRegion r;
        r.x1 = (16 - ((int)((pos - 1) / 5) + 1) * 2) * LATTICE_SIZE_X;
        r.y1 = ((int)(pos - 1) % 5)*2 * LATTICE_SIZE_Y;
        r.x2 = (16 - ((int)((pos - 1) / 5)) * 2) * LATTICE_SIZE_X;
        r.y2 = ((int)(pos - 1) % 5 * 2 + 2) * LATTICE_SIZE_Y;
        return r;
    }

    void update_region(void)
    {
        List::iterator it;
        for (it = _list.begin(); it != _list.end(); ++it)
        {
            AttackOrder *ao = *it;
            if ((ao != NULL))
            {
            	if((ao->target_region_lt != -1)){
					SoccerRegion lt = get_region(ao->target_region_lt);
					SoccerRegion rb = get_region(ao->target_region_rb);
					lt.x1 = rb.x1;
					lt.y2 = rb.y2;
					ao->target_regions.push_back(lt);
            	}

            	if((ao->src_region_lt != -1)){
            		SoccerRegion lt = get_region(ao->src_region_lt);
            		SoccerRegion rb = get_region(ao->src_region_rb);
					lt.x1 = rb.x1;
					lt.y2 = rb.y2;
					ao->src_regions.push_back(lt);
            	}
            }
        }
    }

    AttackOrder *pop(void);

    AttackOrder *get_pop(void);

    AttackOrder *peek(void)
    {
        return *_list.begin();
    }

    int order_left(void);

    int get_current_order(void)
    {
    	return this->_current_order_index;
    }

    void set_init_player(int init_player)
    {
        _init_player = init_player;
    }

    int get_init_player(void)
    {
        return _init_player;
    }

    void set_move_typ(int move_typ)
    {
    	this->_move_typ = move_typ;
    }

    int get_move_typ(void) const
    {
    	return this->_move_typ;
    }

	void set_card_quality(int quality)
	{
		this->_card_quality = quality;
	}

	int get_card_quality(void)
	{
		return this->_card_quality;
	}

	void set_card_complex(int paramComplex)
	{
		this->_card_complex = paramComplex;
	}

	int get_card_complex(void)
	{
		return this->_card_complex;
	}

	void set_move_id(int move_id)
	{
		this->_card_id = move_id;
	}

	int get_move_id(void) const
	{
		return this->_card_id;
	}

	int get_order_count(void)
	{
		return this->_list.size();
	}

    void remove_first(void);

    void add_suitable_formation_list(int formation_id)
    {
    	this->_suitable_formation_list.push_back(formation_id);
    }

    bool check_move_suitable_formation(int formation_id)
    {
    	std::list<int>::iterator itr = _suitable_formation_list.begin();
    	while (itr != _suitable_formation_list.end())
    	{
    		if (*itr == formation_id)
    		{
    			return true;
    		}
    		itr++;
    	}
    	return false;
    }

    std::list<AttackOrder*>& get_all_order_list(){
    	return _list;
    }

private:
    typedef std::list<AttackOrder *> List;
    typedef List::iterator ListIter;

    std::list<int> _suitable_formation_list;

    List _list;
    List _list_bak;
    int _init_player;
	int _card_id;
    int _move_typ;
	int _card_complex;
	int _card_quality;
    int _current_order_index;
public:
    int get_move_complex(){
    	return this->_card_complex;
    }
};

extern std::map<int, MoveDefine *> g_move_define_table;

MoveDefine *pickup_random_move_by_quality(int quality, int formation_id);

#endif /* _MOVE_TYPE_H_ */
