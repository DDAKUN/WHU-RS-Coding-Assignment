#include "pch.h"
#include "Shell.h"


Shell::Shell() {
	m_Speed = 2;
	m_nDirection = 4;
	m_Armor = 1;
	m_ptPos.x = 0;
	m_ptPos.y = 0;
	f = true;
}





void Shell::Draw(CDC* pDC) {
	if (m_Armor < 1)return;
	SetSize(10);
	__int64 tmCurrent = GetTickCount64();
	__int64 tmGap = tmCurrent - m_InitialTime;//获取当前时间
	int nDis = tmGap * m_Speed/4 ;//计算出移动距离
	switch (m_nDirection) {
	case(1):
		m_ptPos.x = m_ptPos.x + nDis;
		break;
	case(2):
		m_ptPos.x = m_ptPos.x - nDis;
		break;
	case(3):
		m_ptPos.y = m_ptPos.y - nDis;
		break;
	case(4):
		m_ptPos.y = m_ptPos.y + nDis;
		break;
	default:break;
	}//炮弹移动
	pDC->Ellipse(m_ptPos.x - m_nSize, m_ptPos.y - m_nSize, m_ptPos.x + m_nSize, m_ptPos.y + m_nSize);

	m_InitialTime = tmCurrent;

}

void Shell::Move() {
	switch (m_nDirection) {
	case(1):
		m_ptPos.x = m_ptPos.x + m_Speed;
		break;
	case(2):
		m_ptPos.x = m_ptPos.x - m_Speed;
		break;
	case(3):
		m_ptPos.y = m_ptPos.y - m_Speed;
		break;
	case(4):
		m_ptPos.y = m_ptPos.y + m_Speed;
		break;
	default:break;
	}
}