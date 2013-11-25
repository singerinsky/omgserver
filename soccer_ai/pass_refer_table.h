#ifndef _PASS_REFER_TABLE_H_
#define _PASS_REFER_TABLE_H_

struct CrossReferItem
{
    double speed_init;
    double speed_init_z;
    double head_distance_percent;
};

struct PassReferItem
{
    double speed_init;
};

void pass_refer_table_init(void);
void cross_refer_table_init(void);

const CrossReferItem &cross_refer_get(int distance);
const PassReferItem &pass_refer_get(int distance);

#endif /* _PASS_REFER_TABLE_H_ */
