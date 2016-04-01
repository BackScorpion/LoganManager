#include "MainWindow.h"
#include <Windows.h>
#include <WinUser.h>
#include "LibData.h"
#include "resource.h"
MainWindow::MainWindow(void)
{
	
}

MainWindow::~MainWindow(void)
{
}
LPCTSTR MainWindow::GetWindowClassName()const
{
	return _T("MainWindow");
}
CDuiString MainWindow::GetSkinFile()
{
	//return _T("MainWindow.xml");
	return _T("3.xml");
}
CDuiString MainWindow::GetSkinFolder()
{
	return _T("skin");
}
void MainWindow::Notify(TNotifyUI& msg)
{
	if(msg.sType==_T("click"))
	{
		if(msg.pSender->GetName()==_T("btn_close"))
		{
			Close(IDOK);
			
		}
		else if(msg.pSender->GetName()==_T("btn_min"))
		{
			SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
		}
		
	}
	else
	{
		__super::Notify(msg);
	}
}
void MainWindow::OnClick(TNotifyUI& msg)
{
	
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg,wParam,lParam);
}

