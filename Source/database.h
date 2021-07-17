#pragma once
#include "command.h"
#include <map>
#include "tape.h"

struct Initial {
	command::IState IState_;
	command::ISym ISym_;
};

auto GetIPairTie(const Initial& pair);

bool operator<(const Initial& lhs, const Initial& rhs);

class database
{
public:
	void push_back(const command& cm);
	std::size_t size() const;
	void clear();
	void erase(const command& cm);
	void erase(const Initial& init);
	const command& at(const Initial& init) const;
	std::size_t count(const Initial& init) const;

private:
	std::map<Initial, command> bd_;
};

std::istream& operator>>(std::istream& stream, database& bd_);

void emulate(const database& bd_, tape& tape_, std::string initial_state, std::ostream& output);