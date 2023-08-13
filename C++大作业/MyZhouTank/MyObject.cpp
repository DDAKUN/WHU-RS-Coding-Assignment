#include "pch.h"
#include "MyObject.h"


bool MyObject::IsOverLap(MyObject& obj) {//判断是否越界
	double dx = m_ptPos.x - obj.m_ptPos.x;
	double dy = m_ptPos.y - obj.m_ptPos.y;
	double nDis = sqrt(dx * dx + dy * dy);
	if (nDis <= m_nSize + obj.m_nSize) { return true; }
	else { return false; }//计算两物体中心点的距离
}

void MyObject::SetSize(int nSize) {
	if (m_nSize < 3) m_nSize = 3;
	m_nSize = nSize;
}


