
// GTDoc.h : interface of the CGTDoc class
//


#pragma once
class CLeftView;
class CGTView;
class CUpperRightView;
class CGridView;
class CIMUTestFormView;
class CDPLeftFormView;
class CDPUpperRightView;
class CGTDoc : public CDocument
{
protected: // create from serialization only
	CGTDoc();
	DECLARE_DYNCREATE(CGTDoc)

// Attributes
public:
	CLeftView* leftView;
	CGTView* lowerRightView;
	CUpperRightView* upperRightView;
	CGridView* gridView;
	CIMUTestFormView* IMUView;
	CDPLeftFormView* dpLeftView;
	CDPUpperRightView* dpUpperRightView;
private:
	// A CFile pointer to the file which contains the flying statistics
	CFile *sharedFile;


// Operations
public:
	inline CFile* getSharedFile(void) {return sharedFile;}
	inline void setSharedFile(CFile* sharedFile) {this->sharedFile = sharedFile;}
	// Get the next line of the file
	
	// Get the 9 flight state variable value
	BOOL getFlyStatistics(double *stat, int size);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


 