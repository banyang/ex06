
// ReadWriteRTS5822Dlg.h : header file
//

#pragma once

#include "RvcLibFun.h"

// CReadWriteRTS5822Dlg dialog
class CReadWriteRTS5822Dlg : public CDialogEx
{
// Construction
public:
	CReadWriteRTS5822Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READWRITERTS5822_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CRvcLibFun  m_RvcLib ;
	BOOL        m_bResult ;
	BOOL        m_bLoadStatus ;
	DWORD       m_devIndex ;
	DWORD       m_devInst ;
	char       * m_pWriteSN ;
	char       * m_pReadSN ;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWriteSn();
	afx_msg void OnBnClickedButtonReadSn();
	afx_msg void OnClose();
};
