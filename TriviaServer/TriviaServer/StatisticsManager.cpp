#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDataAccess& database) : m_database(database)
{
	//this->m_database.open();
}

////StatisticsManager::~StatisticsManager()
////{
////	this->m_database.close();
////}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return this->m_database.getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> copy;
	copy.push_back(std::to_string(this->m_database.getNumOfPlayersGames(username)));
	copy.push_back(std::to_string(this->m_database.getNumOfCorrectAnswers(username)));
	copy.push_back(std::to_string(this->m_database.getNumOfTotalAnswers(username)));
	copy.push_back(std::to_string(this->m_database.getPlayerAverageAnswerTime(username)));
	return copy;
}
