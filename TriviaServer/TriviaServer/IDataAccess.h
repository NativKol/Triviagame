#pragma once
#include <list>
#include <string>
#include <vector>
#include "Question.h"

/*
                  AVG OF CORRECT ANSWERS(INT)
SCORE =    --------------------------------------    + CORRECT ANSWERS
           0.1 * (AVG TIME FOR QUESTION / 5) + 1
*/

class IDataAccess
{
public:
    virtual ~IDataAccess() = default;

    //USERS
    virtual bool DoesUserExist(const std::string& name) = 0;
    virtual bool DoesPasswordMatch(const std::string& name, const std::string& pass) = 0;
    virtual void AddNewUser(const std::string& name, const std::string& pass, const std::string& email) = 0;

    //QUIZ
    virtual std::list<Question> getQuestions(const int& amount) = 0;

    //STATS
    virtual float getPlayerAverageAnswerTime(const std::string& name) = 0;
    virtual int getNumOfCorrectAnswers(const std::string& name) = 0;
    virtual int getNumOfTotalAnswers(const std::string& name) = 0;
    virtual int getNumOfPlayersGames(const std::string& name) = 0;
    virtual int getPlayerScore(const std::string& name) = 0;
    virtual std::vector<std::string> getHighScores() = 0;

    //database related
    virtual bool open() = 0;
    virtual void close() = 0;
};