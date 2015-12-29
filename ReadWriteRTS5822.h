
// ReadWriteRTS5822.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CReadWriteRTS5822App:
// See ReadWriteRTS5822.cpp for the implementation of this class
//

class CReadWriteRTS5822App : public CWinApp
{
public:
	CReadWriteRTS5822App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CReadWriteRTS5822App theApp;