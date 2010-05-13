// RotorDiskDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "RotorDiskDemarcateDialog.h"
#include "Singleton.h"


// RotorDiskDemarcateDialog 对话框

IMPLEMENT_DYNAMIC(RotorDiskDemarcateDialog, CDialog)

RotorDiskDemarcateDialog::RotorDiskDemarcateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(RotorDiskDemarcateDialog::IDD, pParent)
	, dyPitch(0)
	, dyRoll(0)
	, dyCollective(0)
	, stPitch(0)
	, stRoll(0)
	, stCollective(0)
	, convertedPitch(0)
	, convertedRoll(0)
	, convertedCollective(0)
{
	demarcatedIdx = 0;
	size = 0;
}

RotorDiskDemarcateDialog::~RotorDiskDemarcateDialog()
{
}

void RotorDiskDemarcateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DEMARCATE_ROTORDISK_TAB, m_tabRotorDisk);
	DDX_Text(pDX, IDC_DY_PITCH_EDIT, dyPitch);
	DDX_Text(pDX, IDC_DY_ROLL_EDIT, dyRoll);
	DDX_Text(pDX, IDC_DY_COLLECTIVE_EDIT, dyCollective);
	DDX_Text(pDX, IDC_ST_PITCH_EDIT, stPitch);
	DDX_Text(pDX, IDC_ST_ROLL_EDIT, stRoll);
	DDX_Text(pDX, IDC_ST_HEAD_EDIT, stCollective);
	DDX_Control(pDX, IDC_PITCH_SPIN, pitchSpin);
	DDX_Control(pDX, IDC_ROLL_SPIN, rollSpin);
	DDX_Control(pDX, IDC_COLLECTIVE_SPIN, collectiveSpin);
	DDX_Control(pDX, IDC_ROTOR_RESULT_LIST, demarcatedResult);
	DDX_Text(pDX, IDC_CONVERTED_PITCH_EDIT, convertedPitch);
	DDX_Text(pDX, IDC_CONVERTED_ROLL_EDIT, convertedRoll);
	DDX_Text(pDX, IDC_CONVERTED_COLLECTIVE_EDIT, convertedCollective);
}


BEGIN_MESSAGE_MAP(RotorDiskDemarcateDialog, CDialog)
	ON_WM_PAINT()
	ON_NOTIFY(UDN_DELTAPOS, IDC_PITCH_SPIN, &RotorDiskDemarcateDialog::OnDeltaposDyPitchSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ROLL_SPIN, &RotorDiskDemarcateDialog::OnDeltaposRollSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_COLLECTIVE_SPIN, &RotorDiskDemarcateDialog::OnDeltaposCollectiveSpin)
	ON_BN_CLICKED(IDC_SEND_ROTOR_BUTTON, &RotorDiskDemarcateDialog::OnBnClickedSendRotorButton)
	ON_BN_CLICKED(IDC_DEMARCATED_SUC_BTN, &RotorDiskDemarcateDialog::OnBnClickedDemarcatedSucBtn)
	ON_NOTIFY(NM_CLICK, IDC_ROTOR_RESULT_LIST, &RotorDiskDemarcateDialog::OnNMClickRotorResultList)
	ON_BN_CLICKED(IDCANCEL, &RotorDiskDemarcateDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_DY_PITCH_EDIT, &RotorDiskDemarcateDialog::OnEnChangeDyPitchEdit)
	ON_EN_CHANGE(IDC_DY_ROLL_EDIT, &RotorDiskDemarcateDialog::OnEnChangeDyRollEdit)
	ON_EN_CHANGE(IDC_DY_COLLECTIVE_EDIT, &RotorDiskDemarcateDialog::OnEnChangeDyCollectiveEdit)
END_MESSAGE_MAP()


// RotorDiskDemarcateDialog 消息处理程序

BOOL RotorDiskDemarcateDialog::OnInitDialog()
{

	CDialog::OnInitDialog();
	pitchSpin.SetRange(0, 1000);
	UDACCEL accelValue;
	accelValue.nInc = 1;
	accelValue.nSec = 1000;
	pitchSpin.SetAccel(1, &accelValue);

	rollSpin.SetRange(0, 1000);
	rollSpin.SetAccel(1, &accelValue);

	collectiveSpin.SetRange(0, 1000);
	collectiveSpin.SetAccel(1, &accelValue);

	demarcatedResult.SetExtendedStyle(LVS_EX_FULLROWSELECT | 
		LVS_EX_GRIDLINES);
	LVCOLUMN lvColumn;
	int nCol = 0;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 50;
	lvColumn.pszText = "Times";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 70;
	lvColumn.pszText = "Input Pitch";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 60;
	lvColumn.pszText = "Input Roll";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 90;
	lvColumn.pszText = "Input Collective";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 80;
	lvColumn.pszText = "Output Pitch";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 75;
	lvColumn.pszText = "Output Roll";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = "Output Collective";
	demarcatedResult.InsertColumn(nCol++, &lvColumn);
   // Setup the tab control
   /*int nPageID = 0;
   m_tabCollective.Create(IDD_COLLECTIVE_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage (_T("总距标定"), nPageID++, &m_tabCollective);
   m_tabRoll.Create(IDD_ROLL_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage(_T("侧滚舵机标定"), nPageID++, &m_tabRoll);
   m_tabPitch.Create(IDD_PITCH_ROTORDISK_TAB, this);
   m_tabRotorDisk.AddSSLPage(_T("俯仰舵机标定"), nPageID++, &m_tabPitch);*/
     return TRUE; // return TRUE unless you set the focus to a control
}

//void RotorDiskDemarcateDialog::OnPaint()
//{
//	//CPaintDC dc(this); // device context for painting
//	//// TODO: 在此处添加消息处理程序代码
//	//POINT p;
//	//p.x = 10;
//	//p.y = 460;
//	//origin_x1 = p.x;
//	//origin_y1 = p.y;
//	//drawCoordinateSystem(&dc, p, 150);
//	//char *name = "Rotor disk by collective";
//	//dc.TextOut(p.x, p.y + 15, name, 24);
//	//
//	//p.x = 10 + 160;
//	//p.y = 460;
//	//origin_x2 = p.x;
//	//origin_y2 = p.y;
//	//drawCoordinateSystem(&dc, p, 150);
//	//char *name1 = "Rotor disk by pitch";
//	//dc.TextOut(p.x, p.y + 15, name1, 19);
//	//
//	//p.x = 10 + 2 * 160;
//	//p.y = 460;
//	//origin_x3 = p.x;
//	//origin_y3 = p.y;
//	//drawCoordinateSystem(&dc, p, 150);
//	//char *name2 = "Rotor disk by roll";
//	//dc.TextOut(p.x, p.y + 15, name2, 18);
//	// 不为绘图消息调用 CDialog::OnPaint()
//}

void RotorDiskDemarcateDialog::drawCoordinateSystem(CPaintDC *dc, POINT origin, int length)
{

	/*dc->MoveTo(origin.x, origin.y - length);
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
	dc->TextOut(origin.x + 4 * step - 10, origin.y + 2, originText4, 4);*/

}

void RotorDiskDemarcateDialog::OnDeltaposDyPitchSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// First get the current value of dyPitch
	UpdateData(TRUE);

	LPNMUPDOWN spin = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// The incremental is 0.1
	dyPitch += ((*spin).iDelta / 10.0);
	
	updateConvertedValue(1);

	UpdateData(FALSE);
	*pResult = 0;
}

void RotorDiskDemarcateDialog::OnDeltaposRollSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// First get the current value of dyRoll
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);	
	dyRoll += ((*pNMUpDown).iDelta) / 10.0;

	updateConvertedValue(2);
	
	UpdateData(FALSE);
	*pResult = 0;
}

void RotorDiskDemarcateDialog::OnDeltaposCollectiveSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// First get the current value of dyHead
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	dyCollective += ((*pNMUpDown).iDelta) / 10.0;

	updateConvertedValue(3);
	
	UpdateData(FALSE);
	*pResult = 0;
}

void RotorDiskDemarcateDialog::OnBnClickedSendRotorButton()
{
	/********** Construct the content of the servo actor demarcated data *********/
	UpdateData(TRUE);
	
	char command[sizeof(ServoActorTstInsData) + 2];
	__int16 *c = (__int16 *)command;
	c[0] = SAT_SERVOACTOR_TST;
	
	ServoActorTstInsData satt;
	satt.ActorSerial = 0;
	satt.SetPWM = convertedPitch;
	memcpy(&(command[2]), (char*)&satt, sizeof(satt));	

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));

	satt.ActorSerial = 1;
	satt.SetPWM = convertedRoll;
	memcpy(&(command[2]), (char*)&satt, sizeof(satt));	
	cln->SendSvr(command, sizeof(command));

	satt.ActorSerial = 2;
	satt.SetPWM = convertedCollective;
	memcpy(&(command[2]), (char*)&satt, sizeof(satt));	
	cln->SendSvr(command, sizeof(command));

	TRACE(_T("Sent: %f %f %f\n"), dyPitch, dyRoll, dyCollective);
	TRACE(_T("Sent: %f %f %f\n"), convertedPitch, convertedRoll, convertedCollective);
}

void RotorDiskDemarcateDialog::OnBnClickedDemarcatedSucBtn()
{
	if (size >= 10)
	{
		TRACE("Exceed the limit\n");
		AfxMessageBox(_T("Reach the ceiling\n"), MB_OK | MB_ICONWARNING);
		return;
	}
	// One group succeed
	UpdateData(TRUE);

	CSingleton *instance = CSingleton::getInstance();
	TiltDiscData* tdd = instance->getTDD();

	tdd->CommandAngs[demarcatedIdx][0] = (float)dyPitch;
	tdd->CommandAngs[demarcatedIdx][1] = (float)dyRoll;
	tdd->CommandAngs[demarcatedIdx][2] = (float)dyCollective;

	tdd->MeansureAngs[demarcatedIdx][0] = (float)stPitch;
	tdd->MeansureAngs[demarcatedIdx][1] = (float)stRoll;
	tdd->MeansureAngs[demarcatedIdx][2] = (float)stCollective;

	if (demarcatedIdx == size) {
		LVITEM lvItem;
		int nItem;
		
		CString buf;
		buf.Format("%d", demarcatedIdx);
		
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = demarcatedIdx;
		lvItem.iSubItem = 0;
		lvItem.pszText = (LPSTR)(LPCTSTR)buf;
		nItem = demarcatedResult.InsertItem(&lvItem);

		CString text;
		text.Format("%f", dyPitch);
		demarcatedResult.SetItemText(nItem, 1, text);
		text.Format("%f", dyRoll);
		demarcatedResult.SetItemText(nItem, 2, text);
		text.Format("%f", dyCollective);
		demarcatedResult.SetItemText(nItem, 3, text);
		text.Format("%f", stPitch);
		demarcatedResult.SetItemText(nItem, 4, text);
		text.Format("%f", stRoll);
		demarcatedResult.SetItemText(nItem, 5, text);
		text.Format("%f", stCollective);
		demarcatedResult.SetItemText(nItem, 6, text);
	} else {
		int nItem = demarcatedIdx;
		CString text;
		text.Format("%f", dyPitch);
		demarcatedResult.SetItemText(nItem, 1, text);
		text.Format("%f", dyRoll);
		demarcatedResult.SetItemText(nItem, 2, text);
		text.Format("%f", dyCollective);
		demarcatedResult.SetItemText(nItem, 3, text);
		text.Format("%f", stPitch);
		demarcatedResult.SetItemText(nItem, 4, text);
		text.Format("%f", stRoll);
		demarcatedResult.SetItemText(nItem, 5, text);
		text.Format("%f", stCollective);
		demarcatedResult.SetItemText(nItem, 6, text);
	}

	// Clear
	dyPitch = dyRoll = dyCollective = 0.0f;
	stPitch = stRoll = stCollective = 0.0f;

	UpdateData(FALSE);
	
	if (demarcatedIdx < size) {
		// Edit some line
		demarcatedIdx = size;
	} else {
		size++;
		demarcatedIdx = size;
	}
}

void RotorDiskDemarcateDialog::OnNMClickRotorResultList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	demarcatedIdx = pNMItemActivate->iItem;

	int iSubItem = 1;
	CString text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	dyPitch = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	dyRoll = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	dyCollective = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	stPitch = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	stRoll = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);
	stCollective = atof((LPCTSTR)text);
	text = demarcatedResult.GetItemText(pNMItemActivate->iItem, iSubItem++);

	UpdateData(FALSE);
	*pResult = 0;
}

void RotorDiskDemarcateDialog::OnBnClickedCancel()
{
	if (size < 10) {
		CSingleton *instance = CSingleton::getInstance();
		int result = AfxMessageBox(_T("Need 10 group data\nAre you sure to exit? If exit, all demarcated result will be lost.")
			, MB_YESNO | MB_ICONWARNING);
		switch (result) {
			case IDYES:
				// Will clear the demarcated result
				memset(instance->getTDD(), 0, sizeof(TiltDiscData));
				// Set the flag variable
				instance->setIsRotorDemarcated(FALSE);
				OnCancel();
				break;
			case IDNO:
				break;
			default:
				break;
		}

	} else {
		OnCancel();
	}
}

void RotorDiskDemarcateDialog::OnEnChangeDyPitchEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	updateConvertedValue(1);
}

void RotorDiskDemarcateDialog::OnEnChangeDyRollEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	updateConvertedValue(2);
}

void RotorDiskDemarcateDialog::OnEnChangeDyCollectiveEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	updateConvertedValue(3);
}

// Convert dyPitch into PWM
void RotorDiskDemarcateDialog::updateConvertedValue(int channel)
{
	PHelicopterModel curPHM = CSingleton::getInstance()->getCurPHM();
	float differ;
	switch (channel) {
		case 1:
			differ = curPHM->sad.a1PWMValue[0] - curPHM->sad.a1PWMValue[4];
			if (differ == 0.0f) {
				convertedPitch = 0.0f;
			} else {
				convertedPitch = ((float)dyPitch - curPHM->sad.a1MeansureAng[4]) / (curPHM->sad.a1MeansureAng[0] - curPHM->sad.a1MeansureAng[4]) * differ
					+ curPHM->sad.a1PWMValue[4];
			}
			break;
		case 2:
			 differ = curPHM->sad.a2PWMValue[0] - curPHM->sad.a2PWMValue[4];
			if (differ == 0.0f) {
				convertedRoll = 0.0f;
			} else {
				convertedRoll = ((float)dyRoll - curPHM->sad.a2MeansureAng[4]) / (curPHM->sad.a2MeansureAng[0] - curPHM->sad.a2MeansureAng[4]) * differ 
					+ curPHM->sad.a2PWMValue[4];
			}
			break;
		case 3:
			differ = curPHM->sad.a3PWMValue[0] - curPHM->sad.a3PWMValue[4];
			if (differ == 0.0f) {
				convertedCollective = 0.0f;
			} else {
				convertedCollective = ((float)dyCollective - curPHM->sad.a3MeansureAng[4]) / (curPHM->sad.a3MeansureAng[0] - curPHM->sad.a3MeansureAng[4]) * differ
					+ curPHM->sad.a3PWMValue[4];
			}
			break;
		default:
			break;
	}

	UpdateData(FALSE);	
}
