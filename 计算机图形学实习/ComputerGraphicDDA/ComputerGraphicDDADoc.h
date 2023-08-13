
// ComputerGraphicDDADoc.h: CComputerGraphicDDADoc 类的接口
//


#pragma once
#include "CReality.h"

class CComputerGraphicDDADoc : public CDocument
{
protected: // 仅从序列化创建
	CComputerGraphicDDADoc() noexcept;
	DECLARE_DYNCREATE(CComputerGraphicDDADoc)

// 特性
public:
	CPoint group[100];//定义数组，
	int PointNum;
	COLORREF m_crColor;//保存图形颜色

// 操作
public:
	void DDALine(CClientDC* DCPoint);//定义函数
	void MIDLine(CClientDC* DCPoint);//定义中点直线函数
	void BCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void PNCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void Bezier(CClientDC* DCPoint, int mode);
	void Bezier_4(CClientDC* DCPoint, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	void GenerateGraph(CClientDC* DCPoint);
	void DrawGraph(CClientDC* DCPoint);
	void Symmetry(CPoint p1, CPoint p2);
	void SeedFill(CClientDC* DCPoint, CPoint p);
	void EdgeFill(CClientDC* DCPoint);
	void DrawWindow(CClientDC* DCPoint);
	void CohenSutherland(CClientDC* DCPoint, CPoint p1, CPoint p2);
	int encode(int x, int y);
	void PolygonCut(CClientDC* DCPoint);
	void EdgeClipping(int linecode);
	void BCircle(CClientDC* DCPoint, CRect* rc, CPoint p1, CPoint p2);
	void CircleCut(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void GenerateGraph2(CClientDC* DCPoint);
	void Bsampl(CClientDC* DCPoint, int mode);
	void Hermite(CClientDC* DCPoint, int mode);
	void cutmiddle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	bool ClipT(float p, float q, float* u1, float* u2);
	void LB_lineClip(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void drawPhong(double x, double y, CClientDC* DCPoint);
	void drawLambert(double x, double y, CClientDC* DCPoint);

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CComputerGraphicDDADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnSetColor();
};
