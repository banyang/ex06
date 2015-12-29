#include "StdAfx.h"
#include "RvcLibFun.h"


CRvcLibFun::CRvcLibFun(void)
{
	m_hLib = NULL;
}

CRvcLibFun::~CRvcLibFun(void)
{
	if (m_hLib != NULL) 
	{
		FreeLibrary(m_hLib);
	}
}

BOOL CRvcLibFun::LoadRvcLib()
{
	BOOL bResult = FALSE;

	FreeRvcLib();
#ifdef _DEBUG
	m_hLib = LoadLibrary("RvcLib.dll") ;
#else
	m_hLib = LoadLibrary("RvcLib.dll") ;
#endif
	if (m_hLib != NULL)
	{
		bResult = TRUE;
	}

	return bResult;
}

void CRvcLibFun::FreeRvcLib()
{
	if (m_hLib != NULL) 
	{
		FreeLibrary(m_hLib);
	}

	m_hLib = NULL;
	m_pfnRvcLib_Initialize = NULL;
	m_pfnRvcLib_UnInitialize = NULL;
	m_pfnUvcOpen = NULL;
	m_pfnUvcClose = NULL;
	m_pfnReadSN = NULL;
	m_pfnWriteSN = NULL;

}   

BOOL CRvcLibFun::LoadRvcFun()
{   
	BOOL bResult = TRUE;

	m_pfnRvcLib_Initialize = (pfn_RvcLib_Initialize) GetProcAddress(m_hLib, ("RvcLib_Initialize"));
	m_pfnRvcLib_UnInitialize = (pfn_RvcLib_UnInitialize) GetProcAddress(m_hLib, ("RvcLib_UnInitialize"));
	m_pfnUvcOpen = (pfn_UvcOpen)GetProcAddress(m_hLib, ("UVC_Open"));
	m_pfnUvcClose = (pfn_UvcClose)GetProcAddress(m_hLib, ("UVC_Close"));
	m_pfnReadSN = (pfn_ReadSN)GetProcAddress(m_hLib, ("ReadSN"));
	m_pfnWriteSN = (pfn_WriteSN)GetProcAddress(m_hLib, ("WriteSN"));

	return bResult;
}

//
BOOL CRvcLibFun::RvcLib_Initialize(BOOL bInternalLog, BOOL bLibType)
{
	BOOL bResult = FALSE;

	if (NULL != m_pfnRvcLib_Initialize)
	{
		bResult = m_pfnRvcLib_Initialize(bInternalLog, bLibType);
	}

	return bResult;
}

BOOL CRvcLibFun::RvcLib_UnInitialize(BOOL bLibType)
{
	BOOL bResult = FALSE;

	if(NULL != m_pfnRvcLib_UnInitialize)
	{
		bResult = m_pfnRvcLib_UnInitialize(bLibType);
	}

	return bResult;
}

DWORD CRvcLibFun::UvcOpen(DWORD index)
{
	DWORD devInst = NULL;

	if(NULL != m_pfnUvcOpen)
	{
		devInst = m_pfnUvcOpen(index);
	}

	return devInst;
}

void  CRvcLibFun::UvcClose(DWORD devInst)
{
	if(NULL != m_pfnUvcClose)
	{
		m_pfnUvcClose(devInst);
	}
}

BOOL CRvcLibFun::ReadSN(DWORD devInst, char* pSN, UINT& len)
{
	if (0 != devInst)
	{
		return m_pfnReadSN(devInst, pSN, len);
	}

	return FALSE;
}

BOOL CRvcLibFun::WriteSN(DWORD devInst, char* pSN, UINT len)
{
	if (0 != devInst)
	{
		return m_pfnWriteSN(devInst, pSN, len);
	}

	return FALSE;
}

