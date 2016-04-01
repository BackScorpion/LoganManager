#pragma once
#include "LibData.h"

/************************************************************************/
/*                           保存请求到的数据                           */
/************************************************************************/

struct DATA
{
	char *mem;//保存的内容
	size_t size;//数据大小
};

//内存分配

inline void *memRealloc(void *ptr,size_t size)
{
	if(ptr)//如果存在但是内存不够
		return realloc(ptr,size);
	else
		return malloc(size);
}

// curl的回调函数实现数据的保存

static size_t writeToMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct DATA *mem = (struct DATA *)data;

	mem->mem = (char *)memRealloc(mem->mem, mem->size + realsize + 1);
	if (mem->mem) {
		memcpy(&(mem->mem[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->mem[mem->size] = 0;
	}
	return realsize;
}
/*********************************************************/

class Request
{
public:
	Request(void);
	~Request(void);
	//获取请求内容
	  char *GetRespond(string requestHttpArg);

};
