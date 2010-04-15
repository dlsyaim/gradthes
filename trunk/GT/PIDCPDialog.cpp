// PIDCPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "PIDCPDialog.h"


// CPIDCPDialog 对话框

IMPLEMENT_DYNAMIC(CPIDCPDialog, CDialog)

CPIDCPDialog::CPIDCPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPIDCPDialog::IDD, pParent)
{

}

CPIDCPDialog::~CPIDCPDialog()
{
}

void CPIDCPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_PID_CP, m_Grid);
}


BEGIN_MESSAGE_MAP(CPIDCPDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPIDCPDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CPIDCPDialog 消息处理程序

BOOL CPIDCPDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	m_Grid.SetEditable(TRUE);

	try {
		m_Grid.SetRowCount(13);
		m_Grid.SetColumnCount(10);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	int col, row;
	for (col = 1; col < m_Grid.GetColumnCount(); col++) {
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = col;

		Item.nFormat = DT_CENTER|DT_WORDBREAK | DT_NOPREFIX;
		switch (col) {
			case 1:
				Item.strText.Format(_T("Kp"));
				break;
			case 2:
				Item.strText.Format(_T("Kp_Max"));
				break;
			case 3:
				Item.strText.Format(_T("Kp_Min"));
				break;
			case 4:
				Item.strText.Format(_T("Ki"));
				break;
			case 5:
				Item.strText.Format(_T("Ki_Max"));
				break;
			case 6:
				Item.strText.Format(_T("Ki_Min"));
				break;
			case 7:
				Item.strText.Format(_T("Kd"));
				break;
			case 8:
				Item.strText.Format(_T("Kd_Max"));
				break;
			case 9:
				Item.strText.Format(_T("Kd_Min"));
				break;
			default:
				break;
		}
		m_Grid.SetItem(&Item);
	}

	for (row = 1; row < m_Grid.GetRowCount(); row++) {
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.col = 0;
		Item.row = row;

		Item.nFormat = DT_CENTER|DT_WORDBREAK;
		switch (row) {
			case 1:
				Item.strText.Format(_T("P(x)"));
				break;
			case 2:
				Item.strText.Format(_T("P(y)"));
				break;
			case 3:
				Item.strText.Format(_T("P(z)"));
				break;
			case 4:
				Item.strText.Format(_T("V(x)"));
				break;
			case 5:
				Item.strText.Format(_T("V(y)"));
				break;
			case 6:
				Item.strText.Format(_T("V(z)"));
				break;
			case 7:
				Item.strText.Format(_T("Psi"));
				break;
			case 8:
				Item.strText.Format(_T("Phi"));
				break;
			case 9:
				Item.strText.Format(_T("Theta"));
				break;
			case 10:
				Item.strText.Format(_T("V(Psi)"));
				break;
			case 11:
				Item.strText.Format(_T("V(Phi)"));
				break;
			case 12:
				Item.strText.Format(_T("V(Theta)"));
				break;
			default:
				break;
		}
		m_Grid.SetItem(&Item);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPIDCPDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	/***** Attention start from 1 *****/
	/*
		PID pid;
		memset(&pid, 0, sizeof(pid));
	 */
	int i, j;
	for (i = 1; i < m_Grid.GetRowCount(); i++) {
		for (j = 1; j < m_Grid.GetColumnCount(); j++) {
			CString itemText = m_Grid.GetItemText(i, j);
			/*
				sscanf(itemText, "%f", pid.);
			 */
		}
	}

	OnOK();
}
