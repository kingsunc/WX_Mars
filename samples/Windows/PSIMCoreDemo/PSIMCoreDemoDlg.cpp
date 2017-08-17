
// PSIMCoreDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PSIMCoreDemo.h"
#include "PSIMCoreDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hwndMain;
#define SENDMESSGAE_RESP	(WM_USER+102)
#define RECVMESSGAE_RESP	(WM_USER+103)

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPSIMCoreDemoDlg 对话框
CPSIMCoreDemoDlg::CPSIMCoreDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PSIMCOREDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPSIMCoreDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_APPNAME, m_edtFrom);
	DDX_Control(pDX, IDC_EDIT_APPNAME2, m_edtTo);
	DDX_Control(pDX, IDC_EDIT_APPNAME3, m_edtContent);
	DDX_Control(pDX, IDC_RICHEDIT21, m_edtInfo);
}

BEGIN_MESSAGE_MAP(CPSIMCoreDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPSIMCoreDemoDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CPSIMCoreDemoDlg 消息处理程序
BOOL CPSIMCoreDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	g_hwndMain = m_hWnd;

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_edtFrom.SetWindowText(CA2CT(theApp.m_strUserID));

	/*
	const int iDescCount = 3;
	PS_OffMsgDesc_t* pOffMsgDesc = new PS_OffMsgDesc_t[iDescCount];
	memset(pOffMsgDesc, 0, iDescCount * sizeof(PS_OffMsgDesc_t));
	{
		pOffMsgDesc[0].strFrom = "1101";
		pOffMsgDesc[0].strTo = "1102";
		pOffMsgDesc[0].iSendMode = PS_SendMode_P2P;
		pOffMsgDesc[0].iStartMsgID = 10000;
		pOffMsgDesc[0].iMsgCount = 100;

		pOffMsgDesc[1].strFrom = "1101";
		pOffMsgDesc[1].strTo = "1103";
		pOffMsgDesc[1].iSendMode = PS_SendMode_P2P;
		pOffMsgDesc[1].iStartMsgID = 10000;
		pOffMsgDesc[1].iMsgCount = 100;

		pOffMsgDesc[2].strFrom = "1101";
		pOffMsgDesc[2].strTo = "2000";
		pOffMsgDesc[3].iSendMode = PS_SendMode_Group;
		pOffMsgDesc[2].iStartMsgID = 10000;
		pOffMsgDesc[2].iMsgCount = 100;
	}
	AfxGetPSIMCall()->GetOfflineMsgs(pOffMsgDesc, iDescCount);
	delete[]pOffMsgDesc;
*/
	return TRUE;
}

LRESULT CPSIMCoreDemoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case SENDMESSGAE_RESP:
		{
			int* pCode = (int*)wParam;
			char* pInfo = (char*)lParam;
			if (0 == *pCode)
			{
			
			}
			else
			{
				CString strInfo = CA2CT(pInfo);
				MessageBox(strInfo, _T("提示"), MB_OK);
			}
		}
		break;
	case RECVMESSGAE_RESP:
		{
			MessageItem* pMsgItem = (MessageItem*)wParam;
			assert(pMsgItem);

			CStringA strInfoA;
			strInfoA.Format("from: %s -> to: %s msgid: %d \n content: %s \n", pMsgItem->strFrom, pMsgItem->strTo, (int)(pMsgItem->iMsgId), pMsgItem->psBuff.pBuff);
			CString strInfo = CA2CT(strInfoA);
			AppendInfo(strInfo);
		}
	default:
		break;
	}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}

void CPSIMCoreDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPSIMCoreDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPSIMCoreDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPSIMCoreDemoDlg::OnBnClickedButtonSend()
{
	CString strFrom, strTo, strContent;
	m_edtFrom.GetWindowText(strFrom);
	m_edtTo.GetWindowText(strTo);
	m_edtContent.GetWindowText(strContent);

	int iSeqID = 0;
	bool iRes = AfxGetPSIMCall()->SendTextMessage(iSeqID, PS_SendMode_P2P, CT2CA(strFrom), CT2CA(strTo), CT2CA(strContent), strContent.GetLength(), "");
	if (iRes && (iSeqID > 0))
	{
		CString strInfo;
		strInfo.Format(_T("from: %s -> to: %s seqid: %d \n content: %s \n"), strFrom, strTo, iSeqID, strContent);
		AppendInfo(strInfo);
	}
}

void CPSIMCoreDemoDlg::AppendInfo(CString strInfo)
{
	// 获得文字的长度;
	int nTextLength = m_edtInfo.GetWindowTextLength();
	// 将光标放在文本最末;
	m_edtInfo.SetSel(nTextLength, nTextLength);
	// 写入文本;
	m_edtInfo.ReplaceSel(strInfo);
}


void CPSIMDemoCallBack::OnSendMsgResponse(const int & iCode, const char * strInfo)
{
	printf("CPSIMDemoCallBack::OnSendMsgResponse: iCode(%d), strInfo(%s) \n", iCode, strInfo);

	SendMessage(g_hwndMain, SENDMESSGAE_RESP, (WPARAM)&iCode, (LPARAM)strInfo);
}

void CPSIMDemoCallBack::OnRecvMessage(const MessageItem & msgItem)
{
	printf("CPSIMDemoCallBack::OnRecvMessage");

	SendMessage(g_hwndMain, RECVMESSGAE_RESP, (WPARAM)&msgItem, NULL);
	return;
}