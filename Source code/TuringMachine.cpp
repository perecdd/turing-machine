#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct rule {
	std::string stateStart;
	char startSym;

	std::string stateEnd;
	char endSym;

	int move;
};

class TuringMachine {
private:
	std::vector<std::string> Q;

	std::string state = "E";
	std::string end = "E";

	std::vector<char> A;
	std::vector<rule> P;

	std::vector<char> Feed;
	int workIndex = 0;

	bool DoWork() {
		if (state == end || workIndex > Feed.size() - 1) {
			return false;
		}

		for (rule a : P) {
			if (a.stateStart == state && a.startSym == Feed[workIndex]) {
				Feed[workIndex] = a.endSym;
				state = a.stateEnd;
				workIndex += a.move;
				return true;
			}
		}

		return false;
	}

public:
	friend std::ostream& operator<<(std::ostream& stream, TuringMachine& mach) {
		for (char c : mach.Feed) {
			stream << c;
		}

		return stream;
	}

	void DoFeed(std::string NewFeed) {
		for (char a : NewFeed) {
			Feed.push_back(a);
		}
	}

	void DoFeed(std::vector<char> NewFeed) {
		for (char a : NewFeed) {
			Feed.push_back(a);
		}
	}

	void DoFeed(const char* string) {
		for (int i = 0; string[i] != '\0'; i++) {
			Feed.push_back(string[i]);
		}
	}

	void DoFeed(char a) {
		Feed.push_back(a);
	}

	TuringMachine(std::vector<std::string>& Q, std::vector<char>& A, std::vector<rule>& P, std::string& start, std::string& end) {
		this->Q = Q;
		this->A = A;
		this->P = P;
		this->state = start;
		this->end = end;
	}

	void Work() {
		while (DoWork() == true);
	}
};

void strClean(std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ' || str[i] == ',' || str[i] == ';') {
			str.erase(str.begin() + i);
			i--;
		}
	}
}

int main()
{
	std::string name;

	std::vector<std::string> Q(1);
	std::vector<char> A;
	std::vector<rule> P;
	std::string start;
	std::string end;

	std::string startStatus;
	std::string endStatus;

	std::cin >> name;

	char buffC = ' ';
	int index = 0;

	std::ifstream f(name.c_str());

	if (!f) {
		return 1;
	}

	// Считывание программы*/

	std::string buff;
	while (f.get() != '\n') {
		f.unget();
		f >> buff;
		Q.push_back(buff);
	}

	while (f.get() != '\n') {
		f.unget();
		f >> buffC;
		A.push_back(buffC);
	}

	f >> buff;
	start = buff;
	// Начальное состояние

	f >> buff;
	end = buff;
	// Конечное состояние

	// Считываем программу

	while (!f.eof()) {
		rule r;
		std::string buffer;

		f >> buffer;
		strClean(buffer);
		r.stateStart = buffer;

		f >> r.startSym;

		f >> buffer;

		f >> buffer;
		strClean(buffer);
		r.stateEnd = buffer;

		f >> buffer;
		strClean(buffer);
		r.endSym = buffer[0];

		f >> buffer;
		strClean(buffer);

		r.move = atoi(buffer.c_str());

		P.push_back(r);
	}

	// Считываем программа

	f.close();

	TuringMachine t(Q, A, P, start, end);

	std::string line;
	std::cin >> line;

	t.DoFeed(line);
	t.Work();

	std::cout << t;
	std::cin >> line;
}