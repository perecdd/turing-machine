#include "command.h"
#include <string>
#include <exception>
#include <sstream>
#include <algorithm>

#include <iostream>

command::command(std::string input)
{
	input = clearArrow(clear(input));
	std::size_t count = std::count(input.begin(), input.end(), ',');

	// '->' in 'clear' is replaced by ',', then 3 (m. T. commands standard) + 1 = 4.
	if (count > 4) throw std::invalid_argument("Syntax error: invalid character used ','");
	if (count < 4) throw std::invalid_argument("Syntax error: missing ','");
	
	std::stringstream stream(input);

	std::getline(stream, initial_state_, ',');
	if (initial_state_.empty()) throw std::invalid_argument("Syntax error: missing initial state");

	std::getline(stream, initial_sym_, ',');
	if (initial_sym_.empty()) throw std::invalid_argument("Syntax error: missing initial symbol");

	std::getline(stream, finish_state_, ',');
	if (finish_state_.empty()) throw std::invalid_argument("Syntax error: missing finish state");

	std::getline(stream, finish_sym_, ',');
	if (finish_sym_.empty()) throw std::invalid_argument("Syntax error: missing finish symbol");

	int buff;
	stream >> buff;
	direction_ = buff;
	
	if(direction_ > 1 || direction_ < -1) throw std::invalid_argument("Syntax error: the shift must belong to the range [-1; 1]");
}

command::command(){}

std::string command::formate() const
{
	return initial_state_ + ", " + initial_sym_ + " -> " + finish_state_ + ", " + finish_sym_ + ", " + std::to_string(direction_) + ';';
}

command::ISym command::getISym() const
{
	return ISym(initial_sym_);
}

command::IState command::getIState() const
{
	return IState(initial_state_);
}

command::FSym command::getFSym() const
{
	return FSym(finish_sym_);
}

command::FState command::getFState() const
{
	return FState(finish_state_);
}

std::int8_t command::getDir() const
{
	return direction_;
}

std::string command::clear(std::string a) const
{
	auto it0 = find(a.begin(), a.end(), '#');
	a.erase(it0, a.end());
	
	auto it = std::remove_if(a.begin(), a.end(), [](const char& c) {return c == ' ' || c == '+' || c == '\n'; });
	a.erase(it, a.end());
	return a;
}

std::string command::clearArrow(std::string a) const
{
	std::size_t pos = a.find("->");
	if (pos == std::string::npos) throw std::invalid_argument("Syntax error: missing '->'");

	a[pos] = ',';
	a.erase(pos + 1, 1);
	return a;
}

command make_command(std::istream& stream)
{
	std::string str;
	std::getline(stream, str);
	return command(str);
}

command::ISym::ISym(const std::string& string)
	: value_(string) {}

command::IState::IState(const std::string& string)
	: value_(string) {}

command::FSym::FSym(const std::string& string)
	: value_(string) {}

command::FState::FState(const std::string& string)
	: value_(string) {}