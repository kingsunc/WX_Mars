
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
#define CREATEGROUP_RESP	(WM_USER+104)
#define ADDGROUPUSER_RESP	(WM_USER+105)

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
	DDX_Control(pDX, IDC_EDIT_FROM_USERID, m_edtFromUser);
	DDX_Control(pDX, IDC_EDIT_TO_USERID, m_edtToUser);
	DDX_Control(pDX, IDC_EDIT_SINGLE_CONTENT, m_edtContent);
	DDX_Control(pDX, IDC_RICHEDIT_INFO, m_edtInfo);
	DDX_Control(pDX, IDC_EDIT_GROUP_ID, m_edtGroup);
	DDX_Control(pDX, IDC_EDIT_GROUP_MEMBER_ID, m_edtGroupMember);
	DDX_Control(pDX, IDC_EDIT_FROM_GUSERID, m_edtFromGUser);
	DDX_Control(pDX, IDC_EDIT_TO_GROUPID, m_edtToGroup);
	DDX_Control(pDX, IDC_EDIT_GROUP_CONTENT, m_edtGroupContent);
}

BEGIN_MESSAGE_MAP(CPSIMCoreDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPSIMCoreDemoDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CREATEGROUP, &CPSIMCoreDemoDlg::OnBnClickedButtonCreategroup)
	ON_BN_CLICKED(IDC_BUTTON_DELETEGROUP, &CPSIMCoreDemoDlg::OnBnClickedButtonDeletegroup)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_MEMBER_ADD, &CPSIMCoreDemoDlg::OnBnClickedButtonGroupMemberAdd)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_MEMBER_REMOVE, &CPSIMCoreDemoDlg::OnBnClickedButtonGroupMemberRemove)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_SEND, &CPSIMCoreDemoDlg::OnBnClickedButtonGroupSend)
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

	m_edtFromUser.SetWindowText(CA2CT(theApp.m_strUserID));
	m_edtFromGUser.SetWindowText(CA2CT(theApp.m_strUserID));
	/*
	const int iDescCount = 3;
	PSOffMsgDesc* pOffMsgDesc = new PSOffMsgDesc[iDescCount];
	memset(pOffMsgDesc, 0, iDescCount * sizeof(PSOffMsgDesc));
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

static int sg_iCount = 0;
LRESULT CPSIMCoreDemoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case SENDMESSGAE_RESP:
		{
			PSMsgResp* pMsgResp = (PSMsgResp*)wParam;
			assert(pMsgResp);

			CString strInfo;
			strInfo.Format(_T(" seq(%d) has resp: Code(%d), count(%d), Info(%s), \n"), pMsgResp->iSeqId, pMsgResp->iCode, ++sg_iCount, CA2CT(pMsgResp->strInfo));
			AppendInfo(strInfo);
		}
		break;
	case RECVMESSGAE_RESP:
		{
			PSMessageItem* pMsgItem = (PSMessageItem*)wParam;
			assert(pMsgItem);

			CStringA strInfoA;
			strInfoA.Format("from: %s -> to: %s msgid: %d \n content: %s \n", pMsgItem->strFrom, pMsgItem->strTo, (int)(pMsgItem->iMsgId), pMsgItem->psBuff.pBuff);
			CString strInfo = CA2CT(strInfoA);
			AppendInfo(strInfo);
		}
		break;
	case CREATEGROUP_RESP:
		{
			PSCreateGroupResp* respCreateGroup = (PSCreateGroupResp*)wParam;
			assert(respCreateGroup);

			CStringA strInfoA;
			strInfoA.Format("creategroup :  status(%d) message(%s) \n", respCreateGroup->iStatus, respCreateGroup->strMessage);
			CString strInfo = CA2CT(strInfoA);
			AppendInfo(strInfo);
		}
		break;
	case ADDGROUPUSER_RESP :
		{
			PSAddGroupUsersResp* respAddGroupUsers = (PSAddGroupUsersResp*)wParam;
			assert(respAddGroupUsers);

			CStringA strInfoA;
			strInfoA.Format("addgroupuser :  status(%d) message(%s) \n", respAddGroupUsers->iStatus, respAddGroupUsers->strMessage);
			CString strInfo = CA2CT(strInfoA);
			AppendInfo(strInfo);
		}
		break;
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
	m_edtFromUser.GetWindowText(strFrom);
	m_edtToUser.GetWindowText(strTo);
	m_edtContent.GetWindowText(strContent);

	int iSeqID = 0;
	for (int i = 0; i < 1000; i++)
	{
		bool iRes = AfxGetPSIMCall()->SendTextMessage(iSeqID, PS_SendMode_P2P, CT2CA(strFrom), CT2CA(strTo), CT2CA(strContent), strContent.GetLength(), "");
		if (iRes && (iSeqID > 0))
		{
			CString strInfo;
			strInfo.Format(_T("from: %s -> to: %s seqid: %d \n content: %s \n"), strFrom, strTo, iSeqID, strContent);
			AppendInfo(strInfo);
		}
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

	m_edtInfo.LineScroll(m_edtInfo.GetLineCount());
}


void CPSIMCoreDemoDlg::OnBnClickedButtonCreategroup()
{
	CString strGroupID;
	m_edtGroup.GetWindowText(strGroupID);
	CStringA strGroupIDA;
	strGroupIDA = CT2CA(strGroupID);
	if (strGroupID.IsEmpty())
	{
		MessageBox(_T("groupid 不能为空！"));
		return;
	}

	PSGroupInfo groupInfo;
	groupInfo.strGroupID = (char*)strGroupIDA.GetString();
	AfxGetPSIMCall()->CreateGroup(groupInfo);
}

void CPSIMCoreDemoDlg::OnBnClickedButtonDeletegroup()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPSIMCoreDemoDlg::OnBnClickedButtonGroupMemberAdd()
{
	CString strGroupID;
	m_edtGroup.GetWindowText(strGroupID);
	CStringA strGroupIDA;
	strGroupIDA = CT2CA(strGroupID);
	if (strGroupID.IsEmpty())
	{
		MessageBox(_T("groupid 不能为空！"));
		return;
	}

	CString strMemberID;
	m_edtGroupMember.GetWindowText(strMemberID);
	CStringA strMemberIDA;
	strMemberIDA = CT2CA(strMemberID);
	if (strMemberID.IsEmpty())
	{
		MessageBox(_T("Group Member 不能为空！"));
		return;
	}

	const int iCount = 1;
	PSUserInfo* pUser = new PSUserInfo[iCount];
	pUser[0].strUserID = (char*)strMemberID.GetString();
	AfxGetPSIMCall()->AddGroupUsers(strGroupIDA.GetString(), pUser, iCount);
	delete []pUser;
	pUser = NULL;
}


void CPSIMCoreDemoDlg::OnBnClickedButtonGroupMemberRemove()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPSIMCoreDemoDlg::OnBnClickedButtonGroupSend()
{
	CString strFromGUser, strToGroup, strGroupContent;
	m_edtFromGUser.GetWindowText(strFromGUser);
	m_edtToGroup.GetWindowText(strToGroup);
	m_edtGroupContent.GetWindowText(strGroupContent);

	int iSeqID = 0;
	//for (int i = 0; i < 1000; i++)
	{
		bool iRes = AfxGetPSIMCall()->SendTextMessage(iSeqID, PS_SendMode_Group, CT2CA(strFromGUser), CT2CA(strToGroup), CT2CA(strGroupContent), strGroupContent.GetLength(), "");
		if (iRes && (iSeqID > 0))
		{
			CString strInfo;
			strInfo.Format(_T("from: %s -> to: %s seqid: %d \n content: %s \n"), strFromGUser, strToGroup, iSeqID, strGroupContent);
			AppendInfo(strInfo);
		}
	}
}

// 注销-回调处理;
void CPSIMDemoCallBack::OnMsgLogoutResponse(const PSMsgLoginResp& respMsgLogout)
{
	//printf("CPSIMDemoCallBack::OnSendMsgResponse: iSeqID:(%d), iCode(%d), strInfo(%s) \n", msgResp.iSeqId, msgResp.iCode, msgResp.strInfo);

	//SendMessage(g_hwndMain, SENDMESSGAE_RESP, (WPARAM)&msgResp, NULL);
}

// 被迫踢出-回调处理;
void CPSIMDemoCallBack::OnKickOutResponse(const PSKickOutResp& respKickOut)
{
	//printf("CPSIMDemoCallBack::OnSendMsgResponse: iSeqID:(%d), iCode(%d), strInfo(%s) \n", msgResp.iSeqId, msgResp.iCode, msgResp.strInfo);

	//SendMessage(g_hwndMain, SENDMESSGAE_RESP, (WPARAM)&msgResp, NULL);
}

// callback
void CPSIMDemoCallBack::OnSendMsgResponse(const PSMsgResp& msgResp)
{
	printf("CPSIMDemoCallBack::OnSendMsgResponse: iSeqID:(%d), iCode(%d), strInfo(%s) \n", msgResp.iSeqId, msgResp.iCode, msgResp.strInfo);

	SendMessage(g_hwndMain, SENDMESSGAE_RESP, (WPARAM)&msgResp, NULL);
}

void CPSIMDemoCallBack::OnRecvMessage(const PSMessageItem & msgItem)
{
	printf("CPSIMDemoCallBack::OnRecvMessage\n");

	SendMessage(g_hwndMain, RECVMESSGAE_RESP, (WPARAM)&msgItem, NULL);
}

void CPSIMDemoCallBack::OnCreateGroupResponse(const PSCreateGroupResp & respCreateGroup)
{
	printf("CPSIMDemoCallBack::OnCreateGroupResponse\n");

	SendMessage(g_hwndMain, CREATEGROUP_RESP, (WPARAM)&respCreateGroup, NULL);
}

void CPSIMDemoCallBack::OnAddGroupUsersResponse(const PSAddGroupUsersResp& respAddGroupUsers)
{
	printf("CPSIMDemoCallBack::OnAddGroupUserResponse\n");

	SendMessage(g_hwndMain, ADDGROUPUSER_RESP, (WPARAM)&respAddGroupUsers, NULL);
}