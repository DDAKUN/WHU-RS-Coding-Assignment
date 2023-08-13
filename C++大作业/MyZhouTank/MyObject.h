#pragma once
#include "sapi.h"
#include <vector>
#include <thread>
#include <mutex>
class MyObject
{
public:
	MyObject() { m_nSize = 10; };
	~MyObject() {};
	void Draw(CDC* pDC) {
		pDC->Ellipse(m_ptPos.x - m_nSize, m_ptPos.y - m_nSize, m_ptPos.x + m_nSize, m_ptPos.y + m_nSize);
	};
	void Move(int nDirection) {};
	bool IsOverLap(MyObject& obj);
	void SetSize(int nSize);
	void SetDirection(int nDir) {
		if (nDir < 1 || nDir>4) {
			m_nDirection = 1;
		}
		else {
			m_nDirection = nDir;
		}
	}
	
public:
	int m_Speed;

	int m_Armor;
	CPoint m_ptPos;

	int m_nDirection;
	int m_nSize;
	
protected:


};




