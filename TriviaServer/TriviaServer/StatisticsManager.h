#pragma once
#include "IDataAccess.h"
#include "SqliteDatabase.h"
#include <vector>
#include <string>
#include "sqlite3.h"

class StatisticsManager
{
public:
	StatisticsManager(IDataAccess& database);
	//~StatisticsManager();
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);

private:
	IDataAccess& m_database;
};
