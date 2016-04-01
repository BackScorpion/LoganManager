#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "LogIn.h"
#include "Setting.h"
#include "resource.h"
#include "Request.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "userConfig.h"
LogIn::LogIn(void)
{
	rem=false;
	auto_login=false;
	Code=0;
	PostMsg=_T("");
}

LogIn::~LogIn(void)
{
}

LPCTSTR LogIn::GetWindowClassName()const
{
	return _T("LogIn");
}

CDuiString LogIn::GetSkinFile()
{
	return _T("LogIn.xml");
}

CDuiString LogIn::GetSkinFolder()
{
	return _T("skin");
}

LRESULT LogIn::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg,wParam,lParam);
}

void LogIn::OnClick(TNotifyUI& msg)
{
}

void LogIn::Notify(TNotifyUI& msg)
{
	if(msg.sType==DUI_MSGTYPE_CLICK)
	{
		if(msg.pSender->GetName()==BUTTON_LOGIN)//登录按钮
		{
			//loginEvent();
			Close(IDOK);
		}
		if(msg.pSender->GetName()==BUTTON_CLOSE)//关闭
		{
			Close(IDCANCEL);
		}
		else if(msg.pSender->GetName()==BUTTON_SETTING)//设置
		{
			settingEvent();
		}
		else if(msg.pSender->GetName()==BUTTON_EXIT)
		{
			Close(IDCANCEL);
		}
		else if(msg.pSender->GetName()==CHECK_REMBER)//记住密码
		{
				rem=!rem;
		}
		else if(msg.pSender->GetName()==CHECK_AUTO_LOGIN)//自动登录
		{
				auto_login=!auto_login;
		}
	}
	if(msg.sType==DUI_MSGTYPE_RETURN)//回车
	{
		Close(IDOK);
		//loginEvent();
	}
	if(msg.sType==DUI_MSGTYPE_TEXTCHANGED)
	{
		if(msg.pSender->GetName()==_T("user_name"))
		{
			
		}
	}
	
}

void LogIn::setIP(string ip)
{
	this->ip_address=ip;
}

void LogIn::setPort(string po)
{
	this->port=po;
}

bool LogIn::LoginSuccessful()
{
	if(Code==1) //成功
	{
		updateLog(true);
		return true;
	}
	else
	{
		updateLog(false);
		return false;
	}
	
}

void LogIn::updateLog( bool satus)
{
	ofstream out;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	CDuiString str;
	if(satus)
	{
		str.Format(_T("%d-%d-%d %d:%d:%d %s login LoganManager system succeed"),systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,
			systime.wSecond,user);
	}
	else
	{
		str.Format(_T("%d-%d-%d %d:%d:%d %s login LoganManager system faile"),systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,
			systime.wSecond,user);
	}
	
	out.open(_T("E:\\loger.txt"),ios::out|ios::app);
	out<<str<<endl;
	out.close();
}

// 加载配置

void LogIn::loadConfig()
{	//加载IP和端口
	ifstream in,nn;
	in.open(IPFILE);
	char str[18]="155.255.255.255";
	in.getline(str,17);
	setIP((string(str)));
	in.close();
	nn.open(PORTFILE);
	nn.getline(str,17);
	setPort(string(str));
	nn.close();	
	downloadUserName();



}

//初始化配置
void LogIn::Init()
{
	loadConfig();
}

bool LogIn::existInList(string username)
{
	map<string,string>::iterator iterUser;
	iterUser=userList.find(username);
	if(iterUser==userList.end())
		return false;
	return true;
}

void LogIn::uploadUser(string username,string password)
{	
	//如果登录成功 && 密码表中不存在此用户 && 记住密码 则开始上传
	if(Code==YES && !existInList(username) && rem) 	
	{
		ofstream upload;
		upload.open(USERNAMETABLE,std::ios::out|std::ios::app);
		upload<<username<<"#"<<password<<endl;
		upload.close();
		
	}
	else
	{
		return;
	}

}

void LogIn::downloadUserName()
{
	ifstream inUser;
	inUser.open(USERNAMETABLE);
	char buffer[MIDMSGSIZE];
	while(!inUser.eof())
	{
		inUser.getline(buffer,MIDMSGSIZE);
		string userKey,pwdValue,str;
		str=string(buffer);
		int n=str.find('#');
		userKey=str.substr(0,n);
		pwdValue=str.substr(n+1,str.length());
		userList.insert(map<string,string>::value_type(userKey,pwdValue));

	}
	inUser.close();
}

void LogIn::loginEvent()
{
	//加载配置
	loadConfig();
	CEditUI * edit_user=static_cast<CEditUI*>
		(m_PaintManager.FindControl(_T("user_name")));
	CEditUI * edit_pwd=static_cast<CEditUI*>
		(m_PaintManager.FindControl(_T("pass_code")));
	user=edit_user->GetText();
	pwd=edit_pwd->GetText();

	//输入框判断
	//如果是中文的情况再行判断
	if(user==_T("") ||pwd==_T(""))
	{
		MessageBox(NULL,_T("请输入用户名或密码"),
			_T("警告"),NULL);
		return;
	}
	string s;
	s="http://"+ip_address+":"+port+"/demo.cgi?type=login&";
	LoginUrl=s.c_str();
	CDuiString cduiurl=LoginUrl+"&userName="+user+
		"&password="+pwd;
	string url=(string)cduiurl;
	Request request;
	char* xmlres=request.GetRespond(url);
	TiXmlDocument xml;
	xml.Parse(xmlres);
	TiXmlNode *root=xml.RootElement();
	TiXmlNode *typeNode=root->FirstChild();
	TiXmlNode *codeNode=typeNode->NextSiblingElement();
	TiXmlNode *msgNode=codeNode->NextSiblingElement();
	Code=(UINT)atoi(codeNode->FirstChild()->Value());
	CDuiString ms(msgNode->FirstChild()->Value());
	if(LoginSuccessful())
	{
		uploadUser((string)user,(string)pwd);//上传密码
		Close(IDOK);
	}
	else
	{
		MessageBox(NULL,ms,
			_T("警告"),NULL);
	}
}

//设置事件
void LogIn::settingEvent()
{
	HWND hWnd=::FindWindow(NULL,_T("Setting"));
	if(hWnd)
	{
		SetWindowPos(hWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		return;
	}
	RECT rc;
	GetWindowRect(m_hWnd,&rc);
	Setting *se = new Setting(m_hWnd);
	se->Create(m_hWnd,_T("Setting"),
		UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE,rc,0);
	se->CenterWindow();
	se->ShowModal();

}