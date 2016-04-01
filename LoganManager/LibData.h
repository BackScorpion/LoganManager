#include "../LoganUI/UIlib.h"
#include <Windows.h>
#include <tchar.h>
#include <wchar.h>

/// curl
#include "../libcurl/include/curl/curl.h"
#include "../libcurl/include/curl/easy.h"
#include "../libcurl/include/curl/types.h"


using namespace std;
using namespace DuiLib;

#ifdef _DEBUG
#       pragma comment(lib, "..\\lib\\DuiLib_d.lib")
#else
#       pragma comment(lib, "..\\lib\\DuiLib.lib")
#endif


#pragma  comment(lib,"..\\libcurl\\libcurl.lib")


#define IPFILE					( _T("../Debug/config/ip.cfg"))
#define PORTFILE				(_T("../Debug/config/port.cfg"))
#define USERNAMETABLE			(_T("../Debug/config/userlist.loganlist"))
#define PATH					(_T("../Debug/config/"))