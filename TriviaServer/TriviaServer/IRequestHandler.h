#pragma once
#include "requestStruct.h"
#include "responseStruct.h"
struct RequestResult;
struct RequestInfo;
//RequestInfo info;

class IRequestHandler
{
public: 
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info, SOCKET clientSocket) = 0;
};