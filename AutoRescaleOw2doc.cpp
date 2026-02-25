/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "stdafx.h"
#include "oifiilib.h" //note: oifiilib.lib/.dll is an MFC extension and resource DLL
#include "AutoRescaleOw2doc.h"
#include "FreeImagePlus.h"
#include "utility.h"

IMPLEMENT_DYNCREATE(CAutoRescaleOW2Doc, COW2Doc)

/*
BEGIN_MESSAGE_MAP(CAutoRescaleOW2Doc, COW2Doc)
	//{{AFX_MSG_MAP(CAutoRescaleOW2Doc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoRescaleOW2Doc, COW2Doc)
	//{{AFX_DISPATCH_MAP(CAutoRescaleOW2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
*/


/////////////////////////////////////////////////////////////////////////////
// COW2Doc construction/destruction

CAutoRescaleOW2Doc::CAutoRescaleOW2Doc(HWND hwnd) : COW2Doc(hwnd)
{
}

CAutoRescaleOW2Doc::CAutoRescaleOW2Doc() : COW2Doc()
{
}

CAutoRescaleOW2Doc::~CAutoRescaleOW2Doc()
{	
}

COWPixelset* CAutoRescaleOW2Doc::OpenFileAsPixelset(LPCTSTR lpszPathName) 
{
	//::MessageBoxA(NULL,"yo", "yo yo", MB_OK);

	COWPixelset* pPixelset = NULL;

 	//CLogDocument* pLogDocument = NULL; //spi 2014
	//if(m_parentHWND==NULL) pLogDocument = ((COIIIApp*)AfxGetApp())->GetLogDocument();


	//1) if file is a raster image file
 	wchar_t pszMessage[1024];
	wchar_t pszCharBuf[1024];
	wcscpy(pszCharBuf, lpszPathName);

	//int iType;
	//accusoft supported raster file format
	pPixelset = new COWPixelset;

	wsprintf(pszMessage, L"Loading pixelset ... ");
	fipWinImage myfipWinImage;
	//2021fev08, spi, begin
	BOOL bResult;
	if (myfipWinImage.identifyFIF(utf8_encode(pszCharBuf).c_str()) == FIF_JPEG)
	{
		bResult = myfipWinImage.load(utf8_encode(pszCharBuf).c_str(), JPEG_EXIFROTATE);
	}
	else
	{
		bResult = myfipWinImage.load(utf8_encode(pszCharBuf).c_str());
	}
	//2021fev08, spi, end
	
	if(bResult==FALSE)
	{
		//if(m_parentHWND==NULL) pLogDocument->AddText("error\r\nERROR loading pixelset.\r\n");
		delete pPixelset;
		return NULL;
	}
	//if(m_parentHWND==NULL) pLogDocument->AddText("done.\r\n");

	BITMAPINFOHEADER* pBITMAPINFOHEADER=const_cast<BITMAPINFOHEADER*>(myfipWinImage.getInfoHeader());
	
	int new_width = pBITMAPINFOHEADER->biWidth - pBITMAPINFOHEADER->biWidth%4;
	int new_height = pBITMAPINFOHEADER->biHeight;
	myfipWinImage.rescale(new_width, new_height, FILTER_BICUBIC);
	pBITMAPINFOHEADER= const_cast<BITMAPINFOHEADER*>(myfipWinImage.getInfoHeader());
	

	pPixelset->AllocDIB(pBITMAPINFOHEADER);
	pPixelset->UpdateDIBFrom(pBITMAPINFOHEADER);


	//set the view parameter directly into this document's m_pViewDataSettings 
	m_pViewDataSettings->bDrawPixelset = TRUE;

	if(pPixelset->IsDIBPresent() && !(pPixelset->IsBIIPresent()) )
	{
		//if(m_parentHWND==NULL) pLogDocument->AddText("     Allocating pixelset buffer ... ");
		if(pPixelset->AllocBII(pPixelset->GetDIBPointer())==FALSE)
		{
			//if(m_parentHWND==NULL) pLogDocument->AddText("Error\r\nError, not enough memory to alloc BII buffer, can't perform texture extraction\r\n");
			delete pPixelset;
			return NULL; //error
		}
		pPixelset->UpdateBIIFrom(pPixelset->GetDIBPointer());
		//if(m_parentHWND==NULL) pLogDocument->AddText("done.\r\n");
	}
		
	return pPixelset;
	/*
    char* pszFileExtension = strrchr((char*)lpszPathName,'.');
	pszFileExtension = _strupr( pszFileExtension );
 	if(pszFileExtension!=NULL  &&  strcmp(pszFileExtension, ".RAW") == 0)
	{
		if(m_parentHWND==NULL) pLogDocument->AddText("Sorry, RAW format not supported yet.\r\n");
		delete pPixelset;
		return NULL; //error
	}

	return NULL;
	*/
	//return COW2Doc::OpenFileAsPixelset(lpszPathName);
}