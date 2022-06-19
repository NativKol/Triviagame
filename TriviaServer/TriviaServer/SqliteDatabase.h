#pragma once
#include <list>
#include "IDataAccess.h"
#include "sqlite3.h"
#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include "Question.h"

class SqliteDatabase : public IDataAccess
{

public:
	SqliteDatabase();
	virtual ~SqliteDatabase() = default;

	//USERS
	bool DoesUserExist(const std::string& name);
	bool DoesPasswordMatch(const std::string& name, const std::string& pass);
	void AddNewUser(const std::string& name, const std::string& pass, const std::string& email);

	//QUIZ
	std::list<Question> getQuestions(const int& amount);

	//STATS
	float getPlayerAverageAnswerTime(const std::string& name);
	int getNumOfCorrectAnswers(const std::string& name);
	int getNumOfTotalAnswers(const std::string& name);
	int getNumOfPlayersGames(const std::string& name);
	int getPlayerScore(const std::string& name);
	std::vector<std::string> getHighScores();

	//database related
	bool open() override;
	void close() override;

private:
	sqlite3* db;
};
