#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory fact, LoginManager man) : m_loginManager(man), m_handleFactory(fact)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id == signup_ || info.id == login_)
		return true;
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info, SOCKET clientSocket) //need to change and return 
{
	ErrorResponse err_mes;
	err_mes.message = "Error!";

	std::vector<unsigned char> vec;
	if (isRequestRelevant(info))
	{
		if (info.id == signup_)
		{
			return signup(info, clientSocket);
		}
		else
		{
			return login(info, clientSocket);
		}
	}
	else
		vec = JsonResponsePacketSerializer::serializeResponse(err_mes);
	RequestResult result;
	result.response = vec;
	result.newHandler = nullptr;
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo info, SOCKET clientSocket)
{
	LoginResponse log_mes;
	RequestResult res;
	LoginRequest log_req = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	LoggedUser user(log_req.username, clientSocket);
	MenuRequestHandler* menu = this->m_handleFactory.createMenuRequestHandler(user);

	if (m_loginManager.LogIn(log_req.username, log_req.password, clientSocket))
	{
		log_mes.status = 1;
		res.newHandler = &(*menu);
	}
	else
	{
		log_mes.status = 0;
		res.newHandler = this;
	}

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(log_mes);
	res.response = vec;
	return res;
}

RequestResult LoginRequestHandler::signup(RequestInfo info, SOCKET clientSocket)
{
	RequestResult res;
	SignupResponse sign_mes;
	SignupRequest sign_req = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);

	LoggedUser user(sign_req.username, clientSocket);
	MenuRequestHandler* menu = this->m_handleFactory.createMenuRequestHandler(user);

	if (m_loginManager.SignUp(sign_req.username, sign_req.password, sign_req.email))
	{
		sign_mes.status = 1;
		res.newHandler = &(*menu);
	}
	else
	{
		sign_mes.status = 0;
		res.newHandler = this;
	}

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(sign_mes);
	res.response = vec;
	return res;
}
