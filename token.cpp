

#include "token.h"
#include <string>
#include <iostream>
#include <vector>
#include <array>

bool Token::IsIdentifier(const std::string& str)
{
    for (char c : str) {
        if (!((c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || c == '_'))
            return false;
    }
    return true;
}

token_type Token::FindType(const std::string& tkn) // ��� ������� ������� ������� ����� ���� �������, ��� ��� ����� ������ ������ ����� �������
{                                                  // ���� ���������� �������� ����� ������� � get tokens � ����� � ����, ����� ��������� �� ��� ��������
    if (tkn == "create" || tkn =="table" || tkn == "alter" || tkn == "drop" || tkn == "select") return token_type::MainOperator;
    if (tkn =="(") return token_type::LPAR;   // ��� create table 6-7 ����� �������, ��� alter 10+, ��� drop 3-4, ��� select 15+
    if (tkn == ")") return token_type::RPAR;
    if (tkn == ",") return token_type::COMMA;
    if (tkn == "int" || tkn == "date" || tkn== "time" || tkn== "text") return token_type::VariableType; //varchar(x) �������, ���� text
    if (tkn == "add" || tkn== "drop" || tkn== "modify") return token_type::SecondaryOperator;
    if (tkn == ";") return token_type::SMCLN;
    if (tkn == "from") return token_type::FROM;
    if (tkn =="where") return token_type::WHERE;
    if (tkn == "update") return token_type::UPDATE;
    if (tkn == "set") return token_type::SET;
    if (tkn == "=") return token_type::WRT;
    if (IsIdentifier(tkn)) return token_type::Identifier; // �������� ��� �� �� ����������������
    else return token_type::Error;
}

std::vector<Token> Token::GetTokens(const std::string& str) {
    std::vector<Token> tokens; // ������ ����
    std::string token; // ������� �����
    std::array<char, 11> separators = { ' ', '\t', '\n', '(', ')', '[', '{', '}', '.', ',', ';'};
    for (char c : str) { // �������� �� ������� ������� � ������
        if (c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' | c == '}' || c == '.' || c == ',' || c == ';' || c == '=' || c == '!' || c == '<' || c == '>') { // ���� ������ �������� ������������
            if (!token.empty()) { // ���� ������� ����� �� ������
                tokens.push_back(Token(token)); // ��������� ��� � ������ ����
                token.clear(); // ������� ������� �����
            }
            if (c != ' ' && c != '\t' && c != '\n') {
                tokens.push_back(Token(std::string(1, c)));
            }
        }
        else { // ����� ��������� ������ � ������� �����
            token += c;
        }
    }
    if (!token.empty()) { // ��������� ���������� ����� � ������ (���� ��� ����)
        tokens.push_back(Token(token));
    }
    return tokens; // ���������� ������ ����
}

