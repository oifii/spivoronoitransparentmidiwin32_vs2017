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

/////////////////////////////////////////////////////////////////////////////
// AutoRescaleOW2doc.h : interface of the CAutoRescaleOW2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _AUTORESCALEOW2DOC_H
#define _AUTORESCALEOW2DOC_H

class CAutoRescaleOW2Doc : public COW2Doc
{
public: // create from serialization only
	CAutoRescaleOW2Doc();
	CAutoRescaleOW2Doc(HWND hwnd); 

	DECLARE_DYNCREATE(CAutoRescaleOW2Doc)

	virtual ~CAutoRescaleOW2Doc();

	virtual class COWPixelset* OpenFileAsPixelset(LPCTSTR lpszPathName); 

};

#endif
