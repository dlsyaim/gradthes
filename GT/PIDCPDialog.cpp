// PIDCPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "PIDCPDialog.h"
#include "Singleton.h"
#include "PIDCPDialogController.h"

#define ROW_COUNT 12
#define COL_COUNT 9

bool operator== (const ControlPara &cp1, const ControlPara &cp2)
{
	return !strcmp(cp1.paraname, cp2.paraname)
		&& cp1.type == cp2.type
		&& cp1.vb == cp2.vb
		&& cp1.vf == cp2.vf
		&& cp1.vl == cp2.vl;
}

// CPIDCPDialog 对话框

IMPLEMENT_DYNAMIC(CPIDCPDialog, CDialog)

CPIDCPDialog::CPIDCPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPIDCPDialog::IDD, pParent)
{
	controller = new CPIDCPDialogController();
}

CPIDCPDialog::~CPIDCPDialog()
{
	if (controller)
		delete controller;
}

void CPIDCPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_CUSTOM_PID_CP, m_Grid);
}


BEGIN_MESSAGE_MAP(CPIDCPDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPIDCPDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPIDCPDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPEN_CP_BTN, &CPIDCPDialog::OnBnClickedOpenCPBtn)
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
	m_Grid.ExpandColumnsToFit(FALSE);

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
	m_Grid.ExpandRowsToFit(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPIDCPDialog::OnBnClickedOk()
{
	UpdateData(TRUE);
	// Get the socket cliet
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();

	// Construct the control parameters' data
	char command[sizeof(ControlPara) + 2];
	__int16* c = (__int16*)command;
	c[0] = TPT_LOADCONTROLPARA;

	CSingleton *instance = CSingleton::getInstance();

	std::vector<ControlPara>* PCPV = instance->getCPV();
	std::vector<ControlPara> copy;
	bool isChange = false;
	
	// Attention the index starts from 1
	ControlPara cp;
	// Initialize to zero
	memset(&cp, 0, sizeof(cp));
	int i, j;
	CString paraName, totalParaName;
	for (i = 1; i < m_Grid.GetRowCount(); i++) {
		paraName.Empty();
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
			totalParaName = paraName + m_Grid.GetItemText(0, j);
			memcpy(cp.paraname, totalParaName.GetBuffer(0), sizeof(cp.paraname));
			/*
			 * 'l' represents long type
			 * 'b' represents bool type
			 * 'f' represents float type
			 */
			cp.type = 'f';
			CString itemText = m_Grid.GetItemText(i, j);
			cp.vf = (float) atof((LPCTSTR)itemText);
			memcpy(command + 2, (char *)&cp, sizeof(cp));
			cln->SendSvr(command, sizeof(command));
			copy.push_back(cp);
		}
	}
	if (!isChange) {
		if (copy == controlParameterVector) {
			isChange = false;
		} else {
			isChange = true;
		}
	}
    // Set the global state variable
	instance->setIsControlParameterSet(TRUE);

	if (isChange) {		
		PCPV->clear();
		std::vector<ControlPara>::iterator iter;
		for (iter = copy.begin(); iter != copy.end(); iter++) {
			PCPV->push_back(*iter);
		}
		if (controller->checkControlParameter(instance->getCurControlParameterFileName())) {
			CString namePrefix;
			while (true) {
				CPIDNamePrefixDialog pidNamePrefix;
				if (pidNamePrefix.DoModal() == IDOK) {
					if (pidNamePrefix.namePrefix.GetLength() != 0) {
						namePrefix = pidNamePrefix.namePrefix;
						break;
					}
				}
			}
			controller->saveControlParaFile(namePrefix, PCPV);
		} else {
			controller->updateControlParaFile(PCPV);
		}		
	}

	instance->updateCurConfiguration();
	TRACE("Current CP: %s\n", instance->getCS()->controlParameterFileName);
	CDialog::OnOK();
}

void CPIDCPDialog::OnBnClickedCancel()
{
	CSingleton* instance = CSingleton::getInstance();
	TRACE("Current CP: %s\n", instance->getCS()->controlParameterFileName);

	CDialog::OnCancel();
}

void CPIDCPDialog::OnBnClickedOpenCPBtn()
{
	char szFilter[] = {"All Files (*.*)|*.*||"};
	controlParameterVector.clear();
	CFileDialog openDlg(TRUE, NULL, NULL, 0, szFilter);
	if (openDlg.DoModal() == IDOK) {
		CString fileName = openDlg.GetFileName();
		controller->openControlParaFile(fileName, &controlParameterVector);
		// Update the grid
		updateGrid(&controlParameterVector);
	}
}


void CPIDCPDialog::updateGrid(std::vector<ControlPara> *PCMV)
{
	if (!PCMV)
		return;
	if (PCMV->size() == 0)
		return;
	int i, j, index = 0;
	CString text;
	for (i = 1; i < m_Grid.GetRowCount(); i++) {
		for (j = 1; j < m_Grid.GetColumnCount(); j++) {
			if ((*PCMV)[index].type == 'l') {
				text.Format("%ld", (*PCMV)[index].vl);
			} else if ((*PCMV)[index].type == 'b') {
				text.Format("%d", (*PCMV)[index].vb);
			} else if ((*PCMV)[index].type == 'f') {
				text.Format("%.4g", (*PCMV)[index].vf);
			}
			index++;
			m_Grid.SetItemText(i, j, text);
		}
	}
	m_Grid.Invalidate();
	
	UpdateData(FALSE);
}
// E:\Workspace\Visual Studio 2008\GraduationThesis\GT\PIDCPDialog.cpp : implementation file
//


// CPIDNamePrefixDialog dialog

IMPLEMENT_DYNAMIC(CPIDNamePrefixDialog, CDialog)

CPIDNamePrefixDialog::CPIDNamePrefixDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPIDNamePrefixDialog::IDD, pParent)
	, namePrefix(_T(""))
{

}

CPIDNamePrefixDialog::~CPIDNamePrefixDialog()
{
}

void CPIDNamePrefixDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CP_NAME_PREFIX_EDIT, namePrefix);
}


BEGIN_MESSAGE_MAP(CPIDNamePrefixDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPIDNamePrefixDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CPIDNamePrefixDialog message handlers

void CPIDNamePrefixDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
