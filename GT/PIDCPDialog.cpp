// PIDCPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "PIDCPDialog.h"
#include "Singleton.h"

#define ROW_COUNT 12
#define COL_COUNT 9

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
	ON_BN_CLICKED(IDCANCEL, &CPIDCPDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPIDCPDialog 消息处理程序

BOOL CPIDCPDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	m_Grid.SetEditable(TRUE);

	try {
		m_Grid.SetRowCount(ROW_COUNT + 1);
		m_Grid.SetColumnCount(COL_COUNT + 1);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	// Just fill the column headings
	int col, row;
	for (col = 1; col < m_Grid.GetColumnCount(); col++) {
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.row = 0;
		Item.col = col;
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

	// Just fill the column headings
	for (row = 1; row < m_Grid.GetRowCount(); row++) {
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = row;
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
	this->UpdateData(TRUE);
	/***** Gain the socket cliet  *****/
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();

	/***** Construct the command's data *****/
	char command[34];
	__int32* c = (__int32*)command;
	c[0] = TPT_LOADCONTROLPARA;


	/***** Attention the index starts from 1 *****/
	ControlPara cp;
	int i, j;
	CString paraName;
	for (i = 1; i < m_Grid.GetRowCount(); i++) {
		switch (i) {
			case 1:
				paraName.Append(_T("px_"));
				break;
			case 2:
				paraName.Append(_T("py_"));
				break;
			case 3:
				paraName.Append(_T("pz_"));
				break;
			case 4:
				paraName.Append(_T("vx_"));
				break;
			case 5:
				paraName.Append(_T("vy_"));
				break;
			case 6:
				paraName.Append(_T("vz_"));
				break;
			case 7:
				paraName.Append(_T("psi"));
				break;
			case 8:
				paraName.Append(_T("phi"));
				break;
			case 9:
				paraName.Append(_T("theta"));
				break;
			case 10:
				paraName.Append(_T("vpsi"));
				break;
			case 11:
				paraName.Append(_T("vphi"));
				break;
			case 12:
				paraName.Append(_T("vtheta"));
				break;
			default:
				break;
		}
		for (j = 1; j < m_Grid.GetColumnCount(); j++) {
			paraName.Append(m_Grid.GetItemText(0, j));
			memcpy(cp.paraname, paraName.GetBuffer(0), sizeof(cp.paraname));
			/*
			 * 'l' represents long type
			 * 'b' represents bool type
			 * 'f' represents float type
			 */
			cp.type = 'f';
			CString itemText = m_Grid.GetItemText(i, j);
			sscanf_s(itemText, "%f", &cp.vf);	
			memcpy(command + 2, (char *)&cp, sizeof(cp));
			cln->SendSvr(command, sizeof(command));
		}
	}

	/***** Save the control paramters into files *****/

	CSingleton *instance = CSingleton::getInstance();
	static int version = 0;
	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("%Y-%m-%d");
	CString verStr;	
	
	/***** Set the global flag variable *****/
	instance->setIsControlParameterSet(TRUE);
	/* And need to save the data into the files */
	verStr.Format(_T("-%d.cp"), version++);
	timeString.Append(verStr);
	instance->setRecentCPName(timeString);
	std::ofstream ofs(timeString, std::ios::binary);
	ofs.write((char*) &cp, sizeof(cp));
	ofs.close();
	OnOK();
}

void CPIDCPDialog::OnBnClickedCancel()
{
	CSingleton* instance = CSingleton::getInstance();
	instance->setIsControlParameterSet(FALSE);
	OnCancel();
}
