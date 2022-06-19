#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Question
{
public:
	Question(std::string question, std::vector<std::string> answers, std::string correct);
	~Question();
	std::string getQuestion();
	std::vector<std::string> getAnswers();
	std::string getCorrect();

private:
	std::string _question;
	std::vector<std::string> _answers;
	std::string _correct;
};

