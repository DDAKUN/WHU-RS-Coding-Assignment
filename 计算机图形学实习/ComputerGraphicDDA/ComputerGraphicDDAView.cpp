
// ComputerGraphicDDAView.cpp: CComputerGraphicDDAView 类的实现
//  
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ComputerGraphicDDA.h"
#endif

#include "ComputerGraphicDDADoc.h"
#include "ComputerGraphicDDAView.h"
#include "SetCharDlg.h"
#include "CObject3D.h"
#include "CReality.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern CStatusBar m_wndStatusBar;

// CComputerGraphicDDAView

IMPLEMENT_DYNCREATE(CComputerGraphicDDAView, CView)

BEGIN_MESSAGE_MAP(CComputerGraphicDDAView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CComputerGraphicDDAView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_DDALINE, &CComputerGraphicDDAView::OnDrawDdaline)
	ON_COMMAND(ID_DRAW_BCIRCLE, &CComputerGraphicDDAView::OnDrawBcircle)
	ON_COMMAND(ID_DRAW_PNCIRCLE, &CComputerGraphicDDAView::OnDrawPncircle)
	ON_COMMAND(ID_CURVE_BEZIER, &CComputerGraphicDDAView::OnCurveBezier)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_MIDLINE, &CComputerGraphicDDAView::OnDrawMidline)
	ON_COMMAND(ID_SET_CHAR, &CComputerGraphicDDAView::OnSetChar)
	ON_COMMAND(ID_TRANS_MOVE, &CComputerGraphicDDAView::OnTransMove)
	ON_COMMAND(ID_TRANS_SYMMETRY, &CComputerGraphicDDAView::OnTransSymmetry)
	ON_COMMAND(ID_FILL_SEED, &CComputerGraphicDDAView::OnFillSeed)
	ON_COMMAND(ID_FILL_EDGE, &CComputerGraphicDDAView::OnFillEdge)
	ON_COMMAND(ID_FILL_SCANLINE, &CComputerGraphicDDAView::OnFillScanline)
	ON_COMMAND(ID_CUT_CS, &CComputerGraphicDDAView::OnCutCs)
	ON_COMMAND(ID_CUT_POLYGON, &CComputerGraphicDDAView::OnCutPolygon)
	ON_COMMAND(ID_CUT_CIRCLE, &CComputerGraphicDDAView::OnCutCircle)
	ON_COMMAND(ID_TRANS_ROTATE, &CComputerGraphicDDAView::OnTransRotate)
	ON_COMMAND(ID_TRANS_ZOOM, &CComputerGraphicDDAView::OnTransZoom)
	ON_COMMAND(ID_CURVE_BSAMPLE, &CComputerGraphicDDAView::OnCurveBsample)
	ON_COMMAND(ID_CURVE_HERMITE, &CComputerGraphicDDAView::OnCurveHermite)
	ON_COMMAND(ID_CUT_LIANG, &CComputerGraphicDDAView::OnCutLiang)
	ON_COMMAND(ID_CUT_MIDDLE, &CComputerGraphicDDAView::OnCutMiddle)
	ON_COMMAND(ID_BLANKING, &CComputerGraphicDDAView::OnBlanking)
	ON_COMMAND(ID_LAMBERT, &CComputerGraphicDDAView::OnLambert)
	ON_COMMAND(ID_PHONG, &CComputerGraphicDDAView::OnPhong)
END_MESSAGE_MAP()

// CComputerGraphicDDAView 构造/析构

CComputerGraphicDDAView::CComputerGraphicDDAView() noexcept
{
	// TODO: 在此处添加构造代码

}

CComputerGraphicDDAView::~CComputerGraphicDDAView()
{
}

BOOL CComputerGraphicDDAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CComputerGraphicDDAView 绘图

void CComputerGraphicDDAView::OnDraw(CDC* /*pDC*/)
{
	CComputerGraphicDDADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CComputerGraphicDDAView 打印


void CComputerGraphicDDAView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CComputerGraphicDDAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CComputerGraphicDDAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CComputerGraphicDDAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CComputerGraphicDDAView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CComputerGraphicDDAView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CComputerGraphicDDAView 诊断

#ifdef _DEBUG
void CComputerGraphicDDAView::AssertValid() const
{
	CView::AssertValid();
}

void CComputerGraphicDDAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComputerGraphicDDADoc* CComputerGraphicDDAView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComputerGraphicDDADoc)));
	return (CComputerGraphicDDADoc*)m_pDocument;
}
#endif //_DEBUG


// CComputerGraphicDDAView 消息处理程序


void CComputerGraphicDDAView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CComputerGraphicDDADoc* pDoc = GetDocument(); //获得文档类指针
	CClientDC ht(this); //定义当前绘图设备
	if (MenuID == 1) { //DDA直线
		if (PressNum == 0) { //第一次按键将第一点保留在文档类数组中
			pDoc->group[PressNum] = point;
			mPointOrign = point; mPointOld = point;;//记录第一点
			PressNum++;
			SetCapture();
		}
		else if (PressNum == 1) { //第二次按键保留第二点，用文档类画线
			pDoc->group[PressNum] = point;
			PressNum = 0; //程序画图
			pDoc->DDALine(&ht);
			ReleaseCapture();
		}
	}

	if (MenuID == 2) {//中点直线算法
		if (PressNum == 0) { //第一次按键将第一点保留在文档类数组中
			pDoc->group[PressNum] = point;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			PressNum++;
			SetCapture();
		}
		else if (PressNum == 1) { //第二次按键保留第二点，用文档类画线
			ht.SetROP2(R2_NOT);
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[PressNum] = point;
			PressNum = 0; //程序画图
			pDoc->MIDLine(&ht);
			ReleaseCapture();
		}
	}

	if (MenuID == 3 || MenuID == 4 || MenuID == 33) {//Bresenham圆
		if (PressNum == 0) {//第一次按键将第一点保留在mPointOrign
			pDoc->group[PressNum] = point;
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1 && MenuID == 3) {//第二次按键调用文档类画圆程序画图
			PressNum = 0;
			pDoc->BCircle(&ht, mPointOrign, point);ReleaseCapture();
		}
		else if (PressNum == 1 && MenuID == 4) {//第二次按键调用画圆程序画图
			PressNum = 0;
			pDoc->PNCircle(&ht, mPointOrign, point);ReleaseCapture();
		}
		else if (PressNum == 1 && MenuID == 33)//圆裁剪
		{
			PressNum = 0;
			pDoc->CircleCut(&ht, mPointOrign, point);
			ReleaseCapture();
		}

	}

	if (MenuID == 5 || MenuID == 26 || MenuID == 34) {//Bezier曲线选点并做十字标志
		pDoc->group[pDoc->PointNum++] = point;
		ht.MoveTo(point.x - 5, point.y);
		ht.LineTo(point.x + 5, point.y);
		ht.MoveTo(point.x, point.y - 5);
		ht.LineTo(point.x, point.y + 5);
		SetCapture();
		PressNum = 1;
	}

	if (MenuID == 6 && PressNum == 0) {//在控制点数组中，逐个寻找
		for (int i = 0;i < pDoc->PointNum;i++) {
			if ((point.x >= pDoc->group[i].x - 5) && (point.x <= pDoc->group[i].x + 5) && (point.y >= pDoc->group[i].y - 5) && (point.y <= pDoc->group[i].y + 5)) {
				SaveNumber = i;
				PressNum = 1;
			}
		}
	}

	if (MenuID == 27 && PressNum == 0) {//在控制点数组中，逐个寻找
		for (int i = 0;i < pDoc->PointNum;i++) {
			if ((point.x >= pDoc->group[i].x - 5) && (point.x <= pDoc->group[i].x + 5) && (point.y >= pDoc->group[i].y - 5) && (point.y <= pDoc->group[i].y + 5)) {
				SaveNumber = i;
				PressNum = 1;
			}
		}
	}

	if (MenuID == 35 && PressNum == 0) {//在控制点数组中，逐个寻找
		for (int i = 0;i < pDoc->PointNum;i++) {
			if ((point.x >= pDoc->group[i].x - 5) && (point.x <= pDoc->group[i].x + 5) && (point.y >= pDoc->group[i].y - 5) && (point.y <= pDoc->group[i].y + 5)) {
				SaveNumber = i;
				PressNum = 1;
			}
		}
	}
	if (MenuID == 11) {//平移
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) { //根据两点间距计算平移量
			for (int i = 0;i < pDoc->PointNum;i++)//根据平移量计算新图形坐标
			{
				pDoc->group[i].x += point.x - mPointOrign.x;
				pDoc->group[i].y += point.y - mPointOrign.y;
			}
			ht.DPtoLP(&point);
			ht.SetROP2(R2_NOT);
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 15) {//对称变换
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) {
			pDoc->Symmetry(mPointOrign, point);//进行对称变换
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 20) {//种子填充:画边界
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			mPointOld1 = point;//记录第一点
			PressNum++;
			SetCapture();
		}
		else {
			ht.SetROP2(R2_NOT);
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[0] = mPointOrign;//借助DDA直线函数画边界
			pDoc->group[1] = point;
			pDoc->DDALine(&ht);
			mPointOrign = point;
			mPointOld = point;
		}
	}

	if (MenuID == 21) {//确定种子点，填充
		pDoc->SeedFill(&ht, point);
		PressNum = 0;MenuID = 20;//设置决定顶点操作方式
	}

	if (MenuID == 22|| MenuID == 23 || MenuID == 25) {//边缘填充选顶点
		pDoc->group[PressNum++] = point;
		pDoc->PointNum++;
		mPointOrign = point;
		mPointOld = point;
		SetCapture();
	}

	if (MenuID == 24) {//Cohen-sutherland裁剪算法
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
			SetCapture();
		}
		else
		{
			pDoc->CohenSutherland(&ht, mPointOrign, point);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 31) {
		//缩放
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) {//根据两点间距计算平移量
			int dx = point.x - mPointOrign.x;
			int dy = point.y - mPointOrign.y;

			//根据直线的斜率确定缩放比例，d>0为放大，d<0为缩小
			//根据平移量计算新图形坐标
			pDoc->group[0].x -= (dx / 2);
			pDoc->group[0].y += (dy / 2);
			pDoc->group[1].x += (dx / 2);
			pDoc->group[1].y += (dy / 2);
			pDoc->group[2].x += (dx / 2);
			pDoc->group[2].y -= (dy / 2);
			pDoc->group[3].x -= (dx / 2);
			pDoc->group[3].y -= (dy / 2);
			pDoc->group[4].x -= (dx / 2);
			pDoc->group[4].y += (dy / 2);

			ht.DPtoLP(&point);
			ht.SetROP2(R2_NOT);
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 30) {
		//旋转
		double pai = 3.1415926;
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) {//根据两点间距计算旋转角度‘
			double dx = point.x - mPointOrign.x;
			double dy = -(point.y - mPointOrign.y);
			double k = dy / dx;
			double a;//旋转角

			//根据直线的斜率确定旋转角，统一到顺时针旋转上
			if (dx > 0 && dy > 0) {
				a = 2 * pai - atan(k);//顺时针旋转a(锐角)，第一象限
			}
			else if (dx > 0 && dy < 0) {
				a = atan(-k);//逆时针旋转a(锐角)，第四象限
			}
			else if (dx < 0 && dy>0) {
				a = 2 * pai - (pai - atan(-k));//顺时针旋转a(钝角)，第二象限
			}
			else if (dx < 0 && dy < 0) {
				a = pai - atan(k);//逆时针旋转a(钝角)，第三象限
			}

			//旋转公式为rotateX=cos(a)*sourceX+sin(a)*sourceY；rotateY=-sin(a)*sourceX+cos(a)*sourceY
			for (int i = 0;i < pDoc->PointNum;i++) {
				pDoc->group[i].x = cos(a) * pDoc->group[i].x + sin(a) * pDoc->group[i].y;
				pDoc->group[i].y = -sin(a) * pDoc->group[i].x + cos(a) * pDoc->group[i].y;
			}
			ht.DPtoLP(&point);
			ht.SetROP2(R2_NOT);
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 53) {//梁友栋-Barsky 算法
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
			SetCapture();
		}
		else {
			pDoc->LB_lineClip(&ht, mPointOrign, point);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 62) {//中点裁剪算法
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
			SetCapture();
		}
		else {
			pDoc->cutmiddle(&ht, mPointOrign, point);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 71) {//中点裁剪算法
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
			SetCapture();
		}
		else {
			double x = point.x - mPointOrign.x;
			double y = point.y - mPointOrign.y;
			pDoc->drawPhong(x, y, &ht);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 72) {//中点裁剪算法
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
			SetCapture();
		}
		else {
			double x = point.x - mPointOrign.x;
			double y = point.y - mPointOrign.y;
			pDoc->drawLambert(x, y, &ht);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CComputerGraphicDDAView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC ht(this); //定义当前绘图设备
	OnPrepareDC(&ht);
	ht.DPtoLP(&point);

	if (MenuID == 5 && pDoc->PointNum > 3) {
		pDoc->Bezier(&ht, 1);//绘制Bezier函数
		MenuID = 6; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	if (MenuID == 6 && PressNum == 1) {
		PressNum = 0;
	}

	if (MenuID == 26 && pDoc->PointNum > 4) {
		pDoc->Bsampl(&ht, 1);//绘制B样条函数
		MenuID = 27; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	if (MenuID == 27 && PressNum == 1) {
		PressNum = 0;
	}

	if (MenuID == 34 && pDoc->PointNum > 4) {
		pDoc->Hermite(&ht, 1);//绘制Hermite函数
		MenuID = 35; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	if (MenuID == 35 && PressNum == 1) {
		PressNum = 0;
	}

	if (MenuID == 20 && PressNum > 0) {//种子填充
		ht.MoveTo(mPointOrign);//擦除橡皮筋
		ht.LineTo(point);
		pDoc->group[0] = mPointOld1;//封闭多边形
		pDoc->group[1] = mPointOrign;
		pDoc->DDALine(&ht);
		PressNum = 0;MenuID = 21;//改变操作方式为种子点选取
		ReleaseCapture();
	}

	if (MenuID == 22) {//边缘填充选点结束
		pDoc->group[PressNum] = pDoc->group[0];
		pDoc->PointNum++;
		ht.MoveTo(pDoc->group[PressNum - 1]);
		ht.LineTo(pDoc->group[0]);
		for (int i = 0;i < PressNum;i++)
			ht.LineTo(pDoc->group[i + 1]);
		pDoc->EdgeFill(&ht);
		PressNum = 0;pDoc->PointNum = 0;
		ReleaseCapture();


	}

	if (MenuID == 23) {
		pDoc->group[PressNum] = pDoc->group[0];//封闭多边形
		ht.MoveTo(pDoc->group[PressNum - 1]);//擦除
		ht.LineTo(pDoc->group[0]);
		for (int i = 0;i < PressNum;i++)//擦除
			ht.LineTo(pDoc->group[i + 1]);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//设置多边形边界颜色（即画笔）
		CPen* pOldPen = ht.SelectObject(&pen);
		CBrush brush(RGB(0, 255, 0)); //设置多边形填充颜色（即画刷）
		CBrush* pOldBrush = ht.SelectObject(&brush);
		ht.SetROP2(R2_COPYPEN); //设置直接画方式
		ht.Polygon(pDoc->group, PressNum);//调用多边形扫描线填充函数
		ht.SelectObject(pOldPen);//恢复系统的画笔、画刷颜色设置
		ht.SelectObject(pOldBrush);
		PressNum = 0;pDoc->PointNum = 0;//初始化参数，为下一次操作做准备
		ReleaseCapture();
	}

	if (MenuID == 25) {//多边形裁剪
		ht.SetROP2(R2_NOT);
		ht.MoveTo(mPointOrign);//擦除橡皮筋
		ht.LineTo(point);
		pDoc->group[PressNum] = pDoc->group[0];//将第一个顶点作为最后一个顶点
		pDoc->PointNum = PressNum; //记录顶点数量
		ht.MoveTo(pDoc->group[PressNum - 1]);
		ht.LineTo(pDoc->group[0]);
		pDoc->PolygonCut(&ht);
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}

	if (MenuID == 26 && pDoc->PointNum > 4) {
		pDoc->Bsampl(&ht, 1);//绘制B样条函数
		MenuID = 27; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}

	if (MenuID == 34 && pDoc->PointNum > 4) {
		pDoc->Hermite(&ht, 1);//绘制Hermite函数
		MenuID = 35; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	CView::OnRButtonDown(nFlags, point);
}


void CComputerGraphicDDAView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int xx, yy;
	char p1[20];
	CClientDC pDC(this);
	CComputerGraphicDDADoc* pDoc = GetDocument();
	OnPrepareDC(&pDC);
	pDC.DPtoLP(&point);
	pDC.SetROP2(R2_NOT);//设置异或方式xx=point.x; yy = point.y; //取出坐标信息

	xx = point.x;yy = point.y; //取出坐标信息
	sprintf(p1, "%4d", xx); //转化为字符串
	wchar_t p2[20];	
	for (int i = 0;p1[i];i++) 
		p2[i] = p1[i];
	LPCTSTR str = p2;
	m_wndStatusBar.SetPaneText(2, p2, TRUE); //在第2个区域显示x坐标
	sprintf(p1, "%4d", yy); //转化为字符串
	m_wndStatusBar.SetPaneText(3, p2, TRUE); //在第3个区域显示y坐标

	if ((MenuID == 1 || MenuID==2 || MenuID==11 || MenuID == 15 || MenuID == 20 || MenuID == 22 || 
		MenuID == 23 || MenuID == 24 || MenuID == 25 || MenuID == 30|| MenuID == 31 || MenuID == 53 || MenuID == 62 || MenuID == 71 || MenuID == 72)&& PressNum >0) {
		if (mPointOld != point) {
			pDC.MoveTo(mPointOrign);
			pDC.LineTo(mPointOld);//擦旧线
			pDC.MoveTo(mPointOrign);
			pDC.LineTo(point);//画新线
			mPointOld = point;
		}
	}
	if ((MenuID == 3 || MenuID == 4 || MenuID == 33) && PressNum == 1) {
		pDC.SelectStockObject(NULL_BRUSH);//画空心圆
		if (mPointOld != point) {
			int r = (int)sqrt((mPointOrign.x - mPointOld.x) * (mPointOrign.x-mPointOld.x) + (mPointOrign.y - mPointOld.y) * (mPointOrign.y-mPointOld.y));
			pDC.Ellipse(mPointOrign.x - r, mPointOrign.y-r, mPointOrign.x + r, mPointOrign.y + r);//擦旧圆
			r = (int)sqrt((mPointOrign.x - point.x) * (mPointOrign.x - point.x) +
				(mPointOrign.y - point.y) * (mPointOrign.y - point.y));
			pDC.Ellipse(mPointOrign.x - r, mPointOrign.y-r, mPointOrign.x + r, mPointOrign.y + r);//画新圆
			mPointOld = point;
		}
	}
	if ((MenuID == 6) && PressNum > 0) {
		if (pDoc->group[SaveNumber] != point) {
			//画十字标志
			pDC.MoveTo(pDoc->group[SaveNumber].x - 5, pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x + 5, pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y - 5);
			pDC.LineTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y + 5);
			pDoc->Bezier(&pDC, 1);//擦除十字标志和旧线
			pDC.MoveTo(point.x - 5, point.y);
			pDC.LineTo(point.x + 5, point.y);
			pDC.MoveTo(point.x, point.y - 5);
			pDC.LineTo(point.x, point.y + 5);
			pDoc->group[SaveNumber] = point;//记录新控制点
			pDoc->Bezier(&pDC, 1);//画十字标志和新曲线
		}
	}

	if ((MenuID == 27) && PressNum > 0) {
		if (pDoc->group[SaveNumber] != point) {
			//画十字标志
			pDC.MoveTo(pDoc->group[SaveNumber].x - 5, pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x + 5, pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y - 5);
			pDC.LineTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y + 5);
			pDoc->Bsampl(&pDC, 1);//擦除十字标志和旧线
			pDC.MoveTo(point.x - 5, point.y);
			pDC.LineTo(point.x + 5, point.y);
			pDC.MoveTo(point.x, point.y - 5);
			pDC.LineTo(point.x, point.y + 5);
			pDoc->group[SaveNumber] = point;//记录新控制点
			pDoc->Bsampl(&pDC, 1);//画十字标志和新曲线
		}
	}
	
	if ((MenuID == 35) && PressNum > 0) {
		if (pDoc->group[SaveNumber] != point) {
			//画十字标志
			pDC.MoveTo(pDoc->group[SaveNumber].x - 5, pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x + 5, pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y - 5);
			pDC.LineTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y + 5);
			pDoc->Hermite(&pDC, 1);//擦除十字标志和旧线
			pDC.MoveTo(point.x - 5, point.y);
			pDC.LineTo(point.x + 5, point.y);
			pDC.MoveTo(point.x, point.y - 5);
			pDC.LineTo(point.x, point.y + 5);
			pDoc->group[SaveNumber] = point;//记录新控制点
			pDoc->Hermite(&pDC, 1);//画十字标志和新曲线
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CComputerGraphicDDAView::OnDrawDdaline()
{
	// TODO: 在此添加命令处理程序代码
	 PressNum = 0; MenuID = 1;
}


void CComputerGraphicDDAView::OnDrawBcircle()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0;MenuID = 3;
}


void CComputerGraphicDDAView::OnDrawPncircle()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0;MenuID = 4;
}


void CComputerGraphicDDAView::OnCurveBezier()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	pDoc->PointNum = 0;//初始化

	PressNum = 0;MenuID = 5;
}


void CComputerGraphicDDAView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDC.DPtoLP(&point);
	pDC.SetROP2(R2_NOT);//设置异或方式

	if (MenuID == 6) {
		for (int i = 0;i < pDoc->PointNum;i++) {//消除所有光标，绘制十字标志
			pDC.MoveTo(pDoc->group[i].x - 5, pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x + 5, pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x, pDoc->group[i].y - 5);
			pDC.LineTo(pDoc->group[i].x, pDoc->group[i].y + 5);
		}
		pDoc->Bezier(&pDC, 0);//绘制Bezier函数
		MenuID = 5; //将下面的操作改回Bezier曲线方式
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}

	if (MenuID == 27) {
		for (int i = 0;i < pDoc->PointNum;i++) {//消除所有光标，绘制十字标志
			pDC.MoveTo(pDoc->group[i].x - 5, pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x + 5, pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x, pDoc->group[i].y - 5);
			pDC.LineTo(pDoc->group[i].x, pDoc->group[i].y + 5);
		}
		pDoc->Bsampl(&pDC, 0);//绘制B样条函数
		MenuID = 26; //将下面的操作改回B样条曲线函数方式
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}

	if (MenuID == 35) {
		for (int i = 0;i < pDoc->PointNum;i++) {//消除所有光标，绘制十字标志
			pDC.MoveTo(pDoc->group[i].x - 5, pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x + 5, pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x, pDoc->group[i].y - 5);
			pDC.LineTo(pDoc->group[i].x, pDoc->group[i].y + 5);
		}
		pDoc->Hermite(&pDC, 0);//绘制Hermite函数
		MenuID = 26; //将下面的操作改回Hermite曲线函数方式
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CComputerGraphicDDAView::OnDrawMidline()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0;
	MenuID = 2;
}


void CComputerGraphicDDAView::OnSetChar()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	CSetCharDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFont* pfntOld = pDC->SelectObject(&dlg.m_fnt);//保存旧字体
		pDC->SetTextColor(dlg.m_clrText);//设置颜色
		pDC->TextOut(dlg.m_nX, dlg.m_nY, dlg.m_strString);//画到屏幕上
		pDC->SelectObject(pfntOld);//还原旧字体
	}
	ReleaseDC(pDC);

}


void CComputerGraphicDDAView::OnTransMove()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);//调用文档类函数在屏幕上生成图形
	PressNum = 0; MenuID = 11;
}


void CComputerGraphicDDAView::OnTransSymmetry()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);
	PressNum = 0;MenuID = 15;



}


void CComputerGraphicDDAView::OnFillSeed()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0;MenuID = 20;
}


void CComputerGraphicDDAView::OnFillEdge()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0;MenuID = 22;
}


void CComputerGraphicDDAView::OnFillScanline()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	pDoc->PointNum = 0;//实际上不需要该变量，但为了借鉴边缘填充的部分功能，与边缘填充保持一致
	PressNum = 0;MenuID = 23;
}


void CComputerGraphicDDAView::OnCutCs()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0;MenuID = 24;
}


void CComputerGraphicDDAView::OnCutPolygon()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0;MenuID = 25;

}


void CComputerGraphicDDAView::OnCutCircle()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0;MenuID = 33;

}


void CComputerGraphicDDAView::OnTransRotate()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph2(&pDC);//调用文档类函数在屏幕上生成图形
	PressNum = 0; MenuID = 30;
}


void CComputerGraphicDDAView::OnTransZoom()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph2(&pDC);//调用文档类函数在屏幕上生成图形
	PressNum = 0; MenuID = 31;
}


void CComputerGraphicDDAView::OnCurveBsample()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	pDoc->PointNum = 0;//初始化
	PressNum = 0;MenuID = 26;
}


void CComputerGraphicDDAView::OnCurveHermite()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	pDoc->PointNum = 0;//初始化
	PressNum = 0;MenuID = 34;
}


void CComputerGraphicDDAView::OnCutLiang()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0;MenuID = 53;
}


void CComputerGraphicDDAView::OnCutMiddle()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0;MenuID = 62;
}


void CComputerGraphicDDAView::OnBlanking()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC* pdc = new CClientDC(this);
	CPen* pen1 = new CPen(PS_SOLID, 1, RGB(0, 0XFF, 0));
	CPen* pen2 = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* OldPen = pdc->SelectObject(pen1);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldbrush = (CBrush*)pdc->SelectObject(&brush);
	int flag, k1, k2, r1, r2, n, d, m, p;
	int xs1, xs2, xs3, xs4, ys1, ys2, ys3, ys4, i, j, lastp;
	double x, y, z, thx, th1, th3, yw, zw, xw, thy, th2;
	double PI, ed, od, eh, zzw, ppw;
	double xs[50][17], zs[50][17], ys[50][17], zc[50][17], x1, y1;
	int zz[850], pp[850];
	r1 = 120;
	r2 = 40;
	k1 = 20;
	k2 = 16;
	ed = 1500;
	eh = 0;
	od = 0;
	n = 0;
	PI = 3.14159;
	th3 = 1;
	thx = 0.9;
	for (d = -1; d <= 1; d += 2) {
		for (th1 = 0; th1 <= 2 * PI + 0.1; th1 += 2 * PI / k1) {
			n = n + 1;
			m = 0;
			for (th2 = 0; th2 <= 2 * PI + 0.1; th2 += 2 * PI / k2) {
				m = m + 1;
				x = r1 + r2 * cos(th2);
				y = r2 * sin(th2);
				z = 0;
				thy = th1;
				zw = z;
				xw = x;
				x = zw * cos(thy) - xw * sin(thy);
				z = zw * sin(thy) + xw * cos(thy);
				x = x + r1 / 2 * d;
				if (d == 1) {
					yw = y;
					zw = z;
					y = yw * cos(PI / 2) - zw * sin(PI / 2);
					z = yw * sin(PI / 2) + zw * cos(PI / 2);
				}
				thy = th3;
				zw = z;
				xw = x;
				x = zw * cos(thy) - xw * sin(thy);
				z = zw * sin(thy) + xw * cos(thy);
				yw = y;
				zw = z;
				y = yw * cos(thx) - zw * sin(thx);
				z = yw * sin(thx) + zw * cos(thx);
				x = x * ed / (ed - od - z);
				y = (y * ed - eh * (od + z)) / (ed - od - z);
				xs[n][m] = x;
				ys[n][m] = y;
				zs[n][m] = z;
			}
			flag = 0;
		}
		flag = 0;
	}
	p = 0;
	for (n = 1; n <= k1; n += 1) {
		for (m = 1; m <= k2; m += 1) {
			zc[n][m] = int((zs[n][m] + zs[n + 1][m + 1]) / 2);
			zz[p] = zc[n][m];
			pp[p] = p;
			p = p + 1;
		}
	}
	lastp = p - 1;
	for (i = 2; i <= lastp; i += 1) {
		for (j = i - 1; j >= 0; j += -1) {
			if (zz[j] > zz[j + 1]) {
				zzw = zz[j];
				zz[j] = zz[j + 1];
				zz[j + 1] = zzw;
				ppw = pp[j];
				pp[j] = pp[j + 1];
				pp[j + 1] = ppw;
			}
		}
	}
	for (p = 0; p <= lastp; p += 1) {
		n = int(pp[p] / k2) + 1;
		m = pp[p] % k2 + 1;
		if (n != (k1 + 1)) {
			xs1 = int(xs[n][m]);
			ys1 = int(ys[n][m]);
			xs2 = int(xs[n + 1][m]);
			ys2 = int(ys[n + 1][m]);
			xs3 = int(xs[n + 1][m + 1]);
			ys3 = int(ys[n + 1][m + 1]);
			xs4 = int(xs[n][m + 1]);
			ys4 = int(ys[n][m + 1]);
		}
		if (abs(ys1 * (xs2 - xs3) + ys2 * (xs3 - xs1) + ys3 * (xs1 - xs2)) > 80) {
			pdc->MoveTo(xs1 + 320, ys1 + 200);
			pdc->SelectObject(pen1);
			pdc->LineTo(xs2 + 320, ys2 + 200);
			pdc->LineTo(xs3 + 320, ys3 + 200);
			pdc->LineTo(xs4 + 320, ys4 + 200);
			pdc->LineTo(xs1 + 320, ys1 + 200);
			x = (xs[n][m] + xs[n + 1][m + 1]) / 2;
			y = (ys[n][m] + ys[n + 1][m + 1]) / 2;
			x1 = int(x + 320);
			y1 = int(y + 200);
			pdc->ExtFloodFill(x1, y1, RGB(0, 255, 0), 0);//条件语句结束
		}
		pdc->MoveTo(xs1 + 320, ys1 + 200);
		pdc->SelectObject(pen2);
		pdc->LineTo(xs2 + 320, ys2 + 200);
		pdc->LineTo(xs3 + 320, ys3 + 200);
		pdc->LineTo(xs4 + 320, ys4 + 200);
		pdc->LineTo(xs1 + 320, ys1 + 200);
		Sleep(1);
	}
	pdc->SelectObject(OldPen);
	delete pen1;
	delete pen2;
	pdc->DeleteDC();

}


void CComputerGraphicDDAView::OnLambert()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->drawLambert(0, 0.5, &pDC);
	MenuID = 72;PressNum = 0;

}


void CComputerGraphicDDAView::OnPhong()
{
	// TODO: 在此添加命令处理程序代码
	CComputerGraphicDDADoc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->drawPhong(0, 0.5, &pDC);
	MenuID = 71;PressNum = 0;

}
