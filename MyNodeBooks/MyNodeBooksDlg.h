
// MyNodeBooksDlg.h : header file
//

#pragma once


// CMyNodeBooksDlg dialog
class CMyNodeBooksDlg : public CDialogEx
{
// Construction
public:
	CMyNodeBooksDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYNODEBOOKS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CEdit m_edtBook1;
	CEdit m_edtBook2;
	CEdit m_edtBook3;
	CEdit m_edtBook4;
	CEdit m_edtCmd;
	CString m_strCmd;		//命令
	CString m_strContent;	//编辑框的值
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void GetCommand();
	void Analyze();
	void SaveMyFile(const int &nBookNum);//nNum:编号 
	void OpenMyFile(const int &nBookNum);
	void ClearMyFile(const int &nBookNum);
	int GetBookContent(const int &nBookNum);//取文件框内容
};
