#pragma once
#include "CObject3D.h"
struct LightParam {
	double m_distance;//光源距离
	double c1;//距离衰减系数c1
	double c2;//距离衰减系数c2
	double c3;//距离衰减系数c3
	double irl;//入射光红颜色分量强度
	double igl;//入射光绿颜色分量强度
	double ibl;//入射光蓝颜色分量强度
	double xn, yn, zn;//入射单位方向向量
	double f;//距离衰减
};

class CReality
{
public:
	CArray<TriSurface, TriSurface> m_SurfaceList;//景物表面三角面列表
	CArray<Param, Param> m_ParamList;//景物表面参数列表
	CArray<LightParam, LightParam> m_LightList;//光源参数列表
	double lxn, lyn, lzn;//视点向量
	int m_count;//景物数量
	double ira;//泛光中红色光分量的强度
	double iga;//泛光中绿色光分量的强度
	double iba;//泛光中蓝色光分量的强度
public:
	CReality();
	void AddObject3D(CObject3D* pObject);//添加景物
	void AddLight(LightParam lightParam);//添加光源
	//设置泛光强度
	void SetIA(double r, double g, double b);
	//计算传入两个向量夹角余弦值
	double GetVectorPM(double xn1, double yn1, double zn1, double xn2, double yn2, double zn2);
	//计算投影点
	CPoint Projection(Point3D point3d);
	//Lambert漫反射光照模型实现函数
	void Lambert(CDC* pDC);
	void Phong(CDC* pDC);
	void Clear();//清除当前景物和光源

};

