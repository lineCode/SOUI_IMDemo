// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Adapter_MessageList.h"
#include "Adapter_SearchResult.h"
#include "TreeViewAdapter.h"

#include "utils.h"
#include "extend.ctrls/imre/SImRichEdit.h"
#include "extend.ctrls/imre/RichEditObjEvents.h"
#include "extend.ctrls/imre/ClipboardConverter.h"
#include "extend.ctrls/imre/ImgProvider.h"
#include "extend.events/ExtendEvents.h"

#include "FileHelper.h"
#include "MenuWrapper.h"

#include "CWindowEnumer.h"
#include "SnapshotDlg.h"
#include "EmojiDlg.h"

class CMainDlg : public SHostWnd
	, public TAutoEventMapReg<CMainDlg>//通知中心自动注册
	, public CAdapter_MessageList::IListener
	, public CContactTreeViewAdapter::IListener
	, public CAdapter_SearchResult::IListener
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	void OnLButtonDown(UINT nFlags, CPoint pt);
	//托盘通知消息处理函数
	//LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

public:
	virtual void MessageListItemClick(int nType, const std::string& strID);
	virtual void MessageListItemRClick(int nType, const std::string& strID);

	virtual void ContactItemClick(int nGID, const std::string& strID);
	virtual void ContactItemDBClick(int nGID, const std::string& strID);
	virtual void ContactItemRClick(int nGID, const std::string& strID);

	virtual void SearchResultItemDBClick(int nType, const std::string& strID);
protected:
	void OnBnClickMessage();
	void OnBnClickContact();
	void OnBnClickFavorites();
	void OnBnClickMenu();
	void OnBnClickSearchCancel();

	void OnBnClickSend();

	bool OnSendRichEditAcceptData(SOUI::EventArgs* pEvt);
	bool OnSendRichEditEditorChange(SOUI::EventArgs* pEvt);
	bool OnSendRichEditMenu(SOUI::EventArgs* pEvt);
	bool OnSendRichEditObjEvent(SOUI::EventArgs* pEvt);

	bool OnRecvRichEditAcceptData(SOUI::EventArgs *pEvt);
	bool OnRecvRichEditMenu(SOUI::EventArgs *pEvt);
	bool OnRecvRichEditObjEvent(SOUI::EventArgs *pEvt);
	bool OnRecvRichEditScrollEvent(SOUI::EventArgs *pEvt);

	void FillRClickAvatarMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickImageMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickFileMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickSelRegionMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickBubbleMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickNothingMenu(MenuWrapper& menu);
	void FillRClickAudioMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickVideoMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickLocationMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickLinkMenu(MenuWrapper& menu, RichEditContent* pContent);

	void DragDropFiles(RichFormatConv::DropFiles& files);

	void OnBnClickChatEmotion();
	void OnBnClickChatImage();
	void OnBnClickChatFile();
	void OnBnClickChatCapture();
	void OnBnClickSettingCapture();
	void OnBnClickChatHistory();

	bool OnEditSearchSetFocus(EventArgs* pEvt);
	bool OnEditSearchKillFocus(EventArgs* pEvt);
	bool OnEditSearchChanged(EventArgs *e);

	bool OnEventSnapshotFinish(EventArgs* e);
private:
	void AddBackGeneralMessage(SImRichEdit* pRecvRichEdit, const std::vector<SStringW>& vecContents);
	void AddBackFileMessage(SImRichEdit* pRecvRichEdit, const SStringW& sstrFilePath);
	void AddBackSysMessage(SImRichEdit* pRecvRichEdit, const SStringW& sstrContent);
// 	void AddFrontGeneralMessage(SImRichEdit* pRecvRichEdit, const std::vector<SStringW>& vecContents);
// 	void AddFrontFileMessage(SImRichEdit* pRecvRichEdit, const SStringW& sstrFilePath);
// 	void AddFrontSysMessage(SImRichEdit* pRecvRichEdit, const SStringW& sstrContent);

	void AddFetchMoreBlock(SImRichEdit* pRecvRichEdit);
protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)

		EVENT_NAME_COMMAND(L"btn_message", OnBnClickMessage)
		EVENT_NAME_COMMAND(L"btn_contact", OnBnClickContact)
		EVENT_NAME_COMMAND(L"btn_favorites", OnBnClickFavorites)
		EVENT_NAME_COMMAND(L"btn_menu", OnBnClickMenu)
		EVENT_NAME_COMMAND(L"search_cancel", OnBnClickSearchCancel)

		EVENT_NAME_COMMAND(L"btn_emotion", OnBnClickChatEmotion)
		EVENT_NAME_COMMAND(L"btn_image", OnBnClickChatImage)
		EVENT_NAME_COMMAND(L"btn_file", OnBnClickChatFile)
		EVENT_NAME_COMMAND(L"btn_snapshot", OnBnClickChatCapture)
		EVENT_NAME_COMMAND(L"btn_snapshot_arrow", OnBnClickSettingCapture)
		EVENT_NAME_COMMAND(L"btn_history", OnBnClickChatHistory)

		EVENT_NAME_COMMAND(L"btn_send", OnBnClickSend)

		EVENT_NAME_HANDLER(L"search_edit", EventSetFocus::EventID, OnEditSearchSetFocus)
		EVENT_NAME_HANDLER(L"search_edit", EventKillFocus::EventID, OnEditSearchKillFocus)
		EVENT_ID_HANDLER(R.id.search_edit, EventRENotify::EventID, OnEditSearchChanged)

		EVENT_HANDLER(EVT_SNAPSHOTFINISH, OnEventSnapshotFinish)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
	//托盘消息处理
		//MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;	

	CAdapter_MessageList* m_pAdapterLasttalk;
	CContactTreeViewAdapter* m_pTreeViewAdapter;
	CAdapter_SearchResult*	m_pAdapterSearchResult;

	CEmojiDlg*				m_pEmojiDlg;
	bool					m_bEmotionShow;

	LASTTALK_CURSEL	m_LasttalkCurSel;
	bool			m_bSnapshotHideWindow;
	int				m_nOldCurSel;

	bool			m_bResultEmpty;
};
