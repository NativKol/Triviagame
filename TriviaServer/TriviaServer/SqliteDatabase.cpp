#include "SqliteDatabase.h"

//global variables
bool exist = false; // to check if user exist
int numSave = 0;
float dualSave = 0;
std::vector<std::string> namesSave;

//QUESTIONS
std::string questionSave;
std::string correctSave;
std::vector<std::string> answersSave;
std::list<Question> quizSave;

//callback that check if ther feild exist bigger than 0
int callback_existUser(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "EXIST")
		{
			//std::cout << azColName[i] << " = " << argv[i] << std::endl;
			if (*argv[i] == '0')
			{
				exist = false;
			}
			else
			{
				exist = true;
			}
			return 0;
		}
	}
	std::cout << std::endl;
	return 0;
}

SqliteDatabase::SqliteDatabase()
{
	this->open();
}

/*
check if ther user with that name
*/
bool SqliteDatabase::DoesUserExist(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT count(username) AS EXIST FROM User WHERE username == \"" +
		name + "\";";

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_existUser, nullptr, errMessage);
	return exist;
}

/*
check if there user with that name and the password is belong to him
*/
bool SqliteDatabase::DoesPasswordMatch(const std::string& name, const std::string& pass)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT count(username) AS EXIST FROM User WHERE username == \"" +
		name + "\" and user_password == \"" + pass + "\";";

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_existUser, nullptr, errMessage);
	return exist;
}

/*
insert user (with name, passwoed, email)
*/
void SqliteDatabase::AddNewUser(const std::string& name, const std::string& pass, const std::string& email)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "INSERT INTO User VALUES(\"" + name + "\", \"" +
		pass + "\", \"" + email + "\");";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return;
}


//callback that check get data of int/float
int callback_getQuestionsData(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "Question")
		{
			questionSave = argv[i];
			answersSave.clear();
		}
		if (std::string(azColName[i]) == "Answer1")
		{
			answersSave.push_back(argv[i]);
		}
		if (std::string(azColName[i]) == "Answer2")
		{
			answersSave.push_back(argv[i]);
		}
		if (std::string(azColName[i]) == "Answer3")
		{
			answersSave.push_back(argv[i]);
		}
		if (std::string(azColName[i]) == "Answer4")
		{
			answersSave.push_back(argv[i]);
		}
		if (std::string(azColName[i]) == "Correct")
		{
			correctSave = argv[i];
			quizSave.push_back(Question(questionSave, answersSave, correctSave));
		}
	}
	std::cout << std::endl;
	return 0;
}

std::list<Question> SqliteDatabase::getQuestions(const int& amount)
{
	answersSave.clear();
	quizSave.clear();

	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "select * from Questions ORDER BY RANDOM() LIMIT " + std::to_string(amount) + "; ";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getQuestionsData, nullptr, errMessage);

	return quizSave;
}

//callback that check get data of int/float
int callback_getData(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "DataINT")
		{
			//std::cout << azColName[i] << " = " << argv[i] << std::endl;
			numSave = std::stoi(argv[i]);;
		}
		if (std::string(azColName[i]) == "DataFLOAT")
		{
			//std::cout << azColName[i] << " = " << argv[i] << std::endl;
			dualSave = std::stof(argv[i]);;
		}
	}
	std::cout << std::endl;
	return 0;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT avg_time as DataFLOAT FROM Stats WHERE username == \"" + name + "\";";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getData, nullptr, errMessage);
	float value = round(dualSave * 100) / 100;
	return value;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT correct_answers as DataINT FROM Stats WHERE username == \"" + name + "\";";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getData, nullptr, errMessage);
	return numSave;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT total_answers as DataINT FROM Stats WHERE username == \"" + name + "\";";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getData, nullptr, errMessage);
	return numSave;
}

int SqliteDatabase::getNumOfPlayersGames(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT games_played as DataINT FROM Stats WHERE username == \"" + name + "\";";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getData, nullptr, errMessage);
	return numSave;
}

int SqliteDatabase::getPlayerScore(const std::string& name)
{
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT score as DataINT FROM Stats WHERE username == \"" + name + "\";";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getData, nullptr, errMessage);
	return numSave;
}

//callback that add to vector names by order
int callback_getRecords(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "username")
		{
			namesSave.push_back(argv[i]);
		}
	}
	std::cout << std::endl;
	return 0;
}


std::vector<std::string> SqliteDatabase::getHighScores()
{
	namesSave.clear();
	char** errMessage = nullptr;
	std::string sqlCommand;
	int res;

	sqlCommand = "SELECT username FROM Stats ORDER BY score DESC LIMIT 5; ";

	std::cout << sqlCommand << std::endl;

	const char* sqlStatement = sqlCommand.c_str();

	res = sqlite3_exec(db, sqlStatement, callback_getRecords, nullptr, errMessage);

	return namesSave;
}

bool SqliteDatabase::open()
{
	//open the database by file name
	std::string dbFileName = "UserData.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	//check if exist
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist == 0)
	{
		//close db
		std::cout << "The file already exists" << std::endl;
	}
	else if (file_exist != 0)
	{
		// init database
		std::cout << "Create new database.." << std::endl;

		char** errMessage = nullptr;
		const char* sqlStatement;

		//Create User Table
		sqlStatement = R""""""(CREATE TABLE User(
			username TEXT PRIMARY KEY,
			user_password TEXT,
			email TEXT);
			 )"""""";

		res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
			return false;

		//Create Stats Table
		sqlStatement = R""""""(CREATE TABLE Stats(
			username TEXT PRIMARY KEY,
			games_played INTEGER,
			correct_answers INTEGER,
			total_answers INTEGER,
			avg_time REAL,
			score INTEGER,
			FOREIGN KEY (username) REFERENCES USER(username)
			);
			 )"""""";

		res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
			return false;

		//Create Question Table
		sqlStatement = R""""""( CREATE TABLE "Questions" (
			Question TEXT PRIMARY KEY,
			Answer1 TEXT,
			Answer2 TEXT,
			Answer3 TEXT,
			Answer4 TEXT,
			Correct TEXT);
			 )"""""";

		res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
			return false;

	}
	return true;
}

void SqliteDatabase::close()
{
	sqlite3_close(db);
	db = nullptr;
}


