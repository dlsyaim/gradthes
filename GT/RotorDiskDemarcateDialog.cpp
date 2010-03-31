// RotorDiskDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "RotorDiskDemarcateDialog.h"


// RotorDiskDemarcateDialog 对话框

IMPLEMENT_DYNAMIC(RotorDiskDemarcateDialog, CDialog)

RotorDiskDemarcateDialog::RotorDiskDemarcateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(RotorDiskDemarcateDialog::IDD, pParent)
{

}

RotorDiskDemarcateDialog::~RotorDiskDemarcateDialog()
{
}

void RotorDiskDemarcateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEMARCATE_ROTORDISK_TAB, m_tabRotorDisk);
}


BEGIN_MESSAGE_MAP(RotorDiskDemarcateDialog, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// RotorDiskDemarcateDialog 消息处理程序

BOOL RotorDiskDemarcateDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

   // Setup the tab control
   int nPageID = 0;
   m_tabCollective.Create(IDD_COLLECTIVE_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage (_T("总距标定"), nPageID++, &m_tabCollective);
   m_tabRoll.Create(IDD_ROLL_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage(_T("侧滚舵机标定"), nPageID++, &m_tabRoll);
   m_tabPitch.Create(IDD_PITCH_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage(_T("俯仰舵机标定"), nPageID++, &m_tabPitch);
   return TRUE; // return TRUE unless you set the focus to a control
}

void RotorDiskDemarcateDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	POINT p;
	p.x = 10;
	p.y = 460;
	origin_x1 = p.x;
	origin_y1 = p.y;
	drawCoordinateSystem(&dc, p, 150);
	char *name = "Rotor disk by collective";
	dc.TextOut(p.x, p.y + 15, name, 24);
	
	p.x = 10 + 160;
	p.y = 460;
	origin_x2 = p.x;
	origin_y2 = p.y;
	drawCoordinateSystem(&dc, p, 150);
	char *name1 = "Rotor disk by pitch";
	dc.TextOut(p.x, p.y + 15, name1, 19);
	
	p.x = 10 + 2 * 160;
	p.y = 460;
	origin_x3 = p.x;
	origin_y3 = p.y;
	drawCoordinateSystem(&dc, p, 150);
	char *name2 = "Rotor disk by roll";
	dc.TextOut(p.x, p.y + 15, name2, 18);
	// 不为绘图消息调用 CDialog::OnPaint()
}

void RotorDiskDemarcateDialog::drawCoordinateSystem(CPaintDC *dc, POINT origin, int length)
{

	dc->MoveTo(origin.x, origin.y - length);
	dc->LineTo(origin.x, origin.y);
	dc->LineTo(origin.x + length, origin.y);

	dc->MoveTo(origin.x - 5, origin.y - length + 5);
	dc->LineTo(origin.x, origin.y - length - 5);
	dc->LineTo(origin.x + 5, origin.y - length + 5);
	
	dc->MoveTo(origin.x + length - 5, origin.y - 5);
	dc->LineTo(origin.x + length + 5, origin.y);
	dc->LineTo(origin.x + length - 5, origin.y + 5);

	char *originText = "0";
	dc->TextOut(origin.x, origin.y + 2, originText, 1);
	step = length / 5;

	char *originText1 = "25%";
	dc->MoveTo(origin.x + step, origin.y);
	dc->LineTo(origin.x + step, origin.y - 3);
	dc->TextOut(origin.x + step - 10, origin.y + 2, originText1, 3);

	char *originText2 = "50%";
	dc->MoveTo(origin.x + 2 * step, origin.y);
	dc->LineTo(origin.x + 2 * step, origin.y - 3);
	dc->TextOut(origin.x + 2 * step - 10, origin.y + 2, originText2, 3);

	char *originText3 = "75%";
	dc->MoveTo(origin.x + 3 * step, origin.y);
	dc->LineTo(origin.x + 3 * step, origin.y - 3);
	dc->TextOut(origin.x + 3 * step - 10, origin.y + 2, originText3, 3);

	char *originText4 = "100%";
	dc->MoveTo(origin.x + 4 * step, origin.y);
	dc->LineTo(origin.x + 4 * step, origin.y - 3);
	dc->TextOut(origin.x + 4 * step - 10, origin.y + 2, originText4, 4);

}
