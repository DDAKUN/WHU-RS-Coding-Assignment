#include "pch.h"
#include "CReality.h"

CReality::CReality()
{
	//初始化视线向量
	lxn = -0.45;lyn = 0;lzn = 0.9;
	m_count = 0;
	ira = 0;iga = 0;iba = 0;
}

void CReality::AddObject3D(CObject3D* pObject)
{
	m_count++;
	for (int i = 0;i < pObject->m_SurfaceList.GetSize();i++)
	{
		TriSurface surface = (TriSurface)pObject->m_SurfaceList.GetAt(i);
		//背向视点方向的面不可见
		if (GetVectorPM(surface.xn, surface.yn, surface.zn, lxn, lyn, lzn) >= 0)
		{
			surface.no = m_count;//设置当前面对应的光照参数
			m_SurfaceList.Add(surface);
		}
	}
	//设置景物参数
	m_ParamList.Add(pObject->m_Param);
}

void CReality::AddLight(LightParam lightParam)
{
	//计算距离衰减
	double f = 1.0 / (lightParam.c1 + lightParam.c2 * lightParam.m_distance +
		lightParam.c3 * lightParam.m_distance * lightParam.m_distance);
	if (f <= 0 || f > 1)
		f = 1.0;
	lightParam.f = f;
	//添加到光源列表中
	m_LightList.Add(lightParam);
}

void CReality::SetIA(double r, double g, double b)
{
	ira = r;iga = g; iba = b;
}

double CReality::GetVectorPM(double xn1, double yn1, double zn1, double xn2, double yn2, double zn2)
{
	return (xn1 * xn2 + yn1 * yn2 + zn1 * zn2) /
		(sqrt(xn1 * xn1 + yn1 * yn1 + zn1 * zn1) * sqrt(xn2 * xn2 + yn2 * yn2 + zn2 * zn2));
}

CPoint CReality::Projection(Point3D point3d)
{
	CPoint point;
	point.x = (long)(point3d.x + point3d.z * 0.5 * cos(0));
	point.y = 800 - (long)(point3d.y + point3d.z * 0.5 * sin(0));
	return point;
}

//Lambert漫反射光照模型
void CReality::Lambert(CDC* pDC)
{
	int no = 0;
	//景物表面三颜色分量的泛光反射率和漫反射率
	double kra, kga, kba, krd, kgd, kbd;
	double cosnl;//景物表面单位法向量与入射光单位向量间夹角的余弦值
	double ird, igd, ibd;//景物表面三角面反射的三颜色光强度
	//循环处理每一个三角面
	for (int i = 0;i < m_SurfaceList.GetSize();i++)
	{
		//获得景物表面三角面
		TriSurface surface = (TriSurface)m_SurfaceList.GetAt(i);
		//获得当前景物的参数
		if (no != surface.no)
		{
			no = surface.no;
			Param param = (Param)m_ParamList.GetAt(no - 1);
			kra = param.kra;kga = param.kga;kba = param.kba;
			krd = param.krd;kgd = param.kgd;kbd = param.kbd;
		}
		//计算景物表面三角面反射的三颜色光强度
		ird = ira * kra;igd = iga * kga;ibd = iba * kba;
		//循环光源列表
		for (int j = 0;j < m_LightList.GetSize();j++)
		{
			//获得光源参数
			LightParam light = (LightParam)m_LightList.GetAt(j);
			//计算景物表面单位法向量与入射光单位向量间夹角的余弦值
			cosnl = GetVectorPM(surface.xn, surface.yn, surface.zn,
				light.xn, light.yn, light.zn);
			//累加计算景物表面在多个光源照射下的三颜色分量光强度
			ird = ird + light.f * krd * light.irl * cosnl;
			igd = igd + light.f * kgd * light.igl * cosnl;
			ibd = ibd + light.f * kbd * light.ibl * cosnl;
		}
		if (ird < 0) ird = 0;if (ird > 255) ird = 255;
		if (igd < 0) igd = 0;if (igd > 255) igd = 255;
		if (ibd < 0) ibd = 0;if (ibd > 255) ibd = 255;
		//计算三角面的投影
		CPoint p[3];
		p[0] = Projection(surface.p1);
		p[1] = Projection(surface.p2);
		p[2] = Projection(surface.p3);
		//绘制三角面
		CPen pen(PS_SOLID, 1, RGB((int)ird, (int)igd, (int)ibd));
		CBrush brush(RGB((int)ird, (int)igd, (int)ibd));
		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		pDC->Polygon(p, 3);
		brush.DeleteObject();
		pen.DeleteObject();
	}
}

void CReality::Phong(CDC* pDC)
{
	int no = 0;
	//景物表面三颜色分量的泛光反射率
	double kra, kga, kba;
	//景物表面三颜色分量的漫反射率
	double krd, kgd, kbd;
	//景物表面的三颜色分量的镜面反射率
	double krs, kgs, kbs;
	//镜面高光指数
	int n;
	//理想镜面法向量
	double hxn, hyn, hzn;
	double cosnl;//景物表面单位法向量与入射光单位向量间夹角的余弦值
	double cosnh;//景物表面单位法向量与理想镜面法向量夹角的余弦值
	double ird, igd, ibd;//景物表面三角面反射的三颜色光强度
	//循环处理每一个三角面
	for (int i = 0;i < m_SurfaceList.GetSize();i++)
	{
		//获得景物表面三角面
		TriSurface surface = (TriSurface)m_SurfaceList.GetAt(i);
		//获得当前景物的参数
		if (no != surface.no)
		{
			no = surface.no;
			Param param = (Param)m_ParamList.GetAt(no - 1);
			kra = param.kra;kga = param.kga;kba = param.kba;
			krd = param.krd;kgd = param.kgd;kbd = param.kbd;
			krs = param.krs;kgs = param.kgs;kbs = param.kbs;
			n = param.n;
		}
		//计算景物表面三角面反射的三颜色光强度
		ird = ira * kra;igd = iga * kga;ibd = iba * kba;
		//循环光源列表
		for (int j = 0;j < m_LightList.GetSize();j++)
		{
			//获得光源参数
			LightParam light = (LightParam)m_LightList.GetAt(j);
			//计算景物表面单位法向量与入射光单位向量间夹角的余弦值
			cosnl = GetVectorPM(surface.xn, surface.yn, surface.zn,
				light.xn, light.yn, light.zn);
			//计算理想镜面法向量
			hxn = (light.xn + lxn) / 2;hyn = (light.yn + lyn) / 2;hzn = (light.zn + lzn) / 2;
			//计算景物表面单位法向量与理想镜面法向量夹角的余弦值
			cosnh = GetVectorPM(surface.xn, surface.yn, surface.zn,
				hxn, hyn, hzn);
			cosnh = pow(cosnh, n);//计算cosnh的n次幂
			//累加计算景物表面在多个光源照射下的三颜色分量光强度
			ird = ird + light.f * (krd * light.irl * cosnl +
				krs * light.irl * cosnh);
			igd = igd + light.f * (kgd * light.igl * cosnl +
				kgs * light.igl * cosnh);
			ibd = ibd + light.f * (kbd * light.ibl * cosnl +
				kbs * light.ibl * cosnh);
		}
		if (ird < 0) ird = 0;if (ird > 255) ird = 255;
		if (igd < 0) igd = 0;if (igd > 255) igd = 255;
		if (ibd < 0) ibd = 0;if (ibd > 255) ibd = 255;
		//计算三角面的投影
		CPoint p[3];
		p[0] = Projection(surface.p1);
		p[1] = Projection(surface.p2);
		p[2] = Projection(surface.p3);
		//绘制三角面
		CPen pen(PS_SOLID, 1, RGB((int)ird, (int)igd, (int)ibd));
		CBrush brush(RGB((int)ird, (int)igd, (int)ibd));
		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		pDC->Polygon(p, 3);
		brush.DeleteObject();
		pen.DeleteObject();
	}

}

void CReality::Clear()
{
	m_SurfaceList.RemoveAll();
	m_LightList.RemoveAll();
	m_ParamList.RemoveAll();
	m_count = 0;
}
