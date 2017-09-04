#include "stdafx.h"
#include "SkinManager.h"

namespace DuiLib {
	CSkinManager* CSkinManager::m_pSkinManager = NULL;

	CSkinManager* CSkinManager::GetSkinManager()
	{
		if (m_pSkinManager == NULL)
		{
			m_pSkinManager = new CSkinManager();
		}

		return m_pSkinManager;
	}

	void CSkinManager::AddReceiver(ReceiverImpl<BOOL, SkinChangedParam>* receiver)
	{
		m_SkinChangeObserver.AddReceiver(receiver);
	}

	void CSkinManager::RemoveReceiver(ReceiverImpl<BOOL, SkinChangedParam>* receiver)
	{
		m_SkinChangeObserver.RemoveReceiver(receiver);
	}

	void CSkinManager::Broadcast(SkinChangedParam param)
	{
		m_SkinChangeObserver.Broadcast(param);
	}

	void CSkinManager::Notify(SkinChangedParam param)
	{
		m_SkinChangeObserver.Notify(param);
	}

	CSkinManager::CSkinManager()
	{
	}

}