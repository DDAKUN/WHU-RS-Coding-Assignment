#include "pch.h"
#include "CReality.h"

CReality::CReality()
{
	//��ʼ����������
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
		//�����ӵ㷽����治�ɼ�
		if (GetVectorPM(surface.xn, surface.yn, surface.zn, lxn, lyn, lzn) >= 0)
		{
			surface.no = m_count;//���õ�ǰ���Ӧ�Ĺ��ղ���
			m_SurfaceList.Add(surface);
		}
	}
	//���þ������
	m_ParamList.Add(pObject->m_Param);
}

void CReality::AddLight(LightParam lightParam)
{
	//�������˥��
	double f = 1.0 / (lightParam.c1 + lightParam.c2 * lightParam.m_distance +
		lightParam.c3 * lightParam.m_distance * lightParam.m_distance);
	if (f <= 0 || f > 1)
		f = 1.0;
	lightParam.f = f;
	//��ӵ���Դ�б���
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

//Lambert���������ģ��
void CReality::Lambert(CDC* pDC)
{
	int no = 0;
	//�����������ɫ�����ķ��ⷴ���ʺ���������
	double kra, kga, kba, krd, kgd, kbd;
	double cosnl;//������浥λ������������ⵥλ������нǵ�����ֵ
	double ird, igd, ibd;//������������淴�������ɫ��ǿ��
	//ѭ������ÿһ��������
	for (int i = 0;i < m_SurfaceList.GetSize();i++)
	{
		//��þ������������
		TriSurface surface = (TriSurface)m_SurfaceList.GetAt(i);
		//��õ�ǰ����Ĳ���
		if (no != surface.no)
		{
			no = surface.no;
			Param param = (Param)m_ParamList.GetAt(no - 1);
			kra = param.kra;kga = param.kga;kba = param.kba;
			krd = param.krd;kgd = param.kgd;kbd = param.kbd;
		}
		//���㾰����������淴�������ɫ��ǿ��
		ird = ira * kra;igd = iga * kga;ibd = iba * kba;
		//ѭ����Դ�б�
		for (int j = 0;j < m_LightList.GetSize();j++)
		{
			//��ù�Դ����
			LightParam light = (LightParam)m_LightList.GetAt(j);
			//���㾰����浥λ������������ⵥλ������нǵ�����ֵ
			cosnl = GetVectorPM(surface.xn, surface.yn, surface.zn,
				light.xn, light.yn, light.zn);
			//�ۼӼ��㾰������ڶ����Դ�����µ�����ɫ������ǿ��
			ird = ird + light.f * krd * light.irl * cosnl;
			igd = igd + light.f * kgd * light.igl * cosnl;
			ibd = ibd + light.f * kbd * light.ibl * cosnl;
		}
		if (ird < 0) ird = 0;if (ird > 255) ird = 255;
		if (igd < 0) igd = 0;if (igd > 255) igd = 255;
		if (ibd < 0) ibd = 0;if (ibd > 255) ibd = 255;
		//�����������ͶӰ
		CPoint p[3];
		p[0] = Projection(surface.p1);
		p[1] = Projection(surface.p2);
		p[2] = Projection(surface.p3);
		//����������
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
	//�����������ɫ�����ķ��ⷴ����
	double kra, kga, kba;
	//�����������ɫ��������������
	double krd, kgd, kbd;
	//������������ɫ�����ľ��淴����
	double krs, kgs, kbs;
	//����߹�ָ��
	int n;
	//���뾵�淨����
	double hxn, hyn, hzn;
	double cosnl;//������浥λ������������ⵥλ������нǵ�����ֵ
	double cosnh;//������浥λ�����������뾵�淨�����нǵ�����ֵ
	double ird, igd, ibd;//������������淴�������ɫ��ǿ��
	//ѭ������ÿһ��������
	for (int i = 0;i < m_SurfaceList.GetSize();i++)
	{
		//��þ������������
		TriSurface surface = (TriSurface)m_SurfaceList.GetAt(i);
		//��õ�ǰ����Ĳ���
		if (no != surface.no)
		{
			no = surface.no;
			Param param = (Param)m_ParamList.GetAt(no - 1);
			kra = param.kra;kga = param.kga;kba = param.kba;
			krd = param.krd;kgd = param.kgd;kbd = param.kbd;
			krs = param.krs;kgs = param.kgs;kbs = param.kbs;
			n = param.n;
		}
		//���㾰����������淴�������ɫ��ǿ��
		ird = ira * kra;igd = iga * kga;ibd = iba * kba;
		//ѭ����Դ�б�
		for (int j = 0;j < m_LightList.GetSize();j++)
		{
			//��ù�Դ����
			LightParam light = (LightParam)m_LightList.GetAt(j);
			//���㾰����浥λ������������ⵥλ������нǵ�����ֵ
			cosnl = GetVectorPM(surface.xn, surface.yn, surface.zn,
				light.xn, light.yn, light.zn);
			//�������뾵�淨����
			hxn = (light.xn + lxn) / 2;hyn = (light.yn + lyn) / 2;hzn = (light.zn + lzn) / 2;
			//���㾰����浥λ�����������뾵�淨�����нǵ�����ֵ
			cosnh = GetVectorPM(surface.xn, surface.yn, surface.zn,
				hxn, hyn, hzn);
			cosnh = pow(cosnh, n);//����cosnh��n����
			//�ۼӼ��㾰������ڶ����Դ�����µ�����ɫ������ǿ��
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
		//�����������ͶӰ
		CPoint p[3];
		p[0] = Projection(surface.p1);
		p[1] = Projection(surface.p2);
		p[2] = Projection(surface.p3);
		//����������
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
