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
		if(msg.pSender->GetName()==BUTTON_LOGIN)//��¼��ť
		{
			//loginEvent();
			Close(IDOK);
		}
		if(msg.pSender->GetName()==BUTTON_CLOSE)//�ر�
		{
			Close(IDCANCEL);
		}
		else if(msg.pSender->GetName()==BUTTON_SETTING)//����
		{
			settingEvent();
		}
		else if(msg.pSender->GetName()==BUTTON_EXIT)
		{
			Close(IDCANCEL);
		}
		else if(msg.pSender->GetName()==CHECK_REMBER)//��ס����
		{
				rem=!rem;
		}
		else if(msg.pSender->GetName()==CHECK_AUTO_LOGIN)//�Զ���¼
		{
				auto_login=!auto_login;
		}
	}
	if(msg.sType==DUI_MSGTYPE_RETURN)//�س�
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
	if(Code==1) //�ɹ�
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

// ��������

void LogIn::loadConfig()
{	//����IP�Ͷ˿�
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

//��ʼ������
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
	//�����¼�ɹ� && ������в����ڴ��û� && ��ס���� ��ʼ�ϴ�
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
	//��������
	loadConfig();
	CEditUI * edit_user=static_cast<CEditUI*>
		(m_PaintManager.FindControl(_T("user_name")));
	CEditUI * edit_pwd=static_cast<CEditUI*>
		(m_PaintManager.FindControl(_T("pass_code")));
	user=edit_user->GetText();
	pwd=edit_pwd->GetText();

	//������ж�
	//��������ĵ���������ж�
	if(user==_T("") ||pwd==_T(""))
	{
		MessageBox(NULL,_T("�������û���������"),
			_T("����"),NULL);
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
		uploadUser((string)user,(string)pwd);//�ϴ�����
		Close(IDOK);
	}
	else
	{
		MessageBox(NULL,ms,
			_T("����"),NULL);
	}
}

//�����¼�
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