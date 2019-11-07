#include "stdafx.h"
#include<math.h>
#include "hgPlaneProjection.h"
CPlaneProjection::CPlaneProjection(void)
{
	my_fOrigin[0] = 0.0;         // lat.  [rad]
	my_fOrigin[1] = 0.0;         // long. [rad]
	my_fEarthRadius = 6366707.0; // [m]
} // constructor

CPlaneProjection::~CPlaneProjection(void)
{
}

//////////////////////////////////////////////////////////////////////////
//--- Earth parameters

//! Set location where tangent plane touches the Earth
/*!
* @param fOrigin  Location where tangent plane touches the Earth (lat,long). [rad]
*/
void CPlaneProjection::set_origin(double fOrigin[])
{
	for(int i=0; i<2; ++i)
		my_fOrigin[i] = fOrigin[i];
}

//! Get location where tangent plane touches the Earth
/*!
* @param fOrigin  Location where tangent plane touches the Earth (lat,long). [rad]
*/
void CPlaneProjection::get_origin(double fOrigin[])
{
	for(int i=0; i<2; ++i)
		fOrigin[i] = my_fOrigin[i];
}

//////////////////////////////////////////////////////////////////////////
//--- Projection

//! Projection from Earth to	
/*!
* @param fLatLong  Point on Earth. (lat,long). [rad]
* @param fXY       Point on tangent plane. [m]
*/
void CPlaneProjection::llxy(double fLatLong[], double fXY[])
{
	double dlat ;
	double dlng ;

	dlat = fLatLong[0] - my_fOrigin[0];
	dlng = fLatLong[1] - my_fOrigin[1];

	fXY[0] = my_fEarthRadius * (dlat + .5 * sin(fLatLong[0])*cos(fLatLong[0]) * dlng*dlng) ;
	fXY[1] = my_fEarthRadius * cos(fLatLong[0]) *dlng ;
} // llxy

//! Projection from tangent plane to Earth
/*!
* @param fXY       Point on tangent plane. [m]
* @param fLatLong  Point on Earth. (lat,long). [rad]
*/
void CPlaneProjection::xyll(double fXY[], double fLatLong[])
{
#define EPS   (.001/my_fEarthRadius) // stop within 1 mm

	double a ;
	double b ;
	double dlat ;
	int    count ;

	//cout << "my_fOrigin[0] = " << my_fOrigin[0] << endl;
	fLatLong[0] = my_fOrigin[0];

	a = my_fOrigin[0] + fXY[0] /my_fEarthRadius;
	b = 0.5 * (fXY[1]/my_fEarthRadius) * (fXY[1]/my_fEarthRadius);

	count = 0;

	do {

		dlat  = - (fLatLong[0] + b * tan(fLatLong[0]) - a) 
			/ (1. + b/(cos(fLatLong[0])*cos(fLatLong[0])));

		fLatLong[0] = fLatLong[0] + dlat;

		++count;

	} while (fabs(dlat) > EPS);

	fLatLong[1] = my_fOrigin[1] + fXY[1] / my_fEarthRadius / cos(fLatLong[0]);

	//cout << "Count in sl " << count << "\n" ;

} // xyll

//船体坐标系逆时针旋转alfa=heading到正北坐标系
//外部处理使用弧度
void CPlaneProjection::xyToLL(double alfa,double fOriLL[],double fXY[], double fLatLong[])
{
	/*alfa=alfa*PI/180.0;
	for (int i=0;i<2;i++)
	{
		fOriLL[i]=fOriLL[i]*PI/180.0;
	}*/
	set_origin(fOriLL);
	double fXYNorth[2]={0.0};
	//V=V*M
	// hzxie [4/22/2014 ]
	//fXYNorth[0]=cos(alfa)*fXY[0]+sin(alfa)*fXY[1];
	fXYNorth[0]=cos(alfa)*fXY[0]-sin(alfa)*fXY[1];
	//fXYNorth[1]=-sin(alfa)*fXY[0]+cos(alfa)*fXY[1];
	fXYNorth[1]=sin(alfa)*fXY[0]+cos(alfa)*fXY[1];
	xyll(fXYNorth,fLatLong);
	//for(int i=0;i<2;i++)
	//{
	//	fLatLong[i]=fLatLong[i]*180.0/PI;
	//	//将所引用的的数据还原成角度经纬度
	//	fOriLL[i]=fOriLL[i]*180.0/PI;
	//}
}
//正北坐标系顺时针旋转alfa=heading到船体坐标系
void CPlaneProjection::llToXY(double alfa,double fOriLL[],double fLatLong[], double fXY[])
{
	//alfa=alfa*PI/180.0;
	//for (int i=0;i<2;i++)
	//{
	//	fOriLL[i]=fOriLL[i]*PI/180.0;
	//}
	double fXYNorth[2]={0.0};
	set_origin(fOriLL);
	/*for(int i=0;i<2;i++)
	{
	fLatLong[i]=fLatLong[i]*PI/180.0;
	}*/
	llxy(fLatLong,fXYNorth);
	//此时得到的fXYNorth坐标是正北笛卡尔坐标系下坐标，还需要转到本船坐标系
	// hzxie [4/22/2014 ]
	fXY[0]=cos(alfa)*fXYNorth[0]+sin(alfa)*fXYNorth[1];
	fXY[1]=-sin(alfa)*fXYNorth[0]+cos(alfa)*fXYNorth[1];
	//for (int i=0;i<2;i++)
	//{
	//	//还原成角度经纬度
	//	fOriLL[i]=fOriLL[i]*180.0/PI;
	//	fLatLong[i]=fLatLong[i]*180.0/PI;
	//}
}
// hzxie [4/22/2014 ]
//hzxie以下变换仅适用于y-x坐标系，y水平向右，x垂直向上
/****************************************************************
y-x坐标系下，正北笛卡尔坐标系顺时针旋转a=heading到船体坐标系旋转矩阵(区别于x-y坐标系)
												[cosa,-sina]
船体坐标系下任意点[x,y]=[x0,y0]*                                 [x0,y0]为正北坐标系下任意点
												[sina,  cosa]
*****************************************************************/

/****************************************************************
y-x坐标系下，船体坐标系逆时针旋转a=heading到正北笛卡尔坐标系
												[cosa, sina]
正北笛卡尔坐标系下[x,y]=[x0,y0]*                                [x0,y0]为船体坐标系下任一点
												[-sina, cosa]
*****************************************************************/