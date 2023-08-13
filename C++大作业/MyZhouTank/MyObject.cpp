#include "pch.h"
#include "MyObject.h"


bool MyObject::IsOverLap(MyObject& obj) {//�ж��Ƿ�Խ��
	double dx = m_ptPos.x - obj.m_ptPos.x;
	double dy = m_ptPos.y - obj.m_ptPos.y;
	double nDis = sqrt(dx * dx + dy * dy);
	if (nDis <= m_nSize + obj.m_nSize) { return true; }
	else { return false; }//�������������ĵ�ľ���
}

void MyObject::SetSize(int nSize) {
	if (m_nSize < 3) m_nSize = 3;
	m_nSize = nSize;
}


