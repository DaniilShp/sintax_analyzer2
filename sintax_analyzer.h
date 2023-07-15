

const int CommandsAmount = 4;

enum class CommandType {
	CREATE,
	ALTER,
	DROP,
    SELECT
};

const std::string CommandNames[CommandsAmount] = {
	"create table",
	"alter table",
	"drop table",
    "select"
};

class Analyzer
{
private:
	std::string command;
	void initialise();
	bool StrStartsWith(std::string);
public:
	Analyzer();
	bool AnaliseCreateTable();
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
    bool AnaliseSelect();
	bool StartAnalis(std::string command);

};

typedef bool (Analyzer::* TypeCommandAnalise)();

const TypeCommandAnalise CommandTypesFunctions[CommandsAmount] = {
	&Analyzer::AnaliseCreateTable,
	&Analyzer::AnaliseAlterTable,
	&Analyzer::AnaliseDropTable,
	&Analyzer::AnaliseSelect
};
