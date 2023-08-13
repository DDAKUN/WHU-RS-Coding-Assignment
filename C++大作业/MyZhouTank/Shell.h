#pragma once
#include"MyObject.h"
class Shell : public MyObject
{

public:
	Shell();
	~Shell() {};
	void Draw(CDC* pDC);
	void Move();
	bool f;
public:
	__int64 m_InitialTime;
};
