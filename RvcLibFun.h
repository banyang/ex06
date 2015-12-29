#pragma once

//#include "User.h"

typedef BOOL(*pfn_RvcLib_Initialize)(BOOL bInternalLog, BOOL bLibType);
typedef BOOL(*pfn_RvcLib_UnInitialize)(BOOL bLibType);
typedef DWORD(*pfn_UvcOpen)(DWORD index);
typedef BOOL(*pfn_UvcClose)(DWORD devInst);
typedef BOOL(*pfn_ReadSN)(DWORD devInst, char* pSN, UINT& len);
typedef BOOL(*pfn_WriteSN)(DWORD devInst, char* pSN, UINT len);


class CRvcLibFun
{
public:
	CRvcLibFun(void);
	~CRvcLibFun(void);

public:
	BOOL LoadRvcLib();
	BOOL LoadRvcFun();
	void FreeRvcLib();

	HINSTANCE		m_hLib;

public:
	pfn_RvcLib_Initialize   m_pfnRvcLib_Initialize;
	pfn_RvcLib_UnInitialize m_pfnRvcLib_UnInitialize;
	pfn_UvcOpen m_pfnUvcOpen;
	pfn_UvcClose m_pfnUvcClose;
	pfn_ReadSN m_pfnReadSN;
	pfn_WriteSN m_pfnWriteSN;

public:
	BOOL    RvcLib_Initialize(BOOL bInternalLog, BOOL bLibType);
	BOOL    RvcLib_UnInitialize(BOOL bLibType);
	DWORD   UvcOpen(DWORD index);
	void    UvcClose(DWORD devInst);
	BOOL	ReadSN(DWORD devInst, char* pSN, UINT& len);
	BOOL	WriteSN(DWORD devInst, char* pSN, UINT len);
};

