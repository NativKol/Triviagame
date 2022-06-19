#pragma once
#include "JsonResponsePacketSerializer.h"
#include "requestStruct.h"
#include "responseStruct.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include <vector>
//#define SIGNUP false
//#define LOGIN true
class IRequestHandler;
class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory fact, LoginManager man);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo info);
	virtual RequestResult handleRequest(RequestInfo info, SOCKET clientSocket);
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
	RequestResult login(RequestInfo info, SOCKET clientSocket);
	RequestResult signup(RequestInfo info, SOCKET clientSocket);
};