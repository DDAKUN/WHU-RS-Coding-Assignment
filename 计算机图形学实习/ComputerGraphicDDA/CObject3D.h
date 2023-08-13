#pragma once
#include <afx.h>

//三维空间中点
struct Point3D {
	double x;
	double y;
	double z;
};
//三角面
struct TriSurface {
	int no;//所属景物序号
	Point3D p1, p2, p3;//三角面的顶点
	double xn, yn, zn;//三角面的法向量
};
//景物光照参数
struct Param {
	double krd;//景物表面红色光漫反射率
	double kgd;//景物表面绿色光漫反射率
	double kbd;//景物表面蓝色光漫反射率
	double kra;//景物表面红色光泛光反射率
	double kga;//景物表面绿色光泛光反射率
	double kba;//景物表面蓝色光泛光反射率
	double krs;//景物表面红色光镜面反射率
	double kgs;//景物表面绿色光镜面反射率
	double kbs;//景物表面蓝光镜面反射率
	int n;//景物表面镜面高光指数
};

class CObject3D :
    public CObject
{
public:
	//球体表面三角剖分后得到的三角面列表
	CArray<TriSurface, TriSurface> m_SurfaceList;
	Param m_Param;//球体表面光照参数
	Point3D p3d[101][101];//球体表面参数点数组
	int countx, county;//生成的参数点在经度和纬度上的数量
	double bx, by, bz;//圆心坐标
public:
	//创建指定球心和半径的球体
	void CreateBall(double x0, double y0, double z0, double r);
	void SetSurfaceList();//对球体表面进行三角剖分
	void SetFVector(TriSurface* surface);//设置三角面的法向量
	void SetParam(Param param);//设置球体表面光照参数

};

