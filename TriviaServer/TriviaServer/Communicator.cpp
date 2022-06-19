#include "Communicator.h"
#include <thread>
#include "responseStruct.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <queue>
//the queue of the messages
std::queue <std::string> msg;
using json = nlohmann::json;


Communicator::Communicator(IDataAccess* dataAccess, RequestHandlerFactory& fact) : m_handlerFactory(fact)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}


void Communicator::handle_messages(int port)
{
	std::string s = "";
	std::thread th(&Communicator::bindAndListen, this, 8826);
	while (true)
	{
		if (!msg.empty())
		{
			//get from queue
			s = msg.front();
			msg.pop();
			//get the socket
			std::string soc = s.substr(0, 3);
			SOCKET tmp = (stoi(soc));
			s = s.substr(3);
			std::cout << s << std::endl;
			//send message to client
			send(tmp, s.c_str(), s.size(), 0);
		}
	}

	th.detach();
}

void Communicator::bindAndListen(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{

		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		// the function that handle the conversation with the client
		std::thread t(&Communicator::startHandleRequest, this, client_socket);
		t.detach();
		IRequestHandler* newHandler = new LoginRequestHandler(this->m_handlerFactory, this->m_handlerFactory.getLoginManager());
		m_clients.insert({ client_socket, newHandler });
	}
	
}

/*
convert to string by index
*/
std::string Communicator::convertToString(char* a, int start, int end)
{
	int i;
	std::string s = "";
	for (i = start; i < end; i++) {
		s = s + a[i];
	}
	return s;
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	/*SqliteDatabase db_backup;
	db_backup = m_;*/
	std::vector<unsigned char> vec;
	RequestResult res;
	SignupRequest sign;
	LoginRequest login;
	RequestInfo info;
	//LoginRequestHandler* log_handler = m_handlerFactory.createLoginRequestHandler();
	int len, count = 0, x = 0;
	//std::cout << "hi";

	while (true)
	{
		char m[LEN_OF_MESSAGE]{};

		x = recv(clientSocket, m, LEN_OF_MESSAGE, 0);
		
		if (x == -1)
		{
			std::cout << "client has disconnected!" << std::endl;
			break;
		}

		//making request info struct
		info.receivalTime = time(NULL);
		info.id = m[0] - '0';
		vec.insert(vec.begin(), std::begin(m), std::end(m));
		info.buffer = vec;
		vec.clear();

		auto it = this->m_clients.find(clientSocket);
		res = it->second->handleRequest(info, clientSocket);
		//this->m_handlerFactory.getLoginManager().;
		vec = res.response;

		std::cout << "received: " << m << std::endl;

		if (res.newHandler == NULL)
			std::cout << "illegal request!";
		else
			it->second = res.newHandler;

		std::cout << "received: " << m << std::endl;

				//convert to char vector in order to send the message
		std::vector<char> newOne = std::vector<char>(vec.begin(), vec.end());
		for (int i = 0; i < newOne.size(); i++) {
			std::cout << newOne[i];
		}
		send(clientSocket, &newOne[0], vec.size(), 0);
		
	}
}


void Communicator::startHandleRequest(SOCKET clientSocket)
{
	std::cout << "NEW CLIENT\n";
	std::string msg_socket = std::to_string(clientSocket);
	int len = 0;
	char m[LEN_OF_MESSAGE]{};

	msg.push(msg_socket + "hello");
	recv(clientSocket, m, LEN_OF_MESSAGE, 0);
	//len = (m[3] - 48) * 10 + (m[4] - 48);		//ASCI to len of name
	std::cout << "received: " << m << std::endl; //nativ wrote "receaved" -_-

	handleNewClient(clientSocket);

}
