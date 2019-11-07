#ifndef PLANEPROJECTION_H
#define PLANEPROJECTION_H
//const double PI=3.1415926;
#ifndef PI
#define  PI 3.1415926
#endif

class CPlaneProjection
{
public:
	//! @name construction
	//! @{
	CPlaneProjection(void);
	~CPlaneProjection(void);
	//! @}

public:
	//! @name Earth parameters
	//! @{

	void set_origin(double fOrigin[]);
	void get_origin(double fOrigin[]);
	//! @}

public:
	//! @name Projection
	//! @{

	void llxy(double fLatLong[], double fXY[]);
	void xyll(double fXY[], double fLatLong[]);

	//! @}

protected:
	//! @name Earth parameters
	//! @{

	//! Origin of tangent plane
	/*!  
	* @li Unit: rad
	*/
	double my_fOrigin[2];

	//! Earth radius
	/*!
	* @li Unit: [m]
	*/
	double my_fEarthRadius;
public:
//增加接口,以经纬度为参数，返回经纬度（统一弧度）
	void xyToLL(double alfa,double fOriLL[],double fXY[], double fLatLong[]);
	void llToXY(double alfa,double fOriLL[],double fLatLong[], double fXY[]);
	//! @}
};
#endif