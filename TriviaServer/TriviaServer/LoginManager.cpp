#include "LoginManager.h"

LoginManager::LoginManager()
{
    //this->m_database = nullptr;
}

LoginManager::LoginManager(IDataAccess* dataAccess) :
    m_database(dataAccess)
{
    this->m_loggedUsers.clear();
    //this->m_database.open();
}

LoginManager::~LoginManager()
{
    this->m_loggedUsers.clear();
    //this->m_database->close();
    //delete this;
}

bool LoginManager::SignUp(std::string name, std::string pass, std::string email)
{
    if (m_database->DoesUserExist(name))
    {
        std::cout << "User does already exist!" << std::endl;
        return false;
    }
    else
    {
        m_database->AddNewUser(name, pass, email);
        return true;
    }
}

bool LoginManager::LogIn(std::string name, std::string pass, SOCKET clientSocket)
{
    //std::cout << this->m_database;
    if (!(m_database->DoesPasswordMatch(name, pass)))
    {
        std::cout << "No existing user" << std::endl;
        return false;
    }
    else
    {
        this->m_loggedUsers.push_back(LoggedUser(name, clientSocket));
        return true;
    }
}

bool LoginManager::LogOut(std::string name)
{
    int j = 0;
    int size = m_loggedUsers.size();

    for (auto& i : m_loggedUsers) 
    {
        if (i.getUsername() == name)
        {
            m_loggedUsers.erase(m_loggedUsers.begin() + j);
            return true;
        }
        j++;
    }

    std::cout << "User does not exist" << std::endl; //retuen false
    return false;
}

std::vector<LoggedUser> LoginManager::getUsers()
{
    return this->m_loggedUsers;
}
