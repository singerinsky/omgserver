/*
 * soccer_pitch.cpp
 *
 *  Created on: 2011-12-05
 *      Author: singerinsky
 */

#include "soccer_pitch.h"

RegionSet SoccerPitch::forbidden_area_l;
RegionSet SoccerPitch::forbidden_area_r;
RegionSet SoccerPitch::fat_shoot_area;
SoccerPitch* SoccerPitch::_instance;
SoccerPitch::SoccerPitch()
{
	init();
}

SoccerPitch::~SoccerPitch()
{

}

void SoccerPitch::init()
{
	this->forbidden_area_l.x1 = A_GOAL_WIDTH;
	this->forbidden_area_l.y1 = A_FORBIDDEN_AREA_Y;
	this->forbidden_area_l.x2 = A_FORBIDDEN_AREA_X;
	this->forbidden_area_l.y2 = A_FORBIDDEN_AREA_Y + FORBIDDEN_AREA_HEIGHT;

	this->forbidden_area_r.x1 = B_FORBIDDEN_AREA_X;
	this->forbidden_area_r.y1 = B_FORBIDDEN_AREA_Y;
	this->forbidden_area_r.x2 = B_GOAL_WIDTH;
	this->forbidden_area_r.y2 = B_FORBIDDEN_AREA_Y+FORBIDDEN_AREA_HEIGHT;

	this->fat_shoot_area.x1 = B_FORBIDDEN_AREA_X - 15*METER_TO_POINT;
	this->fat_shoot_area.y1 = B_FORBIDDEN_AREA_Y;
	this->fat_shoot_area.x2 = B_FORBIDDEN_AREA_X;
	this->fat_shoot_area.y2 = B_FORBIDDEN_AREA_Y + FORBIDDEN_AREA_HEIGHT;

}
