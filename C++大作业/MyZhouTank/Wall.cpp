#include "pch.h"
#include "Wall.h"

Wall::Wall() {
	m_Speed = 0;
	m_Armor = 2;
	m_nDirection = 1;
	m_ptPos.x = -1;
	m_ptPos.y = -1;
	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int npos = str.ReverseFind('\\');
	CString strPathName = str.Left(npos);
	strPathName += L"\\Data";
	CString strImagePathName;
	strImagePathName = strPathName + L"\\Brick.png";
	m_Brick.Load(strImagePathName);
	m_nSize = 20;
}


Wall::~Wall() {

}

void Wall::SetArmor(int nArmor) {
	m_Armor = nArmor;
}

void Wall::SetPosition(int x, int y) {
	m_ptPos.x = x;
	m_ptPos.y = y;
}

void Wall::Draw(CDC* pDC, CRect rct) {
	if (m_Armor < 1)return;


	if (!m_Brick.IsNull()) {
		m_Brick.Draw(pDC->GetSafeHdc(), rct);
	}

}