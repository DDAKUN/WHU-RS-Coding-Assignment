#pragma once
#include"MyObject.h"
class Tree :public MyObject
{
public:
	Tree();
	~Tree();
	void SetArmor(int nArmor);
	void SetPosition(int x, int y);
	void Draw(CDC* pDC, CRect rct);
	CImage m_Brick;
};

