// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PSIMCoreDemo.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#define LOGIN_RESP	(WM_USER + 100)

HWND g_hwndLogin;

// CLoginDlg 对话框
IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_APPNAME, m_edtAppName);
	DDX_Control(pDX, IDC_EDIT_APPTOKEN, m_edtAppToken);
	DDX_Control(pDX, IDC_EDIT_USERID, m_edtUserID);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDIT_DEVICETOKEN, m_edtDeviceToken);
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	g_hwndLogin = m_hWnd;

	m_edtAppName.SetWindowText(_T("xes"));
	m_edtAppToken.SetWindowText(_T("token"));
	m_edtUserID.SetWindowText(_T("3"));
	m_edtUserName.SetWindowText(_T("zhang"));
	m_edtDeviceToken.SetWindowText(_T("windowstoken"));

	return 0;
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedLogin)
END_MESSAGE_MAP()

// CLoginDlg 消息处理程序
void CLoginDlg::OnBnClickedLogin()
{
	CString strAppName, strAppToken, strUserID, strUserName, strDeviceToken;
	m_edtAppName.GetWindowText(strAppName);
	m_edtAppToken.GetWindowText(strAppToken);
	m_edtUserID.GetWindowText(strUserID);
	m_edtUserName.GetWindowText(strUserName);
	m_edtDeviceToken.GetWindowText(strDeviceToken);

	theApp.m_strAppID = CT2CA(strAppName);
	theApp.m_strUserID = CT2CA(strUserID);

#if NO_UNIT_TEST
	AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), CT2CA(strUserName), PS_DeviceType_Windows, CT2CA(strDeviceToken));
#else
	//AfxGetPSIMCall()->MsgLogin(NULL, NULL, NULL, NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin("", NULL, NULL, NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), NULL, NULL, NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), "", NULL, NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), NULL, NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), "", NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Other, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Windows, NULL);	// successed

	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Ios, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Ios, "");
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Ios, CT2CA(strDeviceToken));	// successed
	
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Android, NULL);
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Android, "");
	//AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), NULL, PS_DeviceType_Android, CT2CA(strDeviceToken));	// successed

	AfxGetPSIMCall()->MsgLogin(CT2CA(strAppName), CT2CA(strAppToken), CT2CA(strUserID), CT2CA(strUserName), PS_DeviceType_Windows, CT2CA(strDeviceToken));
#endif
}

LRESULT CLoginDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case LOGIN_RESP:
		{
			PSMsgLoginResp* pRespMsgLogin = (PSMsgLoginResp*)wParam;
			assert(pRespMsgLogin);
			if ( 0 == pRespMsgLogin->iStatus)
			{
				EndDialog(IDOK);
			}
			else
			{
				CString strInfo = CA2CT(pRespMsgLogin->strMessage.GetString());
				MessageBox(strInfo, _T("提示"), MB_OK);
			}
		}
		break;
	default:
		break;
	}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}

void CPSIMDemoCallBack::OnMsgLoginResponse(const PSMsgLoginResp& resp)
{
	printf("CPSIMDemoCallBack::OnLoginResponse: iCode(%d), strInfo(%s) \n", resp.iStatus, resp.strMessage.GetString());

	::SendMessage(g_hwndLogin, LOGIN_RESP, (WPARAM)&resp, NULL);
}