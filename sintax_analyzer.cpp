#include "token.h"
#include "sintax_analyzer.h"

#include <algorithm>
#include <iostream>
#include <regex> // не стоит это использовать
#include <string>
#include <vector>
#include <cctype>


Analyzer::Analyzer() 
{ 
	initialise();
}

void Analyzer::initialise()
{
	//может потом пригодится
}

bool Analyzer::AnaliseCreateTable()		// специализированные методы. они нужны так для каждого ключевого оператора (create alter и т д ) используются разные вспомогательные операторы
{
	std::vector<Token> TokensLine = Token::GetTokens(command);
	if (7 >= TokensLine.size()) return false;
	for (auto& tkn : TokensLine) {
		//std::cout << tkn.GetName() << (int)tkn.GetType();
	}
	if (TokensLine[0].GetType() != token_type::MainOperator && TokensLine[1].GetType() != token_type::MainOperator)
		return false;
	if (TokensLine[2].GetType() != token_type::Identifier) return false;
	if (TokensLine[3].GetType() != token_type::LPAR) return false;
	int i = 4; //size_t
	for (; i < TokensLine.size()-4;i+=3) {
		if (TokensLine[i].GetType() != token_type::Identifier) return false;
		if (TokensLine[i+1].GetType() != token_type::VariableType) return false;
		if (TokensLine[i + 2].GetType() != token_type::COMMA) return false;
	}
	if (TokensLine[i].GetType() != token_type::Identifier) return false;
	if (TokensLine[++i].GetType() != token_type::VariableType) return false;
	if (TokensLine[++i].GetType() != token_type::RPAR) return false;
	if (TokensLine[++i].GetType() != token_type::SMCLN) return false;
	return true;

}


bool Analyzer::AnaliseAlterTable()
{
	int i = 3;
	std::vector<Token> TokensLine = Token::GetTokens(command);
	if ( 6 >= TokensLine.size()) return false;
	if (TokensLine[0].GetType() != token_type::MainOperator && TokensLine[1].GetType() != token_type::MainOperator)
		return false;
	if (TokensLine[2].GetType() != token_type::Identifier) return false;
	if ((TokensLine[3].GetName()) == "add" ) {
		if (TokensLine[++i].GetType() != token_type::Identifier) return false;
		if (TokensLine[++i].GetType() != token_type::VariableType) return false;
	}
	else if ((TokensLine[3].GetName()) == "alter") {
		if ((TokensLine[++i].GetName()) == "column") return false;
		if (TokensLine[++i].GetType() != token_type::Identifier) return false;
		if (TokensLine[++i].GetType() != token_type::VariableType) return false;
	}
	else if ((TokensLine[3].GetName()) == "drop") {
		if ((TokensLine[++i].GetName()) == "column") return false;
		if (TokensLine[++i].GetType() != token_type::Identifier) return false;
	}
	else return false;
	if (7 >= TokensLine.size()) {
		if (TokensLine[++i].GetType() != token_type::SMCLN) return false;
	}
	return true;
}

bool Analyzer::AnaliseDropTable()
{
	std::vector<Token> TokensLine = Token::GetTokens(command);
	if (4 != TokensLine.size()) return false;
	if (TokensLine[0].GetType() != token_type::MainOperator && TokensLine[1].GetType() != token_type::MainOperator)
		return false;
	if (TokensLine[2].GetType() != token_type::Identifier) return false;
	if (TokensLine[3].GetType() != token_type::SMCLN) return false;
	return true;
}

bool Analyzer::AnaliseSelect()
{
    std::vector<Token> TokensLine = Token::GetTokens(command);
    if(TokensLine.size() <= 4 )
    if (TokensLine[0].GetType() != token_type::MainOperator) return false;
    if (TokensLine[1].GetType() != token_type::Identifier) return false;
    if (TokensLine[2].GetType() != token_type::FROM) return false;
    if (TokensLine[3].GetType() != token_type::Identifier) return false;
    if (TokensLine[4].GetType() != token_type::WHERE) {
        if (TokensLine[5].GetType() != token_type::Identifier) return false;
        if (TokensLine[6].GetType() != token_type::SMCLN) return false;
        //TODO реализовать что может быть после WHERE после WHERE надо писать GROUP BY
    }
    if (TokensLine[4].GetType() != token_type::SMCLN) return false;
    return true;
}

bool Analyzer::StrStartsWith(std::string key) // проверка с какого ключевого слова начинается запрос
{
	for (int i = 0; i < this->command.length(); i++)
	{
		if (this->command[i] == ' ' || this->command[i] == '\t')	//игнорирование пробелов и табуляций
			continue;
		if (this->command.find(key) == i)
			return true;
		else
			return false;
	}
	return false;
}

bool Analyzer::StartAnalis(std::string _command)	//запуск анализа 
{
	command.clear();
	for (auto& c : _command) {
		command += std::tolower(c);
	}
	for (int i = 0; i < CommandsAmount; i++) {
		if (this->StrStartsWith(CommandNames[i]))
		{
			return ((this->*CommandTypesFunctions[i])());	// в зависимости от ключевого слова в начале запроса вызываются разные специализированные методы
		}
	}
	return false;
}

int main()
{
	std::string text1 = "drop table tablename;";
	std::string text2 = "create table tablename (id int, data date, cost int);";
	std::string text3 = "alter table tablename add id int;";
    std::string text4 = "select a from b;";
    std::string text5 = "select a from b where c;";
	Analyzer analyzer;
	std::cout << analyzer.StartAnalis(text1) << std::endl;
	std::cout << analyzer.StartAnalis(text2) << std::endl;
	std::cout << analyzer.StartAnalis(text3) << std::endl;
	return 0;
}

/*
пока только это работает

CREATE TABLE table_name
(
	column_name_1 column_type_1,
	column_name_2 column_type_2,
	...,
	column_name_N column_type_N,
);

ALTER TABLE название_таблицы
{ ADD название_столбца тип_данных_столбца |
  DROP COLUMN название_столбца |
  ALTER COLUMN название_столбца тип_данных_столбца }

DROP TABLE table_name
*/