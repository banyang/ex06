
// ReadWriteRTS5822Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadWriteRTS5822.h"
#include "ReadWriteRTS5822Dlg.h"
#include "afxdialogex.h"

#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadWriteRTS5822Dlg dialog



CReadWriteRTS5822Dlg::CReadWriteRTS5822Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READWRITERTS5822_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadWriteRTS5822Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadWriteRTS5822Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_WRITE_SN, &CReadWriteRTS5822Dlg::OnBnClickedButtonWriteSn)
	ON_BN_CLICKED(IDC_BUTTON_READ_SN, &CReadWriteRTS5822Dlg::OnBnClickedButtonReadSn)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CReadWriteRTS5822Dlg message handlers

BOOL CReadWriteRTS5822Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_bResult = FALSE ;

	if (m_RvcLib.LoadRvcLib())
	{
		m_RvcLib.LoadRvcFun() ;

		if (m_RvcLib.m_pfnRvcLib_Initialize)
		{
			m_RvcLib.m_pfnRvcLib_Initialize(0, 2);

			m_devIndex = 0 ;
			m_devInst  = m_RvcLib.m_pfnUvcOpen(m_devIndex);
			m_pWriteSN = new char[12];
			m_pReadSN  = new char[12];
			memset(m_pWriteSN, 0, 12);
			memset(m_pReadSN, 0, 12);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReadWriteRTS5822Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReadWriteRTS5822Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReadWriteRTS5822Dlg::OnBnClickedButtonWriteSn()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	UINT len = sizeof(m_pWriteSN) / sizeof(m_pWriteSN[0]) ;
	CString str = "" ;
	CString tmp = "" ;

	// Get serial no string
	((CButton *)(GetDlgItem(IDC_EDIT_WRITE_SN)))->GetWindowText(str) ;

	// Convertt string to char array
	m_pWriteSN = str.GetBuffer(str.GetLength()) ;
	tmp.Format("%s", m_pWriteSN) ;

	OutputDebugString(tmp) ;

    if (m_RvcLib.WriteSN(m_devInst, m_pWriteSN, 6))
	{ 
		printf("Write Serial number = %s \n", m_pWriteSN) ;
	}
	else
	{
		printf("Write Serial number failed.\n") ;
	}
}

void CReadWriteRTS5822Dlg::OnBnClickedButtonReadSn()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	UINT len = sizeof(m_pReadSN) / sizeof(m_pReadSN[0]);
	CString str = _T("");

	if (m_RvcLib.ReadSN(m_devInst, m_pReadSN, len))
	{
		printf("Read Serial number = %s \n", m_pReadSN);
		str.Format("%s", m_pReadSN) ;
		((CButton *)(GetDlgItem(IDC_STATIC_READ_SN)))->SetWindowText(str) ;
	}
	else
	{
		printf("Read Serial number failed.\n");
	}
}


void CReadWriteRTS5822Dlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_RvcLib.m_pfnUvcClose(m_devInst);
	m_RvcLib.m_pfnRvcLib_UnInitialize(2);

	CDialogEx::OnClose();
}
