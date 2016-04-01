#pragma once
#include "LibData.h"

/************************************************************************/
/*                           �������󵽵�����                           */
/************************************************************************/

struct DATA
{
	char *mem;//���������
	size_t size;//���ݴ�С
};

//�ڴ����

inline void *memRealloc(void *ptr,size_t size)
{
	if(ptr)//������ڵ����ڴ治��
		return realloc(ptr,size);
	else
		return malloc(size);
}

// curl�Ļص�����ʵ�����ݵı���

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
	//��ȡ��������
	  char *GetRespond(string requestHttpArg);

};
