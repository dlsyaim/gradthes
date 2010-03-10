
// GTDoc.cpp : implementation of the CGTDoc class
//

#include "stdafx.h"
#include "GT.h"

#include "GTDoc.h"
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include "Util.h"
#include "SerialPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGTDoc

IMPLEMENT_DYNCREATE(CGTDoc, CDocument)

BEGIN_MESSAGE_MAP(CGTDoc, CDocument)
END_MESSAGE_MAP()


// CGTDoc construction/destruction

CGTDoc::CGTDoc()
{
	// TODO: add one-time construction code here
	sharedFile = new CStdioFile();
	CFileException e;
	// Open the file
	if (!sharedFile->Open(_T("data"), 
		// Read the file's content
		CFile::modeRead |
		// If the file exists, no truncate it.
		CFile::modeNoTruncate |
		// Deny other processes' reading and writing
		CFile::shareDenyNone, &e
		)) {
			if (sharedFile) {
				sharedFile->Close();
				delete sharedFile;
				sharedFile = NULL;
			}
			TRACE(_T("File could not be opened %d \n"), e.m_cause);
	}
}

// Get the 9 flight state variable value
BOOL CGTDoc::getFlyStatistics(double *stat, int size)
{
	if (!stat || size <= 0 || !sharedFile)
		return FALSE;

	int i = 0;
	char line[55];
	if (((CStdioFile*)sharedFile)->ReadString((LPTSTR)line, 55)) {
		sharedFile->Seek(2, CFile::current);
		
		// Split the string by ' ' character.
		std::istringstream ss(line);
		std::string sub;
		double value;
		do {
			ss >> sub;
			switch(i) {
				case 0:
					value = HexToDem(sub);
					break;
				default:
					value = HexToDem(sub, TRUE);
					break;
			}		
			if (i >= 6) {
				value /= 100.0;
			}
			stat[i++] = value;
		} while (ss && i < size);
	}

	return TRUE;	
}

CGTDoc::~CGTDoc()
{
	if (sharedFile)
	{
		sharedFile->Close();
		delete sharedFile;
	}

}

BOOL CGTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGTDoc serialization

void CGTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGTDoc diagnostics

#ifdef _DEBUG
void CGTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGTDoc commands
