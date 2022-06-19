#include "Question.h"

Question::Question(std::string question, std::vector<std::string> answers, std::string correct)
{
	this->_question = question;
	this->_answers = answers;
	this->_correct = correct;
}

Question::~Question()
{
	this->_question = "";
	this->_answers.clear();
	this->_correct = "";
}

std::string Question::getQuestion()
{
	return this->_question;
}

std::vector<std::string> Question::getAnswers()
{
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(this->_answers), std::end(this->_answers), rng);
	return this->_answers;
}

std::string Question::getCorrect()
{
	return this->_correct;
}
