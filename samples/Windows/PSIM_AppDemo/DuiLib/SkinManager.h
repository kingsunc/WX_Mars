#pragma once

namespace DuiLib {

	class UILIB_API SkinChangedParam
	{
	public:
		SkinChangedParam()
		{
		}
		SkinChangedParam(bool bColor, int iBkColor, CDuiString strBkImage)
		{
			m_bColor = bColor;
			m_iBkColor = iBkColor;
			m_strBkImage = strBkImage;
		}

		bool			m_bColor;
		int				m_iBkColor;
		CDuiString		m_strBkImage;
	};

	typedef class ObserverImpl<BOOL, SkinChangedParam> SkinChangedObserver;
	typedef class ReceiverImpl<BOOL, SkinChangedParam> SkinChangedReceiver;

	class UILIB_API CSkinManager
	{
	public:
		static CSkinManager* GetSkinManager();

	public:
		void AddReceiver(ReceiverImpl<BOOL, SkinChangedParam>* receiver);
		void RemoveReceiver(ReceiverImpl<BOOL, SkinChangedParam>* receiver);

		void Broadcast(SkinChangedParam param);

		void Notify(SkinChangedParam param);

	private:
		CSkinManager();

	private:
		SkinChangedObserver m_SkinChangeObserver;
		static CSkinManager* m_pSkinManager;
	};
}