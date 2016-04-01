

/************************************************************************/
/*                              ��¼ϵͳҳ��                             /
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
	bool rem;//��ס����
	bool auto_login;//�Զ���¼
	string ip_address;
	string port;
	map<string,string>userList;
	void setIP(string ip); 
	void setPort(string po);
	//�ж��Ƿ��¼�ɹ�
	inline bool LoginSuccessful();
	//��¼��־
	void updateLog( bool satus);
private:
	void loadConfig();
	void Init();
	//�ϴ��û���
	void uploadUser(string username,string password);
	//�ж��û������Ƿ�����û�
	void downloadUserName();
	bool existInList(string username);
	//��¼�¼�
	void loginEvent();
	//�����¼�
	void settingEvent();
	
};
