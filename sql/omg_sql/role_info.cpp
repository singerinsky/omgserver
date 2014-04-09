#include "role_info.h" 

role_info::role_info()
{
    role_id = 0;
    uid = 0;
    tid = 0;
    gender = 0;
    job_type = 0;
    role_level = 0;
    role_exp = 0;
    costume_tid = 0;
    title = 0;
    coin = 0;
    coupon = 0;
    diamond = 0;
    vip_end_ts = 0;
    vip_level = 0;
    map_id = 0;
    map_x = 0;
    map_y = 0;
    last_map_id = 0;
    last_map_x = 0;
    last_map_y = 0;
    flag = 0;
    status = 0;
    server_id = 0;
    create_time = 0;
    team_id = 0;
    team_create_time = 0;
    bag_size = 0;
    depot_size = 0;
    buddy_size = 0;
    lineup_size = 0;
    default_lineup_id = 0;
    lineup_capacity = 0;
    login_time = 0;
    last_logoff_time = 0;
    instance_count = 0;
    instance_time = 0;
    guild_id = 0;
    guild_time = 0;
    phy_strength = 0;
    extra_phy_strength = 0;
    time_to_recover_phy_strength = 0;
    time_to_recover_extra_phy_strength = 0;
    renown = 0;
    memset(dirty,1,sizeof(dirty));
}
void role_info::load(const char** data)
{
    role_id = (int32_t)atoi(data[0]);
    uid = (int32_t)atoi(data[1]);
    tid = (int32_t)atoi(data[2]);
    name.assign(data[3]);
    gender = (int8_t)atoi(data[4]);
    job_type = (int8_t)atoi(data[5]);
    role_level = (int8_t)atoi(data[6]);
    role_exp = (int32_t)atoi(data[7]);
    costume_tid = (int32_t)atoi(data[8]);
    title = (int32_t)atoi(data[9]);
    coin = (int32_t)atoi(data[10]);
    coupon = (int32_t)atoi(data[11]);
    diamond = (int32_t)atoi(data[12]);
    vip_end_ts = (int32_t)atoi(data[13]);
    vip_level = (int8_t)atoi(data[14]);
    map_id = (int16_t)atoi(data[15]);
    map_x = (int16_t)atoi(data[16]);
    map_y = (int16_t)atoi(data[17]);
    last_map_id = (int16_t)atoi(data[18]);
    last_map_x = (int16_t)atoi(data[19]);
    last_map_y = (int16_t)atoi(data[20]);
    flag = (int16_t)atoi(data[21]);
    status = (int8_t)atoi(data[22]);
    server_id = (int32_t)atoi(data[23]);
    create_time = (int32_t)atoi(data[24]);
    team_id = (int32_t)atoi(data[25]);
    team_create_time = (int32_t)atoi(data[26]);
    bag_size = (int16_t)atoi(data[27]);
    depot_size = (int16_t)atoi(data[28]);
    buddy_size = (int8_t)atoi(data[29]);
    lineup_size = (int8_t)atoi(data[30]);
    default_lineup_id = (int32_t)atoi(data[31]);
    lineup_capacity = (int32_t)atoi(data[32]);
    login_time = (int32_t)atoi(data[33]);
    last_logoff_time = (int32_t)atoi(data[34]);
    login_ip.assign(data[35]);
    instance_count = (int32_t)atoi(data[36]);
    instance_time = (int32_t)atoi(data[37]);
    guild_id = (int32_t)atoi(data[38]);
    guild_time = (int32_t)atoi(data[39]);
    guild_name.assign(data[40]);
    phy_strength = (int32_t)atoi(data[41]);
    extra_phy_strength = (int32_t)atoi(data[42]);
    time_to_recover_phy_strength = (int32_t)atoi(data[43]);
    time_to_recover_extra_phy_strength = (int32_t)atoi(data[44]);
    renown = (int32_t)atoi(data[45]);
    memset(dirty,0,sizeof(dirty));
}
void role_info::load(const vector<string>& data)
{
    role_id = (int32_t)atoi(data[0].c_str());
    uid = (int32_t)atoi(data[1].c_str());
    tid = (int32_t)atoi(data[2].c_str());
    name.assign(data[3].c_str());
    gender = (int8_t)atoi(data[4].c_str());
    job_type = (int8_t)atoi(data[5].c_str());
    role_level = (int8_t)atoi(data[6].c_str());
    role_exp = (int32_t)atoi(data[7].c_str());
    costume_tid = (int32_t)atoi(data[8].c_str());
    title = (int32_t)atoi(data[9].c_str());
    coin = (int32_t)atoi(data[10].c_str());
    coupon = (int32_t)atoi(data[11].c_str());
    diamond = (int32_t)atoi(data[12].c_str());
    vip_end_ts = (int32_t)atoi(data[13].c_str());
    vip_level = (int8_t)atoi(data[14].c_str());
    map_id = (int16_t)atoi(data[15].c_str());
    map_x = (int16_t)atoi(data[16].c_str());
    map_y = (int16_t)atoi(data[17].c_str());
    last_map_id = (int16_t)atoi(data[18].c_str());
    last_map_x = (int16_t)atoi(data[19].c_str());
    last_map_y = (int16_t)atoi(data[20].c_str());
    flag = (int16_t)atoi(data[21].c_str());
    status = (int8_t)atoi(data[22].c_str());
    server_id = (int32_t)atoi(data[23].c_str());
    create_time = (int32_t)atoi(data[24].c_str());
    team_id = (int32_t)atoi(data[25].c_str());
    team_create_time = (int32_t)atoi(data[26].c_str());
    bag_size = (int16_t)atoi(data[27].c_str());
    depot_size = (int16_t)atoi(data[28].c_str());
    buddy_size = (int8_t)atoi(data[29].c_str());
    lineup_size = (int8_t)atoi(data[30].c_str());
    default_lineup_id = (int32_t)atoi(data[31].c_str());
    lineup_capacity = (int32_t)atoi(data[32].c_str());
    login_time = (int32_t)atoi(data[33].c_str());
    last_logoff_time = (int32_t)atoi(data[34].c_str());
    login_ip.assign(data[35].c_str());
    instance_count = (int32_t)atoi(data[36].c_str());
    instance_time = (int32_t)atoi(data[37].c_str());
    guild_id = (int32_t)atoi(data[38].c_str());
    guild_time = (int32_t)atoi(data[39].c_str());
    guild_name.assign(data[40].c_str());
    phy_strength = (int32_t)atoi(data[41].c_str());
    extra_phy_strength = (int32_t)atoi(data[42].c_str());
    time_to_recover_phy_strength = (int32_t)atoi(data[43].c_str());
    time_to_recover_extra_phy_strength = (int32_t)atoi(data[44].c_str());
    renown = (int32_t)atoi(data[45].c_str());
    memset(dirty,0,sizeof(dirty));
}
int role_info::sql_key(char* buf,int size) const
{
    int origin_size = size ,len = 0; 
    len =sql_role_id(buf,size);
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
int role_info::sql_data(char* buf,int size,bool check_dirty) const
{
    int origin_size = size,len=0 ; 
    int first_flag = 1 ; 
    if((!check_dirty) || dirty[0])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_role_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[1])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_uid(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[2])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_tid(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[3])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_name(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[4])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_gender(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[5])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_job_type(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[6])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_role_level(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[7])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_role_exp(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[8])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_costume_tid(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[9])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_title(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[10])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_coin(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[11])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_coupon(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[12])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_diamond(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[13])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_vip_end_ts(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[14])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_vip_level(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[15])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_map_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[16])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_map_x(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[17])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_map_y(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[18])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_last_map_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[19])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_last_map_x(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[20])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_last_map_y(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[21])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_flag(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[22])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_status(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[23])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_server_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[24])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_create_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[25])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_team_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[26])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_team_create_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[27])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_bag_size(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[28])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_depot_size(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[29])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_buddy_size(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[30])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_lineup_size(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[31])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_default_lineup_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[32])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_lineup_capacity(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[33])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_login_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[34])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_last_logoff_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[35])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_login_ip(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[36])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_instance_count(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[37])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_instance_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[38])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_guild_id(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[39])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_guild_time(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[40])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_guild_name(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[41])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_phy_strength(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[42])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_extra_phy_strength(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[43])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_time_to_recover_phy_strength(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[44])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_time_to_recover_extra_phy_strength(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    if((!check_dirty) || dirty[45])
    {
        if(first_flag==0) {memcpy(buf,",",1); buf+= 1 ; size-= 1 ;}
        len =sql_renown(buf,size);
        buf += len ; size -= len ;first_flag=0;
    }
    return origin_size - size ; 
} 
int role_info::sql_query(char* buf,int size) const
{
    int origin_size = size ,len=0; 
    len = snprintf(buf,size,"select * from role_info where ");
    buf += len ; size -= len ;
    len = sql_key(buf,size) ;
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
int role_info::sql_insert(char* buf,int size) const
{
    int origin_size = size,len=0 ; 
    len = snprintf(buf,size,"insert into role_info set ");
    buf += len ; size -= len ;
    len = sql_data(buf,size,false) ;
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
int role_info::sql_replace(char* buf,int size) const
{
    int origin_size = size,len=0 ; 
    len = snprintf(buf,size,"replace into role_info set ");
    buf += len ; size -= len ;
    len = sql_data(buf,size,false) ;
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
int role_info::sql_update(char* buf,int size) const
{
    int origin_size = size,len=0 ; 
    len = snprintf(buf,size,"update role_info set ");
    buf += len ; size -= len ;
    len = sql_data(buf,size,true) ;
    buf += len ; size -= len ;
    memcpy(buf," where ",7); buf+= 7 ; size-= 7 ;
    len = sql_key(buf,size) ;
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
int role_info::sql_delete(char* buf,int size) const
{
    int origin_size = size ,len=0; 
    len = snprintf(buf,size,"delete from role_info where ");
    buf += len ; size -= len ;
    len = sql_key(buf,size) ;
    buf += len ; size -= len ;
    return origin_size - size ; 
} 
