
// MFCApplication1View.cpp : CMFCApplication1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMFCApplication1View ����/����

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: �ڴ˴���ӹ������
	m_bIfPaint=0;
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View ����

void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCApplication1View ��ӡ

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCApplication1View ���

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View ��Ϣ�������


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIfPaint=~m_bIfPaint;
	m_ptOrigin=point;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_ptOriginΪ��һ����
	/*
	HDC hdc;
	hdc=::GetDC(m_hWnd);
	MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,NULL);
	LineTo(hdc,point.x,point.y);
	::ReleaseDC(m_hWnd,hdc);
	*/
	/*
	CDC *pDC=GetDC();
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point);
	ReleaseDC(pDC);
	*/
	/*
	//CClientDC ����ʱ����GetDC����ʱReleaseDC
	CClientDC dc(this);
	//CClientDC dc(GetParent()); //��ȡ������
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/
	/*
	//CWindowDC dc(this);
	//CWindowDC dc(GetParent());
	CWindowDC dc(GetDesktopWindow());
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/
	/*
	//���� ���ͣ��߿���ɫ
	CPen pen(PS_SOLID,20,RGB(255,0,0));
	CClientDC dc(this);
	CPen *pOldPen=dc.SelectObject(&pen);
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	dc.SelectObject(&pOldPen);
	*/
	/*
	//��ˢ
	//CBrush brush(RGB(255,0,0));
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	CBrush brush(&bitmap);
	CClientDC dc(this);
	dc.FillRect(CRect(m_ptOrigin,point),&brush);
	*/
	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bIfPaint)
	{
		CClientDC dc(this);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin=point;
	}
	CView::OnMouseMove(nFlags, point);
}


//BOOL CMFCApplication1View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	
//	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//��ѧϰʱд��OnCreate��Ϣ��Ӧ����
	/*��Ӧ���ִ�С�������
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);
	*/
	/*λͼ���
	CBitmap bitmap;	//������һ��Ҫд��������У��������������
	bitmap.LoadBitmapW(IDB_BITMAP1);
	CreateCaret(&bitmap);
	*/
	ShowCaret(); //��ʾ���
	return 0;
}


void CMFCApplication1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	CString aa;
	aa.Format(L"%c",nChar);
	dc.TextOutW(0,0,aa,nRepCnt);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
