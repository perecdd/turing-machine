#pragma once
#include <list>
#include <string>
#include <iostream>

class tape
{
public:
	tape(const std::string& string);
	tape(); // tape can be empty
	void push_back(const std::string& sym); // string is necessary so that you can specify combined characters
	void push_front(const std::string& sym);
	void pop_back();
	void pop_front();
	std::string& getCurrent() const;
	void ToBegin();
	void ToEnd();
	void Output(std::ostream& stream);
	void Shift(std::int8_t direction_);
	void clear();
	std::size_t size();

	const char* empty_string = "^";
private:
	std::list<std::string> tape_;
	std::list<std::string>::iterator it = tape_.end();
};

std::istream& operator>>(std::istream& stream, tape& tape_);