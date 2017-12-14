#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

map<string, int> wordID;
set<string> compoundWords;

void isCompound(const string& s)
{
	for (int i = 1; i < s.size(); i++)
	{
		if (wordID.count(s.substr(0, i)))
			if (wordID.count(s.substr(i, string::npos)))
				compoundWords.insert(s);
	}
}

int main()
{
	string s;
	int n = 0;
	while (getline(cin, s))
		wordID[s] = n++;
	for (auto& s : wordID)
		isCompound(s.first);

	for (auto& s : compoundWords)
		cout << s << "\n";
	return 0;
}
