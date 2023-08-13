#pragma once
#include "CObject3D.h"
struct LightParam {
	double m_distance;//��Դ����
	double c1;//����˥��ϵ��c1
	double c2;//����˥��ϵ��c2
	double c3;//����˥��ϵ��c3
	double irl;//��������ɫ����ǿ��
	double igl;//���������ɫ����ǿ��
	double ibl;//���������ɫ����ǿ��
	double xn, yn, zn;//���䵥λ��������
	double f;//����˥��
};

class CReality
{
public:
	CArray<TriSurface, TriSurface> m_SurfaceList;//��������������б�
	CArray<Param, Param> m_ParamList;//�����������б�
	CArray<LightParam, LightParam> m_LightList;//��Դ�����б�
	double lxn, lyn, lzn;//�ӵ�����
	int m_count;//��������
	double ira;//�����к�ɫ�������ǿ��
	double iga;//��������ɫ�������ǿ��
	double iba;//��������ɫ�������ǿ��
public:
	CReality();
	void AddObject3D(CObject3D* pObject);//��Ӿ���
	void AddLight(LightParam lightParam);//��ӹ�Դ
	//���÷���ǿ��
	void SetIA(double r, double g, double b);
	//���㴫�����������н�����ֵ
	double GetVectorPM(double xn1, double yn1, double zn1, double xn2, double yn2, double zn2);
	//����ͶӰ��
	CPoint Projection(Point3D point3d);
	//Lambert���������ģ��ʵ�ֺ���
	void Lambert(CDC* pDC);
	void Phong(CDC* pDC);
	void Clear();//�����ǰ����͹�Դ

};

