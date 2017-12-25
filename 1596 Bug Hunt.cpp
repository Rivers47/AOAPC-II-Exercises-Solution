#include <iostream>
#include <string>
#include <map>
using namespace std;

enum lineType { assignment, declaration };
lineType getType(string& s, size_t& equal)
{
	if ((equal = s.find('=')) != -1)
	{
		return assignment;
	}
	return declaration;
}

struct arr
{
	//string name;
	int size;
	map<int, int> element;    //first is array index, second is the value it contains

		arr(string& s)
	{
		size_t l = s.find('[');
		size_t r = s.find(']');
		//this->name = s.substr(0,l+1);
		this->size = stoi(s.substr(l + 1, r - l - 1));
	}
	arr()
	{
		size = 0;
	}
	bool assign(int index, int n)
	{
		if (index >= this->size)
			return false;
		this->element[index] = n;
	}
};
map<string, arr> program;

int getExpression(const string& s)
{
	size_t l = s.find('[');
	if (l == -1)
		return stoi(s);
	string name = s.substr(0, l);
	if (s[l + 1] < 48 || s[l + 1] > 57)
	{
		int index = getExpression(s.substr(l + 1, s.size() - l - 2));
		if (index == -1)
			return -1;
		if (program[name].element.count(index))
			return program[name].element[index];
		else
			return -1;
	}
	else    //the last recursion
	{
		size_t r = s.find(']');
		int index = stoi(s.substr(l + 1, r - l - 1));    //current index;
		if (program[name].element.count(index))
			return program[name].element[index];
		else
			return -1;
	}
}

//the LHS doesn't need to be defined previously
void getLHS(const string& line, string& name, int& index)
{
	size_t l = line.find('[');
	name = line.substr(0, l);
	index = getExpression(line.substr(l + 1, line.size() - l - 2));
	if (index >= program[name].size)
		index = -1;
}

void next()
{
	cin.ignore(1000, '.');
	cin.ignore();
}

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);

	while (1)
	{
		program.clear();
		int lineNumber = 1;
		string line;
		while (1)    //every case
		{
			getline(cin, line);
			if (line == ".")
			{
				cout << 0 << "\n";
				getline(cin, line);
				if (line == ".")
					return 0;
				else
				{
					program.clear();
					lineNumber = 1;
				}
			}
			size_t equal = -1;
			//get the type of the line and the position of the equal sign as well
			lineType type = getType(line, equal);

			if (type)    //decleration
			{
				program[line.substr(0, line.find('['))] =
					arr(line);//program.insert(arr(line));
			}
			else    //assignment
			{
				int LHSindex;
				int RHS;
				string name;
				
				getLHS(line.substr(0, equal), name, LHSindex);
				if (LHSindex == -1)
				{
					cout << lineNumber++ << "\n";
					next();
					break;
				}
				
				RHS = getExpression(line.substr(equal + 1, string::npos));
				if (RHS == -1)
				{
					cout << lineNumber++ << "\n";
					next();
					break;
				}
				//if the LHS is good
				program[name].element[LHSindex] = RHS;

			}
			lineNumber++;
		}
	}
	return 0;
}
