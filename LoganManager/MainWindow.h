#pragma once
#include "LibData.h"
/************************************************************************/
/*                               ��ҳ��                                 */
/************************************************************************/
class MainWindow :
	public WindowImplBase
{
public:
	MainWindow(void);
	~MainWindow(void);
	LPCTSTR GetWindowClassName()const;
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
	void OnClick(TNotifyUI& msg);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
