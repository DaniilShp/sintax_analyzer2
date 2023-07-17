#pragma once

const int CommandsAmount = 5;

enum class CommandType { // ������ �������������: CommandNames[(int)CommandType::CREATE] = "create table" � � CommandTypesFunctions �������� ����������
	CREATE,
	ALTER,
	DROP,
    SELECT,
    UPDATE
};

const std::string CommandNames[CommandsAmount] = {
        "create table",
        "alter table",
        "drop table",
        "select",
        "update"
};

class Analyzer
{
private:
	std::string command;
	void initialise();
	bool StrStartsWith(std::string);
	bool AnaliseWhere(std::vector<Token>&, size_t&);
public:
	Analyzer();
	bool AnaliseCreateTable();
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
    bool AnaliseSelect();
	bool StartAnalis(std::string command);

    bool AnaliseUpdate();
};

typedef bool (Analyzer::* TypeCommandAnalise)();		//��� ������, �������������� ����� ��������� �� �����

const TypeCommandAnalise CommandTypesFunctions[CommandsAmount] = { // ����������� ������ ��� ��������� ����������, � ������� ����� ���������� ������
	&Analyzer::AnaliseCreateTable,	// ����� ������� ��� ������������������ ������ ��� ������� ���� �������
	&Analyzer::AnaliseAlterTable,
	&Analyzer::AnaliseDropTable,
    &Analyzer::AnaliseSelect,
    &Analyzer::AnaliseUpdate
};