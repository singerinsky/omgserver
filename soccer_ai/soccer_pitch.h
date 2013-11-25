/*
 * soccer_pitch.h
 *
 *  Created on: 2011-12-05
 *      Author: singerinsky
 */

#ifndef SOCCER_PITCH_H_
#define SOCCER_PITCH_H_

#include "soccer_region.h"
//#include "vector2d.h"

class SoccerPitch
{
public:
	//右边的禁区的区域
	static RegionSet forbidden_area_r;
	//左边禁区的区域
	static RegionSet forbidden_area_l;
	//遠射區域
	static RegionSet fat_shoot_area;
	//static double pitch_width;
	//static double pitch_height;

	SoccerPitch();
	~SoccerPitch();
	void init();
	static SoccerPitch* GetInstance(){
		if(_instance == NULL){
			_instance = new SoccerPitch();
		}
		return _instance;
	}
private:
	static SoccerPitch* _instance;
};

#endif /* SOCCER_PITCH_H_ */
