#include "Setting.h"
#include <fstream>
#include "userConfig.h"
Setting::Setting(HWND hw)
{
	hwnd=hw;
}

Setting::~Setting(void)
{
}
LPCTSTR Setting::GetWindowClassName()const
{
	return _T("Setting");
}

CDuiString Setting::GetSkinFile()
{
	return _T("Setting.xml");
}

CDuiString Setting::GetSkinFolder()
{
	return _T("skin");
}

void Setting::OnClick(TNotifyUI& msg)
{
	
	
}

void Setting::Notify(TNotifyUI& msg)
{
	if(msg.sType==DUI_MSGTYPE_CLICK)
	{
		if(msg.pSender->GetName()==BUTTON_BACK)
		{
			Close(IDCANCEL);
		}
		else if(msg.pSender->GetName()==BUTTON_SAVE)
		{
			SaveFile();
			Close(IDOK);
		}
		else if(msg.pSender->GetName()==BUTTON_CANCEL)
		{
			Close(IDCANCEL);
		}
	}
}

LRESULT Setting::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lres=0;
	return __super::HandleMessage(uMsg,wParam,lParam);
}

void Setting::Init()
{
	ReadFile();
}

void Setting::SaveFile()
{
	ofstream outToFile;
	outToFile.open(IPFILE,std::ios::out);
	CEditUI *edit_ip=static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_ip")));
	outToFile<<edit_ip->GetText();
	outToFile.close();
	/********************************************/
	outToFile.open(PORTFILE,std::ios::out);
	CEditUI *edit_port=static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_port")));
	outToFile<<edit_port->GetText();
	outToFile.close();

}

void Setting::ReadFile()
{
	ifstream inToFile1,inToFile2;
	inToFile1.open(IPFILE,std::ios::in);
	CEditUI *edit_ip=static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_ip")));
	char str[30];
	CDuiString cstr;
	inToFile1.getline(str,29);
	cstr=string(str).c_str();
	edit_ip->SetText(cstr);
	inToFile1.close();
	/********************************************/
	inToFile2.open(PORTFILE,std::ios::in);
	CEditUI *edit_port=static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_port")));
	inToFile2.getline(str,29);
	cstr=string(str).c_str();
	edit_port->SetText(cstr);
	inToFile2.close();
}