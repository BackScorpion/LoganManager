#include "LibData.h"
#include "MainWindow.h"
#include "LogIn.h"
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) 
		return 0;
	

	UINT res;

	LogIn *login=new LogIn();
	login->Create(NULL,_T("��¼"),UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	login->CenterWindow();
	res=login->ShowModal();
	if(res==IDOK)
	{
		//��¼�ɹ� ������ҳ
		
		MainWindow *mainWindow=new MainWindow();
		mainWindow->Create(NULL,_T("mainWindows"),UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
		mainWindow->CenterWindow();
		mainWindow->ShowModal();
	}
	else
	{
		// ��¼ʧ��
	}

	return 0;

}