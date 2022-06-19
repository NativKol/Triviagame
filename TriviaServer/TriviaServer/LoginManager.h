#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <exception>
#include "LoggedUser.h"
#include "IDataAccess.h"
#include <algorithm>

#define ASCI_TO_INT 48;
#define LEN_OF_MESSAGE 49

enum options {
    zero,
    sign_in,
    sign_out,
    account_print,
    EXIT
};

class LoginManager
{
public:
    LoginManager();
    LoginManager(IDataAccess* dataAccess);
    ~LoginManager();
    bool SignUp(std::string name, std::string pass, std::string email);
    bool LogIn(std::string name, std::string pass, SOCKET clientSocket);
    bool LogOut(std::string name);

    std::vector<LoggedUser> getUsers();

private:
    std::vector<LoggedUser> m_loggedUsers;
    IDataAccess* m_database;
};