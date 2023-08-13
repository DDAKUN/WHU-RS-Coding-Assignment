#pragma once
#include "Shell.h"
#include "MyObject.h"
#include <thread>
#include "Wall.h"
class Tank : public MyObject
{
public:
	void IsMoveEnable(std::vector<Wall> m_vecWall,int i);
	
	Tank();
	~Tank() {};
	void Draw(CDC* pDC);
	void Move(int nDirection);
	Shell Fire();
	bool f;
	void Judge();
	void SetPosition(int x, int y);
public:
	static CImage img[5];
	int m_SpeedTank[5];


};

