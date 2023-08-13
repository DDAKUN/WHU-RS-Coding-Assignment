#pragma once
#include"MyObject.h"
class Wood:public MyObject
{
	
	Wood();
	~Wood();
	void SetArmor(int nArmor);
	void SetPosition(int x, int y);
	void Draw(CDC* pDC, CRect rct);
	CImage m_Wood;
};

