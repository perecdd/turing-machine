#include "tape.h"

tape::tape(const std::string& string)
{
	for (const auto& k : string) tape_.push_back(std::to_string(k));
}

tape::tape(){}

void tape::push_back(const std::string& sym)
{
	tape_.push_back(sym);
}

void tape::push_front(const std::string& sym)
{
	tape_.push_front(sym);
}

void tape::pop_back()
{
	tape_.pop_back();
}

void tape::pop_front()
{
	tape_.pop_front();
}

std::string& tape::getCurrent() const
{
	if (it == tape_.end()) throw std::out_of_range("Tape: Out of range");
	return *it;
}

void tape::ToBegin()
{
	it = tape_.begin();
}

void tape::ToEnd()
{
	it = tape_.end();
	if (tape_.begin() != tape_.end()) --it;
}

std::istream& operator>>(std::istream& stream, tape& tape_)
{
	tape_.clear();
	std::string str;
	std::getline(stream, str);
	for(std::size_t i = 0; i < str.size(); ++i)
	{
		std::string s;
		s += str[i];
		tape_.push_back(s);
	}
	if (tape_.size() == 0) tape_.push_back(tape_.empty_string); // case when tape is empty
	tape_.ToBegin();
	return stream;
}

void tape::Output(std::ostream& stream)
{
	for(const auto& k : tape_)
	{
		stream << k;
	}
}

void tape::Shift(std::int8_t direction_)
{
	switch(direction_)
	{
	case -1:
		if (it != tape_.begin()) --it;
		if (it == tape_.begin())
		{
			tape_.push_front(empty_string);
			it = tape_.begin();
		}
		break;

	case 0:
		break;

	case 1:
		if (it != tape_.end()) ++it;
		if (it == tape_.end())
		{
			tape_.push_back(empty_string);
			it-- = tape_.end();
		}
		break;

	default:
		throw std::invalid_argument("Tape: direction does not belong to [-1;1]");
	}
}

void tape::clear()
{
	tape_.clear();
}

std::size_t tape::size()
{
	return tape_.size();
}
