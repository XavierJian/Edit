
// MyNodeBooksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyNodeBooks.h"
#include "MyNodeBooksDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyNodeBooksDlg dialog



CMyNodeBooksDlg::CMyNodeBooksDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYNODEBOOKS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyNodeBooksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_BOOK1, m_edtBook1);
	DDX_Control(pDX, IDC_EDT_BOOK2, m_edtBook2);
	DDX_Control(pDX, IDC_EDT_BOOK3, m_edtBook3);
	DDX_Control(pDX, IDC_EDT_BOOK4, m_edtBook4);
	DDX_Control(pDX, IDC_EDT_CMD, m_edtCmd);
}

BEGIN_MESSAGE_MAP(CMyNodeBooksDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMyNodeBooksDlg message handlers

BOOL CMyNodeBooksDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyNodeBooksDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyNodeBooksDlg::OnPaint()
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
HCURSOR CMyNodeBooksDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyNodeBooksDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

}


BOOL CMyNodeBooksDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		switch (GetFocus()->GetDlgCtrlID())
		{
		case IDC_EDT_CMD:
			GetCommand();
			break;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyNodeBooksDlg::GetCommand()
{
	GetDlgItemText(IDC_EDT_CMD, m_strCmd);
	Analyze();
}

void CMyNodeBooksDlg::Analyze()
{
	m_strCmd.MakeUpper();
	int nBookNum = 0;
	if (m_strCmd.Find(_T("SAVE"))) {
		nBookNum = _ttoi(m_strCmd.Right(1));
		SaveMyFile(nBookNum);//保存文件
	} else if (m_strCmd.Find(_T("OPEN"))) {
		nBookNum = _ttoi(m_strCmd.Right(1));
		OpenMyFile(nBookNum);//打开文件
	} else if (m_strCmd.Find(_T("CLEAR"))) {
		nBookNum = _ttoi(m_strCmd.Right(1));
		ClearMyFile(nBookNum);//清空编辑框
	} else if (m_strCmd.Find(_T("PATH"))) {
		PathMyFile(nBookNum);//文件路径
	}
	else {
		AfxMessageBox(_T("命令正在开发中，敬请期待。。。"));
	}
}

void CMyNodeBooksDlg::SaveMyFile(const int &nBookNum)
{
	int nResult = GetBookContent(nBookNum);
	if (nResult != 0) {
		AfxMessageBox(_T("取出文件内容错误！"));
		return;
	}

	CString strTemp;
	strTemp.Format(_T("保存第%d号文件"), nBookNum);
	AfxMessageBox(strTemp);
}

void CMyNodeBooksDlg::OpenMyFile(const int &nBookNum)
{
	int nResult = GetBookContent(nBookNum);
	if (nResult != 0) {
		AfxMessageBox(_T("取出文件内容错误！"));
		return;
	}

	CString strTemp;
	strTemp.Format(_T("打开第%d号文件内容：%s"), nBookNum, m_strContent);
	AfxMessageBox(strTemp);
}

void CMyNodeBooksDlg::ClearMyFile(const int &nBookNum)
{
	
	int nResult = GetBookContent(nBookNum);
	if (nResult != 0) {
		AfxMessageBox(_T("取出文件内容错误！"));
		return;
	}
	CString strTemp;
	strTemp.Format(_T("清除第%d号文件"), nBookNum);
	AfxMessageBox(strTemp);
}

int CMyNodeBooksDlg::GetBookContent(const int &nBookNum)
{
	switch (nBookNum)
	{
	case 1: GetDlgItemText(IDC_EDT_BOOK1, m_strContent); break;
	case 2: GetDlgItemText(IDC_EDT_BOOK2, m_strContent); break;
	case 3: GetDlgItemText(IDC_EDT_BOOK3, m_strContent); break;
	case 4: GetDlgItemText(IDC_EDT_BOOK4, m_strContent); break;
	default:
		AfxMessageBox(_T("请输入1-4！"));
		return -1;
	}

	return 0;
}