#ifndef HG_USERLAYWARNING_H_
#define HG_USERLAYWARNING_H_

class hgUserLayWarning//区域警报参数
{
public:
	hgUserLayWarning(void);
    ~hgUserLayWarning(void);

    void InitAllData();

public:
    int enter_time;//入侵时长
    double enter_speed ;
    int leave_time;//离开
    double leave_speed;
    int inside_time;//内部
    double inside_speed;
    int outside_time;//外部
    double outside_speed;
    int high_duration;//高速
    double high_speed;
    int low_duration;//低速
    double low_speed;
    int pro_duration;//禁锚
    double pro_lat;
    double pro_lon;
    QList<QString>  anc_type;//抛锚
    double add_max;//加速度m/s2
    double add_min;
    double add_duration;
    double col_cpa;//碰撞
    double col_tcpa;
    double col_dcpa;
    double col_dist;
    int con_time;//拥挤
    int con_total;
    double gro_depth;//搁浅
    int gro_time;
    int app_time;//接近
    int cou_change;//航向突变
    int cou_time;
    time_t m_FogBeginTime;
    time_t m_FogEndTime;
    int m_FogTime;
    QVector < QString > m_FogMMSI;
};

#endif //HG_DATAMANAGER_H_