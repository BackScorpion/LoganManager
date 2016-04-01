

/************************************************************************/
/*                              登录系统页面                             /
/************************************************************************/
#pragma once
#include "LibData.h"
#include <fstream>
#include <vector>
#include "userConfig.h"

class LogIn :
	public WindowImplBase
{
public:
	CDuiString LoginUrl;
	LogIn(void);
	~LogIn(void);
	LPCTSTR GetWindowClassName()const;
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
	void OnClick(TNotifyUI& msg);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	UINT Code;
	CDuiString PostMsg;
	CDuiString user;
	CDuiString pwd;
	bool rem;//记住密码
	bool auto_login;//自动登录
	string ip_address;
	string port;
	map<string,string>userList;
	void setIP(string ip); 
	void setPort(string po);
	//判断是否登录成功
	inline bool LoginSuccessful();
	//登录日志
	void updateLog( bool satus);
private:
	void loadConfig();
	void Init();
	//上传用户名
	void uploadUser(string username,string password);
	//判断用户名中是否存在用户
	void downloadUserName();
	bool existInList(string username);
	//登录事件
	void loginEvent();
	//设置事件
	void settingEvent();
	
};
