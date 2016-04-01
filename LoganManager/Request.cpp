#include "Request.h"
#include "LibData.h"
Request::Request(void)
{
}

Request::~Request(void)
{
}


 char*  Request::GetRespond(string requestHttpArg)
 {
	 CURL *curl;

	 struct DATA chunk;

	 chunk.mem=NULL; 
	 chunk.size = 0;   
	 curl_global_init(CURL_GLOBAL_ALL);

	 curl = curl_easy_init();

	 curl_easy_setopt(curl, CURLOPT_URL, requestHttpArg.c_str());
	 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToMemoryCallback);

	 curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	 curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	 curl_easy_perform(curl);
	 curl_easy_cleanup(curl);

	 curl_global_cleanup();
	 return (char*)chunk.mem;

 }