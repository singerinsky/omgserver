#include "../common/head.h"

using namespace std;
//	using namespace std::tr1;

double speed_refer_table[101];

void speed_refer_table_init(void)
{
    for (int i = 0; i <= 100; ++i)
    {	//计算球场里面的所有的映射表
        double v = 100. / (-0.0005891 * i * i + i * 0.01147 + 14.94) / 0.0525 * 0.05;
        speed_refer_table[i] = v;
    }
}

double speed_refer_table_get(int speed)
{
    if ((speed < 0))
    {
        return 0;
    }
    if(speed > 100){
    	speed = 100;
    }

    return speed_refer_table[speed];
}

double acceleration_refer_table_get(int attr)
{
    return attr*0.1;
}
