
/************************************************************************/
/*                             …Ë÷√ΩÁ√Ê                                 */
/************************************************************************/

#pragma once
#include "LibData.h"

class Setting :
	public WindowImplBase
{
public:
	Setting(HWND hw);
	~Setting(void);
	LPCTSTR GetWindowClassName()const;
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
	void OnClick(TNotifyUI& msg);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HWND hwnd;
	void Init();
	void SaveFile();
	void ReadFile();
};
