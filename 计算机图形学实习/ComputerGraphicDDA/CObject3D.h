#pragma once
#include <afx.h>

//��ά�ռ��е�
struct Point3D {
	double x;
	double y;
	double z;
};
//������
struct TriSurface {
	int no;//�����������
	Point3D p1, p2, p3;//������Ķ���
	double xn, yn, zn;//������ķ�����
};
//������ղ���
struct Param {
	double krd;//��������ɫ����������
	double kgd;//���������ɫ����������
	double kbd;//���������ɫ����������
	double kra;//��������ɫ�ⷺ�ⷴ����
	double kga;//���������ɫ�ⷺ�ⷴ����
	double kba;//���������ɫ�ⷺ�ⷴ����
	double krs;//��������ɫ�⾵�淴����
	double kgs;//���������ɫ�⾵�淴����
	double kbs;//����������⾵�淴����
	int n;//������澵��߹�ָ��
};

class CObject3D :
    public CObject
{
public:
	//������������ʷֺ�õ����������б�
	CArray<TriSurface, TriSurface> m_SurfaceList;
	Param m_Param;//���������ղ���
	Point3D p3d[101][101];//����������������
	int countx, county;//���ɵĲ������ھ��Ⱥ�γ���ϵ�����
	double bx, by, bz;//Բ������
public:
	//����ָ�����ĺͰ뾶������
	void CreateBall(double x0, double y0, double z0, double r);
	void SetSurfaceList();//�����������������ʷ�
	void SetFVector(TriSurface* surface);//����������ķ�����
	void SetParam(Param param);//�������������ղ���

};

