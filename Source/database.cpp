#include "database.h"

#include <istream>
#include <iostream>
#include "tuple"
#include <stdexcept>

auto GetIPairTie(const Initial& pair)
{
	return std::make_tuple(pair.IState_.value_, pair.ISym_.value_);
}

bool operator<(const Initial& lhs, const Initial& rhs)
{
	return GetIPairTie(lhs) < GetIPairTie(rhs);
}

void ignoreLine(std::istream& stream)
{
	char buff = ' ';
	while (buff != '\n' && buff != '\0' && buff != -1) buff = stream.get();
}

std::istream& operator>>(std::istream& stream, database& bd_)
{
	bool flag = false;
	
	std::size_t lines_ = 0;

	while (!stream.eof())
	{
		try {
			lines_++;

			if (stream.peek() != '\n' && stream.peek() != -1 && stream.peek() != '#') {
				bd_.push_back(make_command(stream));
			}
			else ignoreLine(stream);
		}

		catch (const std::exception& exception)
		{
			std::cerr << std::to_string(lines_) + " line: " << exception.what() + std::string(" ") + "\n";
			flag = true;
			std::cin.clear();
			char a;
			std::cin >> a;
		}
	}

	if (flag) exit(1);

	return stream;
}

void database::push_back(const command& cm)
{
	Initial pair = { cm.getIState(), cm.getISym() };
	if (bd_.count(pair) > 0) throw std::runtime_error("Programm is not deterministic");
	bd_[pair] = cm;
}

std::size_t database::size() const
{
	return bd_.size();
}

void database::clear()
{
	bd_.clear();
}

void database::erase(const command& cm)
{
	bd_.erase({ cm.getIState(), cm.getISym() });
}

void database::erase(const Initial& init)
{
	bd_.erase(init);
}

const command& database::at(const Initial& init) const
{
	return bd_.at(init);
}

std::size_t database::count(const Initial& init) const
{
	return bd_.count(init);
}

void emulate(const database& bd_, tape& tape_, std::string initial_state, std::ostream& output)
{
	command cm;
	int symbol = 0; // To show position of Turing machine head

	tape_.Output(output);
	output << "\n^\n";
	
	while(bd_.count({ command::IState(initial_state), command::ISym(tape_.getCurrent()) }))
	{
		cm = bd_.at({ command::IState(initial_state), command::ISym(tape_.getCurrent()) });
		tape_.getCurrent() = cm.getFSym().value_;
		initial_state = cm.getFState().value_;
		if (tape_.Shift(cm.getDir())) ++symbol;

		symbol += int(cm.getDir());
		if (symbol < 0) symbol = 0;

		tape_.Output(output);
		output << '\n';

		for (int i = 0; i < symbol; ++i) output << ' ';
		output << "^\n";
	}

	// to show final state
	/*symbol += int(cm.getDir());
	if (symbol < 0) symbol = 0;

	tape_.Output(output);
	output << '\n';

	for (int i = 0; i < symbol; ++i) output << ' ';
	output << "^\n";*/
}