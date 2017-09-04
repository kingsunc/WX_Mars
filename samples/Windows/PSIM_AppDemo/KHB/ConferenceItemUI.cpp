//#include "stdafx.h"
//#include "ConferenceItemUI.h"
//
//IMPLEMENT_DUICONTROL(CConferenceItemUI)
//REGIST_DUICONTROL(CConferenceItemUI)
//
//CConferenceItemUI::CConferenceItemUI()
//{
//	//SetSepWidth()
//}
//
//CConferenceItemUI::~CConferenceItemUI()
//{
//}
//
//void CConferenceItemUI::DoEvent(TEventUI& tEvent)
//{
//	if (!IsEnabled())
//	{
//		// 若禁用，不响应事件;
//		return;
//	}
//
//	switch (tEvent.Type)
//	{
//	case UIEVENT_MOUSEENTER:
//		{
//			SetBkColor(0x33FFFFFF);
//			//return;
//		}
//		break;
//	case UIEVENT_MOUSELEAVE:
//		{
//			SetBkColor(0x11FFFFFF);
//			//return;
//		}
//		break;
//	case UIEVENT_BUTTONDOWN:
//	case UIEVENT_RBUTTONDOWN:
//		{
//			SetBkColor(0x55FFFFFF);
//			return;
//		}
//		break;
//	case UIEVENT_BUTTONUP:
//	case UIEVENT_RBUTTONUP:
//		{
//			m_pManager->SendNotify(this, CONFERENCEITEM_BUTTONUP);
//			return;
//		}
//		break;
//	}
//
//	CVerticalLayoutUI::DoEvent(tEvent);
//}
//
//void CConferenceItemUI::SetConferenceItem(const CConfItem& CommentNode)
//{
//	m_CommentItem = CommentNode;
//
//	// 会议主题;
//	{
//		CTextUI* pTitleUI = dynamic_cast<CTextUI*>(GetItemAt(0));
//		assert(pTitleUI);
//		CDuiString strTitle;
//		strTitle.Format(_T("会议主题: %s"), m_CommentItem.m_strSubject.c_str());
//		pTitleUI->SetText(strTitle);
//	}
//
//	// 会议创建时间;
//	{
//		time_t tick = (time_t)m_CommentItem.m_iStartTime;
//		struct tm tm;
//		char strTemp[100];
//
//		tm = *localtime(&tick);
//		strftime(strTemp, sizeof(strTemp), "%Y-%m-%d %H:%M:%S", &tm);
//
//		CTextUI* pTimeUI = dynamic_cast<CTextUI*>(GetItemAt(1));
//		assert(pTimeUI);
//
//		CDuiString strTime;
//		strTime.Format(_T("创建时间: %s"), _A2T(strTemp).c_str());
//		pTimeUI->SetText(strTime);
//	}
//
//	// 会议ID;
//	{
//		CTextUI* pIDUI = dynamic_cast<CTextUI*>(GetItemAt(2));
//		assert(pIDUI);
//		CDuiString strID;
//		strID.Format(_T("会议ID: %s"), m_CommentItem.m_strID.c_str());
//		pIDUI->SetText(strID);
//	}
//
//	{
//		CHorizontalLayoutUI* pBottom = dynamic_cast<CHorizontalLayoutUI*>(GetItemAt(4));
//		// 开会
//		CButtonUI* pStartUI = dynamic_cast<CButtonUI*>(pBottom->GetItemAt(0));
//		assert(pStartUI);
//		CDuiString strStartName;
//		strStartName.Format(_T("btn_conferenceitem_start_%s"), m_CommentItem.m_strID.c_str());
//		pStartUI->SetName(strStartName);
//
//		// 编辑
//		CButtonUI* pEditUI = dynamic_cast<CButtonUI*>(pBottom->GetItemAt(2));
//		assert(pEditUI);
//		CDuiString strEditName;
//		strEditName.Format(_T("btn_conferenceitem_edit_%s"), m_CommentItem.m_strID.c_str());
//		pEditUI->SetName(strEditName);
//
//		/*CDuiString strID;
//		strID.Format(_T("会议ID: %s"), m_CommentItem.m_strID.c_str());
//		pIDUI->SetText(strID);
//
//		<HorizontalLayout height = "24" >
//			<Button width = "65" style = "loginbtn_style" keyboard = "false" text = "开会" font = "1" textcolor = "#FFFFFFFF" disabledtextcolor = "#FFFFFFFF" / >
//			<HorizontalLayout width = "10" / >
//			<Button width = "65" style = "loginbtn_style" keyboard = "false" text = "编辑" font = "1" textcolor = "#FFFFFFFF" disabledtextcolor = "#FFFFFFFF" / >
//			< / HorizontalLayout >*/
//	}
//
//}
//
//CConfItem& CConferenceItemUI::GetConferenceItem()
//{
//	return m_CommentItem;
//}
//
//LPCTSTR CConferenceItemUI::GetClass() const
//{
//	return _T("ConferenceItemUI");
//}