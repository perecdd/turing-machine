#pragma once
#include <string>

class command
{
public:
	struct ISym
	{
		explicit ISym(const std::string& string);
		const std::string value_;
	};

	struct IState
	{
		explicit IState(const std::string& string);
		const std::string value_;
	};

	struct FSym
	{
		explicit FSym(const std::string& string);
		const std::string value_;
	};

	struct FState
	{
		explicit FState(const std::string& string);
		const std::string value_;
	};
	
	explicit command(std::string input);

	command();
	std::string formate() const;
	
	ISym getISym() const;
	IState getIState() const;
	FSym getFSym() const;
	FState getFState() const;
	std::int8_t getDir() const;

private:
	std::string initial_state_;
	std::string initial_sym_;

	std::string finish_state_;
	std::string finish_sym_;

	std::int8_t direction_;

	std::string clear(std::string a) const;

	std::string clearArrow(std::string a) const;
};

void TestCommands();

command make_command(std::istream& stream);