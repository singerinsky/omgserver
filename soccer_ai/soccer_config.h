#ifndef _SOCCER_CONFIG_H_
#define _SOCCER_CONFIG_H_

#define POINT_BUFFER 10
#define SLIDE_RADIUS 20

#define AIR_ACCE 0.5
#define GRAVITY 1
#define GROUND_ACCE 0.3
#define ACTUAL_FINAL_SPEED 32. /* 球速度 */

#define GOAL_Y1 335
#define GOAL_Y2 419

#define GOAL_HEART_BEAT 25 /* 心跳秒数 */

#define TIME_SCALE 1 /* 播放速度 */

#define RUN_TO_COUNT 6 /* 传球前运球次数 */

/////////////////////////////////////////////////////////////////////////////
#define METER_TO_POINT 12

#define LATTICE_EQUAL_X 16 /* 长度等分 */
#define LATTICE_EQUAL_Y 10 /* 宽度等分 */

#define PITCH_WIDTH (111 * METER_TO_POINT) /* 球场总长度 1332 */
#define PITCH_HEIGHT (76 * METER_TO_POINT) /* 球场总宽度 912 */

#define OUTSIDE_WIDTH (3 * METER_TO_POINT) /* 安全边界（真正球场大小开始坐标） 36 */
#define OUTSIDE_HEIGHT (3 * METER_TO_POINT) /* 安全边界（真正球场大小开始坐标） 36 */

#define PENALTY_LOCATION (11 * METER_TO_POINT) /* 点球点距离球门中心距离 */

#define GOAL_WIDTH (7.32 * METER_TO_POINT) /* 球门宽度 */

 /* 大禁区 */
#define FORBIDDEN_AREA_WIDTH (16.5 * METER_TO_POINT)
#define FORBIDDEN_AREA_HEIGHT (GOAL_WIDTH + 2 * FORBIDDEN_AREA_WIDTH)

 /* 小禁区 */
#define GOAL_AREA_WIDTH (5.5 * METER_TO_POINT)
#define GOAL_AREA_HEIGHT (GOAL_WIDTH + 2 * GOAL_AREA_WIDTH)
////////////////////////////////////////////////////////////////////////////
// A 左边 B 右边

/* A 球门 中心 坐标 */
#define A_GOAL_WIDTH (OUTSIDE_WIDTH)
#define A_GOAL_HEIGHT (PITCH_HEIGHT / 2)

/* B 球门 中心 坐标 */
#define B_GOAL_WIDTH (PITCH_WIDTH - OUTSIDE_WIDTH)
#define B_GOAL_HEIGHT (PITCH_HEIGHT / 2)

/* A 点球 坐标 */
#define A_PENALTY_LOCATION_X (A_GOAL_WIDTH + PENALTY_LOCATION)
#define A_PENALTY_LOCATION_Y (PITCH_HEIGHT / 2)

/* B 点球 坐标 */
#define B_PENALTY_LOCATION_X (B_GOAL_WIDTH - PENALTY_LOCATION)
#define B_PENALTY_LOCATION_Y (PITCH_HEIGHT / 2)

/* A 球门 坐标 */
#define A_GOAL_WIDTH_X_1 (A_GOAL_WIDTH)
#define A_GOAL_WIDTH_Y_1 (A_GOAL_HEIGHT - GOAL_WIDTH / 2)
#define A_GOAL_WIDTH_X_2 (A_GOAL_WIDTH)
#define A_GOAL_WIDTH_Y_2 (A_GOAL_HEIGHT + GOAL_WIDTH / 2)

/* B 球门 坐标 */
#define B_GOAL_WIDTH_X_1 (B_GOAL_WIDTH)
#define B_GOAL_WIDTH_Y_1 (B_GOAL_HEIGHT - GOAL_WIDTH / 2)
#define B_GOAL_WIDTH_X_2 (B_GOAL_WIDTH)
#define B_GOAL_WIDTH_Y_2 (B_GOAL_HEIGHT + GOAL_WIDTH / 2)

/* A 小禁区 */
#define A_GOAL_AREA_X (A_GOAL_WIDTH + GOAL_AREA_WIDTH)
#define A_GOAL_AREA_Y (A_GOAL_HEIGHT - GOAL_AREA_HEIGHT / 2)

/* B 小禁区 */
#define B_GOAL_AREA_X (B_GOAL_WIDTH - GOAL_AREA_WIDTH)
#define B_GOAL_AREA_Y (B_GOAL_HEIGHT - GOAL_AREA_HEIGHT / 2)

/* A 大禁区 */
#define A_FORBIDDEN_AREA_X (A_GOAL_WIDTH + FORBIDDEN_AREA_WIDTH)
#define A_FORBIDDEN_AREA_Y (A_GOAL_HEIGHT - FORBIDDEN_AREA_HEIGHT / 2)

/* B 大禁区 */
#define B_FORBIDDEN_AREA_X (B_GOAL_WIDTH - FORBIDDEN_AREA_WIDTH)
#define B_FORBIDDEN_AREA_Y (B_GOAL_HEIGHT - FORBIDDEN_AREA_HEIGHT / 2)

/* 格子的大小 */
#define LATTICE_SIZE_X ((PITCH_WIDTH - OUTSIDE_WIDTH * 2) / LATTICE_EQUAL_X)
#define LATTICE_SIZE_Y ((PITCH_HEIGHT - OUTSIDE_HEIGHT * 2) / LATTICE_EQUAL_Y)

/* 球场中心 */
#define STADIUM_CENTER_WIDTH (PITCH_WIDTH / 2)
#define STADIUM_CENTER_HEIGHT (PITCH_HEIGHT / 2)

#define STADIUM_CENTER_CIRCLE 9.15 * METER_TO_POINT

/* 球队防守的最后的一道线的X坐标，deadline */
#define DEFEND_LINE	B_FORBIDDEN_AREA_X - 50

#define DEFEND_LINE_SEC 65.5 * METER_TO_POINT

#define DEFEND_LINE_THR 83 * METER_TO_POINT

/* 中圈弧A */
#define MIDDLE_CIRCLE_A PITCH_WIDTH / 2 - 9.15 * 12;

/* 中圈弧B */
#define MIDDLE_CIRCLE_B PITCH_WIDTH / 2 + 9.15 * 12

#define PITCH_SAFE_WIDTH 15.
#define PITCH_SAFE_HEIGHT 15.

const int HOME_TEAM_ID = 10;
const int AWAY_TEAM_ID = 50;

const double pos_x_array[] = {4, 	4, 		3.5, 	4, 		4,
	   		 	 	 	 	  4, 	4, 		4.5, 	5, 		5,
	   		 	 	 	 	  7.5, 	7.5, 	7, 		7.5, 	7.5,
	   		 	 	 	 	  8.5, 	9, 		9, 		9, 		8.5,
	   		 	 	 	 	  9.7, 	10.5, 	10.5, 	10.5, 	9.7,
	   		 	 	 	 	  11.5, 12.5, 	12.5, 	12.5, 	11.5,
	   		 	 	 	 	  13.5, 13.5, 	13.5, 	13.5, 	13.5};

const double pos_y_array[] = {1.5,	3.0,	5,	7,		8.5,
	    					  1.5,	3.0,	5,	7,		8.5,
	    					  1.5,	3.0,	5,	7,		8.5,
	    					  1.5,	3.0,	5,	7,		8.5,
	    					  1.5,	3.0,	5,	7,		8.5,
	    					  1,	3.0,	5,	7,		9,
	    					  1,	2.7,	5,	7.3,	9};

const double kick_off_player_pos_x[] = {14,	 14, 14, 14,  9,   11.5, 11.5, 9,   8.1, 8.1};
const double kick_off_player_pos_y[] = {1.5, 3,  7,  8.5, 1.5, 3,    7,    8.5, 4,   6};

const double kick_off_def_player_pos_x[] = {14,14,14,14,9,11.5,11.5,9,8,7.9};
const double kick_off_def_player_pos_y[] = {1.5,3,7,8.5,1.5,3,7,8.5,3,7};
const double kick_off_region_1[] = {7.9,1,8.1,9};
const double kick_off_region_2[] = {6,4,8,6};
const double kick_off_region_3[] = {4,4,5.5,6};

const int cond_table[] = {30,30,32,34,35,36,38,39,40,41,42
						,43,44,45,46,47,48,49,49,50,51,52
						,53,54,54,55,56,57,57,58,59,60,60
						,61,62,62,63,64,65,65,66,67,67,68
						,69,69,70,70,71,72,72,73,74,74,75
						,75,76,77,77,78,78,79,80,80,81,81
						,82,83,83,84,84,85,85,86,87,87,88
						,88,89,89,90,90,91,91,92,93,93,94
						,94,95,95,96,96,97,97,98,98,99,99
						,100,100};

/*const int penalyt_table_a[] = {};
const int penalyt_table_b[] = {};*/

const int config_tier_rating[] = {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,
								  2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,
								  4,4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,
								  6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,
								  8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,
								  10,10,10,10,10,10,10,10};

//////////////////////////////////////////////////////////////////
#define keep_distance_to_player 50


#endif /* _SOCCER_CONFIG_H_ */
