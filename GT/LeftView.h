#pragma once
#include <vector>
#include "GSDefinition.h"
// CLeftView 窗体视图
class CGTDoc;
class CCurveCtrl;

typedef std::pair<float, float> float_pair;

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFT_FORMVIEW };
	enum FE_STATE {
		STOPED,
		STARTED
	};
	CGTDoc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
// Attributes
	int feHour;
	int feMinute;
	int feSecond;
	double feRoll;
	double feRollUpper;
	double feRollLower;
	double fePitch;
	double fePitchUpper;
	double fePitchLower;
	double feHead;
	double feHeadUpper;
	double feHeadLower;
	CString feFileName;
	// The curve control pointer
	CCurveCtrl *m_pRollCurveCtrl, *m_pPitchCurveCtrl, *m_pHeadCurveCtrl;
// Operations
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedFEStart();
	afx_msg void OnBnClickedFEStop();
	afx_msg LRESULT OnStartTaskReply(WPARAM w, LPARAM l);
	afx_msg LRESULT OnStopTaskReply(WPARAM w, LPARAM l);
	afx_msg LRESULT OnFlyingStateData(WPARAM w, LPARAM l);

	// Setters and getter
	inline void setIsStart(__int32* tmp) {this->isStart = tmp;}
	inline void setIsStop(__int32* tmp) {this->isStop = tmp;}
	inline void setNewestFSG(pFlyStateGroup newestFSG) {this->newestFSG = newestFSG;}

private:
// Attributes
	__int32 *isStart;
	__int32 *isStop;
	// The newest coming fly state group
	pFlyStateGroup newestFSG;
	std::vector<float> rollCurveData;
	std::vector<float> pitchCurveData;
	std::vector<float> headCurveData;
	
	// Buffer for the fly state group
	std::vector<FlyStateGroup> bufFSG;

	// The serial of the fly state group we expect to arrive
	unsigned short expect;
	// Start time and end time
	CTime startTime, endTime;
	// Experiment data
	ExperimentData ed;

// Operations
	void updateCurve(void);

	// Serialize the fly state group
	void serialize(BOOL isForce = FALSE);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CGTDoc* CLeftView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif

