#include "../common/head.h"

#include "move_define.h"

/* 随机的选择一个对应的quality的move */
MoveDefine *pickup_random_move_by_quality(int quality, int formation)
{
	std::vector<MoveDefine *> move_vec;
	std::map<int, MoveDefine *>::iterator itr = g_move_define_table.begin();
	while (itr != g_move_define_table.end())
	{
		if (itr->second->get_card_quality() == quality)
		{
			if (itr->second->check_move_suitable_formation(formation))
			{
				move_vec.push_back(itr->second);
			}
		}
		itr++;
	}	

	int number = move_vec.size();
	if (number == 0)
	{
		return NULL;
	}

	int index_pickup = RAND_INT % number;

	return move_vec[index_pickup];
}

MoveDefine::~MoveDefine(void)
{
    ListIter iter;

    for (iter = _list_bak.begin(); iter != _list_bak.end(); ++iter)
    {
        if (*iter)
        {
            delete *iter;
        }
    }
}

AttackOrder *MoveDefine::pop(void)
{
    ListIter iter = _list.begin();
    if (iter == _list.end())
    {
    	return NULL;
    }

    AttackOrder *result = *iter;
    _list.pop_front();
    _list.push_back(result);
    _current_order_index++;

    return result;
}

AttackOrder *MoveDefine::get_pop(void)
{
    ListIter iter = _list.begin();
    if (iter == _list.end())
    {
    	return NULL;
    }

    AttackOrder *result = *iter;

    return result;
}

int MoveDefine::order_left(void)
{
	return _list.size() - _current_order_index;
}

void MoveDefine::remove_first(void)
{
    ListIter iter = _list.begin();
    if (iter != _list.end())
    {
    	_list.erase(iter);
    	_current_order_index--;
    }
}
