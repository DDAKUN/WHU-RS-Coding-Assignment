#include "pch.h"
#include "Tank.h"
#include "Shell.h"

CImage Tank::img[5];

Tank::Tank() {
	
	m_nDirection = 1;
	m_Armor = 2;
	
	m_SpeedTank[1] = 10;
	m_SpeedTank[2] = 10;
	m_SpeedTank[3] = 10;
	m_SpeedTank[4] = 10;

	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int npos = str.ReverseFind('\\');
	CString strPathName = str.Left(npos);
	strPathName += L"\\Data";
	CString strImagePathName[5];
	strImagePathName[1] = strPathName + L"\\tankright.png";
	strImagePathName[2] = strPathName + L"\\tankleft.png";
	strImagePathName[3] = strPathName + L"\\tankup.png";
	strImagePathName[4] = strPathName + L"\\tankdown.png";
	if (img[1].IsNull()) {
		img[1].Load(strImagePathName[1]);
	}
	if (img[2].IsNull()) {
		img[2].Load(strImagePathName[2]);
	}
	if (img[3].IsNull()) {
		img[3].Load(strImagePathName[3]);
	}
	if (img[4].IsNull()) {
		img[4].Load(strImagePathName[4]);
	}
}

void Tank::Draw(CDC* pDC) {
	SetSize(20);
	CRect rct1;
	rct1.left = m_ptPos.x - 20;
	rct1.right = m_ptPos.x + 20;
	rct1.top = m_ptPos.y - 20;
	rct1.bottom = m_ptPos.y + 20;


	switch (m_nDirection) {
	case 1:
		if (!img[1].IsNull()) {
			img[1].Draw(pDC->GetSafeHdc(), rct1);
		}
		break;
	case 2:
		if (!img[2].IsNull()) {
			img[2].Draw(pDC->GetSafeHdc(), rct1);
		}
		break;
	case 3:
		if (!img[3].IsNull()) {
			img[3].Draw(pDC->GetSafeHdc(), rct1);
		}
		break;
	case 4:
		if (!img[4].IsNull()) {
			img[4].Draw(pDC->GetSafeHdc(), rct1);
		}
		break;
	default:break;

	}

}

void Tank::Move(int nDirection) {

	m_nDirection = nDirection;

	switch (m_nDirection) {
	case 1:

		m_ptPos.x += m_SpeedTank[1];

		break;
	case 2:

		m_ptPos.x -= m_SpeedTank[2];

		break;
	case 3:

		m_ptPos.y -= m_SpeedTank[3];

		break;
	case 4:
		m_ptPos.y += m_SpeedTank[4];

		break;
	default:break;
	}


}


Shell Tank::Fire() {

	Shell newShell;
	switch (m_nDirection) {
	case(1):
		newShell.m_ptPos.x = m_ptPos.x + m_nSize;newShell.m_ptPos.y = m_ptPos.y;break;
	case(2):
		newShell.m_ptPos.x = m_ptPos.x - m_nSize;newShell.m_ptPos.y = m_ptPos.y;break;
	case(3):
		newShell.m_ptPos.y = m_ptPos.y - m_nSize;newShell.m_ptPos.x = m_ptPos.x;break;
	case(4):
		newShell.m_ptPos.y = m_ptPos.y + m_nSize;newShell.m_ptPos.x = m_ptPos.x;break;
	default:break;
	}//判断当前炮口朝向
	newShell.SetDirection(m_nDirection);
	newShell.m_InitialTime = GetTickCount64();
	return newShell;
}



void Tank::IsMoveEnable(std::vector<Wall> m_vecWall,int i) {
	//模拟坦克朝上下左右方向的移动，若某一方向移动后发生阻碍，则将该方向的速度设为0
	Tank tanktest1;
	Tank tanktest2;
	Tank tanktest3;
	Tank tanktest4;
	tanktest1.SetSize(20);
	tanktest2.SetSize(20);
	tanktest3.SetSize(20);
	tanktest4.SetSize(20);
	tanktest1.m_ptPos.x = m_ptPos.x + 9;
	tanktest1.m_ptPos.y = m_ptPos.y;
	tanktest2.m_ptPos.x = m_ptPos.x - 9;
	tanktest2.m_ptPos.y = m_ptPos.y;
	tanktest3.m_ptPos.x = m_ptPos.x;
	tanktest3.m_ptPos.y = m_ptPos.y - 9;
	tanktest4.m_ptPos.x = m_ptPos.x;
	tanktest4.m_ptPos.y = m_ptPos.y + 9;
	for (auto& ql : m_vecWall) {
		if (ql.m_Armor < 1)continue;
		if (i == 1) {

			if (tanktest1.IsOverLap(ql)) {
				m_SpeedTank[1] = 0;
				break;
			}
			else {
				m_SpeedTank[1] = 10;
			}
		}
		if (i == 2) {
			if (tanktest2.IsOverLap(ql)) {
				m_SpeedTank[2] = 0;
				break;
			}
			else {
				m_SpeedTank[2] = 10;
			}
		}

		if (i == 3) {
			if (tanktest3.IsOverLap(ql)) {
				m_SpeedTank[3] = 0;
				break;
			}
			else {
				m_SpeedTank[3] = 10;
			}
		}
		if (i == 4) {
			if (tanktest4.IsOverLap(ql)) {
				m_SpeedTank[4] = 0;
				break;
			}
			else {
				m_SpeedTank[4] = 10;
			}
		}
	}

}

void Tank::Judge() {
    if (m_ptPos.x - 0.01 < 0) {
		m_SpeedTank[2] = 0;
	}
	if (m_ptPos.x + 0.01 > 620) {
		m_SpeedTank[1] = 0;
	}
	if (m_ptPos.y - 0.01 < 0) {
		m_SpeedTank[3] = 0;
	}
	if (m_ptPos.y + 0.01 > 620) {
		m_SpeedTank[4] = 0;//限制活动范围
	}
}


void Tank::SetPosition(int x, int y) {
	m_ptPos.x = x;
	m_ptPos.y = y;
}