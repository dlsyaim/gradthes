// FPSFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "GTDoc.h"
#include "FPSFormView.h"


// CFPSFormView

IMPLEMENT_DYNCREATE(CFPSFormView, CFormView)

CFPSFormView::CFPSFormView()
	: CFormView(CFPSFormView::IDD)
	, mapLongitude(0)
	, mapLatitude(0)
	, jointZCoordinate(0)
{

}

CFPSFormView::~CFPSFormView()
{
}

void CFPSFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAP_LONGITUDE_EDIT, mapLongitude);
	DDX_Text(pDX, IDC_MAP_LATITUDE_EDIT, mapLatitude);
	DDX_Text(pDX, IDC_POINT_Z_COORDINATE, jointZCoordinate);
	DDX_Control(pDX, IDC_MAP_PICTURE_CONTROL, m_Map);
}

BEGIN_MESSAGE_MAP(CFPSFormView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFPSFormView 诊断

#ifdef _DEBUG
void CFPSFormView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CFPSFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CFPSFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFPSFormView 消息处理程序

int CFPSFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->fpsFormView = this;

	return 0;
}


/* 
 * Function LoadAnImage: accepts a file name and returns a HBITMAP.
 * On error, it returns 0.
 */
HBITMAP CFPSFormView::LoadAnImage(CString fileName)
{
	// Use IPicture stuff to use JPG / GIF files
    IPicture* p;
    IStream* s;
    IPersistStream* ps;
    HGLOBAL hG;
    void* pp;
    FILE* fp;


   // Read file into memory
   errno_t erno = fopen_s(&fp, fileName, "rb");
   if (fp)
	   return NULL;

   /*
    * SEEK_END:End of file
	* SEEK_CUR:Current position of file
	* SEEK_SET:Beginning of file
	*/
   fseek(fp, 0, SEEK_END);
   int fs = ftell(fp);
   fseek(fp, 0, SEEK_SET);
   // Allocates the specified number of bytes from the heap
   hG = GlobalAlloc(GPTR,fs);
   if (!hG)
   {
	   fclose(fp);
       return NULL;
   }
   pp = (void*)hG;
   fread(pp, 1, fs, fp);
   fclose(fp);

   // Create an IStream stored in global memory
   CreateStreamOnHGlobal(hG, false, &s);
   if (!s)
      {
      GlobalFree(hG);
      return NULL;
      }

   OleLoadPicture(s,0,false,IID_IPicture,(void**)&p);

   if (!p)
      {
      s->Release();
      GlobalFree(hG);
      return NULL;
      }
   s->Release();
   GlobalFree(hG);

   HBITMAP hB = 0;
   p->get_Handle((unsigned int*)&hB);

   // Copy the image. Necessary, because upon p's release,
   // the handle is destroyed.
   HBITMAP hBB = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,
                                    LR_COPYRETURNORG);

   p->Release();
   return hBB;
   }
