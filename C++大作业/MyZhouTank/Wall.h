#pragma once
#include "MyObject.h"
#include "Shell.h"
class Wall : public MyObject
{
public:
	Wall();
	~Wall();
	void SetArmor(int nArmor);
	void SetPosition(int x, int y);
	void Draw(CDC* pDC, CRect rct);
	CImage m_Brick;

};

