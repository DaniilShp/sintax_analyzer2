#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>

enum class token_type
{
    Error = -1,
    Identifier,
    MainOperator,
    SecondaryOperator,
    VariableType,
    constant,
    LBRA, // {
    RBRA, // }
    LPAR, // (
    RPAR, // )
    LSQR, // [
    RSQR, // ]
    DOT,  // .
    COMMA, // ,
    SMCLN,  // ; semicolon
    WRT, // =
    FROM,
    WHERE,
    UPDATE,
    SET,
    GRB, //Group by
    CMP  //comparison symbols: =, <, >, !, 
};

class Token
{
private:
    std::string name;
    token_type type;
    token_type FindType(const std::string&);
    bool IsIdentifier(const std::string& str);
public:
    Token(const std::string& tkn) { name = tkn; type = this->FindType(tkn); };
    token_type GetType() { return this->type; };
    std::string GetName() { return this->name; };
    static std::vector<Token> GetTokens(const std::string& str);
};

