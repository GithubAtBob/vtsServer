#ifndef HG_USERLAYWARNING_H_
#define HG_USERLAYWARNING_H_

class hgUserLayWarning//���򾯱�����
{
public:
	hgUserLayWarning(void);
    ~hgUserLayWarning(void);

    void InitAllData();

public:
    int enter_time;//����ʱ��
    double enter_speed ;
    int leave_time;//�뿪
    double leave_speed;
    int inside_time;//�ڲ�
    double inside_speed;
    int outside_time;//�ⲿ
    double outside_speed;
    int high_duration;//����
    double high_speed;
    int low_duration;//����
    double low_speed;
    int pro_duration;//��ê
    double pro_lat;
    double pro_lon;
    QList<QString>  anc_type;//��ê
    double add_max;//���ٶ�m/s2
    double add_min;
    double add_duration;
    double col_cpa;//��ײ
    double col_tcpa;
    double col_dcpa;
    double col_dist;
    int con_time;//ӵ��
    int con_total;
    double gro_depth;//��ǳ
    int gro_time;
    int app_time;//�ӽ�
    int cou_change;//����ͻ��
    int cou_time;
    time_t m_FogBeginTime;
    time_t m_FogEndTime;
    int m_FogTime;
    QVector < QString > m_FogMMSI;
};

#endif //HG_DATAMANAGER_H_