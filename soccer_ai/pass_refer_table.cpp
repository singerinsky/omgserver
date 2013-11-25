#include "../common/head.h"

#include "pass_refer_table.h"
#include "vector2d.h"
#include "soccer_config.h"

using namespace std;

static PassReferItem pass_refer_table[int(PITCH_WIDTH - OUTSIDE_WIDTH + 1)];
static CrossReferItem cross_refer_table[int(PITCH_WIDTH - OUTSIDE_WIDTH + 1)];

void pass_refer_table_init(void)
{
    for (int distance = 0; distance <= PITCH_WIDTH - OUTSIDE_WIDTH; ++distance)
    {
        pass_refer_table[distance].speed_init = sqrt(2*GROUND_ACCE * distance + pow(ACTUAL_FINAL_SPEED, 1.8));
    }
}

void cross_refer_table_init(void)
{
    for (int distance = (int)(OUTSIDE_WIDTH); distance < (int)(PITCH_WIDTH - OUTSIDE_WIDTH); ++distance)
    {
        CrossReferItem &item = cross_refer_table[distance];
        double t = sqrt(distance * 2 / GRAVITY);
        item.speed_init = distance / t;
        item.speed_init_z = distance / t;
        for (int i = (int)(t / 2); ; ++i)
        {
            double current_distance = item.speed_init * i;
            double current_z = item.speed_init_z * i - GRAVITY * pow(double(i), 2.0) / 2;
            if (current_z <= 40)
            {
                item.head_distance_percent = current_distance / distance;
                break;
            }
        }
    }
}

const CrossReferItem &cross_refer_get(int distance)
{
    if ((distance < 0) || (distance > PITCH_WIDTH - OUTSIDE_WIDTH))
    {
	LOG(ERROR)<<"ERROR...."<<distance;
    	distance = 20*METER_TO_POINT;
    }

    return cross_refer_table[distance];
}

const PassReferItem &pass_refer_get(int distance)
{
    if ((distance < 0) || (distance > PITCH_WIDTH - OUTSIDE_WIDTH))
    {
    	LOG(ERROR)<<"error "<<distance;
    	distance = 20*METER_TO_POINT;
    }

    return pass_refer_table[distance];
}
