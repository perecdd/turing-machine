#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>


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

	std::string state;
	char blank; // blank;
	std::vector<std::string> F;

	std::vector<char> A;
	std::vector<rule> P;

	std::vector<char> Feed;
	int workIndex = 0;

	bool Stopped(char a, char b, int move) {
		if (a == b && move == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool DoWork() {
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay before displaying a new state

		system("@cls||clear");

		for (char a : Feed) {
			std::cout << a;
		} // Displaying a string on the screen
		std::cout << std::endl;
		
		for (int i = 0; i < workIndex; i++) {
			std::cout << " ";
		}
		std::cout << "^";

		if (workIndex > (int)(Feed.size() - 1)) {
			Feed.push_back(blank);
		}

		if (workIndex < 0) {
			Feed.push_back(blank);

			for (int i = Feed.size() - 1; i > 0; i--) {
				Feed[i] = Feed[i - 1];
			}
			Feed[0] = blank;

			workIndex++;
		}

		for (rule a : P) {
			if (a.stateStart == state && a.startSym == Feed[workIndex]) {
				if (Stopped(a.startSym, a.endSym, a.move)) {
					return false;
				}

				Feed[workIndex] = a.endSym;
				state = a.stateEnd;
				workIndex += a.move;
				return true;
			}
		}

		std::cout << "Failed to process character: no rule exists.";
		return false;
	}

public:
	friend std::ostream& operator<<(std::ostream& stream, TuringMachine& mach) {
		for (char c : mach.Feed) {
			if (c != mach.blank) {
				stream << c;
			}
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

	TuringMachine(std::vector<std::string>& Q, std::vector<char>& A, char b, std::vector<rule>& P, std::string& start, std::vector<std::string>& F) {
		this->Q = Q;
		this->A = A;
		this->blank = b;
		this->P = P;
		this->state = start;
		this->F = F;
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
	char blank;
	std::vector<std::string> F;

	std::string startStatus;
	std::string endStatus;

	std::string line;
	std::cout << "Please enter the file name with the extension: ";
	std::cin >> name;

	char buffC = ' ';
	int index = 0;

	std::ifstream f(name.c_str());

	if (!f) {
		std::cout << "Couldn't open the file." << std::endl;
		std::cin >> line;
		return 1;
	}

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

	f >> blank;

	f >> start;
	f.get();
	// Init state

	while (f.get() != '\n') {
		f.unget();
		f >> buff;
		F.push_back(buff);
	}
	// Accepting states

	// Programm

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

	// Programm

	f.close();

	TuringMachine t(Q, A, blank, P, start, F);

	std::cout << "Please enter the word to be processed:\n";
	std::cin >> line;

	t.DoFeed(line);
	t.Work();

	system("@cls||clear");
	std::cout << "It was: " << line << std::endl;
	std::cout << "Become: " << t << std::endl;
	std::cin >> line;
}