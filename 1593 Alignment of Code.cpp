#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;


struct strline
{
	vector<string> words;
	int nword = 0;
} l[1001];

bool comparenword( strline& a,  strline& b)
{
	return a.nword < b.nword;
}

int width[100];

int main()
{
	string a;
	
	int index = 0;
	while (getline(cin, a))
	{
		stringstream currentLine(a);
		while(currentLine >> a)
			l[index].words.push_back(a);
		l[index].nword = l[index].words.size();
		index++;
	}
	
	//calculate the width
	const int max_nwords = (*max_element(l, l+index, comparenword)).nword;
	for (int s = 0; s < max_nwords; s++)	//for each vertical column
	{
		int w = 0;
		for (int k = 0; k < index; k++)		//for each line
		{
			int currentLength = 0;
			try
			{
				currentLength = l[k].words.at(s).length();
			}
			catch (const std::out_of_range& e) { }
			if(w < currentLength)
				w = currentLength;
		}
		width[s] = w;
	}
	
	//print the code
	for (int i = 0; i < index; i++)
	{
		for (int k = 0; k < l[i].words.size(); k++)
		{
			printf("%s", l[i].words[k].c_str());
			if (!(k+1 == l[i].words.size()))
				printf("%*s", width[k] + 1 - l[i].words[k].size(), "");
		}
		printf("\n");
	}
}

