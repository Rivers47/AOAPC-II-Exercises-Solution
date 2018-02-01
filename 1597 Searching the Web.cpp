#include <algorithm>
#include <iostream>
#include <sstream>
#include <locale>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <iterator>
using namespace std;

/*
the map contains all the occurances of the word in the documents,
the first int of the second value(map) is the number of the document,
the second set is the line numbers that the word occurs.
each vector in documents is a single documents, where each string in the vector
is a single line of that document
*/
vector<vector<string>> documents;	//starts with 0
map <string, map<int, set<int>>> dictonary;	//start with 1...
enum queryType { SINGLE, AND, OR, NOT };

void constructInput(const int& nDocument);
void constructDictonary(string& word,const int& nDocument,const int& nLine);
void preprocessLine(string& line);
//bool preprocessWord(const string& word);
void queryProcess(const string& word);
queryType getQueryType(const string& word, string& a, string& b);
list<int> getNotA(string& A);
void output(const map<int, set<int>>& occ);
void outputWholeDoc(const list<int>& docs);
void notFound();
void setIntersection(const map<int, set<int>>& A, const map<int, set<int>>& B, map<int, set<int>>& result);
void setUnion(const map<int, set<int>>& A, const map<int, set<int>>& B, map<int, set<int>>& result);


void constructInput (const int& n)
{
	for(int i = 1; i <= n; i++)	//for each document
	{
		string line;
		vector<string> document;	//the current document
		for(int nLine = 1;;nLine++)	//ecah line
		{
			getline(cin, line);
			if (line == "**********")
				break;
			document.push_back(line);
			constructDictonary(line, i, nLine);	//put the current line into the dictonary
		}

		documents.push_back(document);	//put it into the cache
	}

}

void constructDictonary(string& line,const int& nDoc,const int& nLine)
{
	preprocessLine(line);
	stringstream ss(line);
	string word;
	while (ss >> word)	
	{
		//if (preprocessWord(word))
			//continue;
		auto& occurance = dictonary[word];
		occurance[nDoc].insert(nLine);
	}
}

//change all the non-alphabetical characters to white space
void preprocessLine(string& s)
{
	for (auto& i : s)
	{
		if (isalpha(i))
		{
			if (isupper(i))
				i = tolower(i);
		}
		else
			i = ' ';
	}
}
/*
bool preprocessWord(const string& word)
{
	//the, a, to, and, or, not
	if (word.size() > 3)
		return false;
	if (word == "the" || word == "a" || word == "to" || word == "and" || word == "or" || word == "not")
		return true;
}
*/
queryType getQueryType(const string& s, string& a, string& b)
{
	stringstream ss(s);
	if (s.find(' ')!=-1)
	{
		if (s[0] == 'N')	//NOT search
		{
			ss.ignore(10,' ');
			ss >> a;
			return NOT;
		}
		ss >> a;
		ss >> b;
		if (b[0] == 'A')
		{
			ss >> b;
			return AND;
		}
		ss >> b;
		return OR;
	}
	return SINGLE;
}



void queryProcess(const string& query)
{
	string a, b;
	queryType type = getQueryType(query,a,b);
	map<int, set<int>> result;

	switch (type)
	{
	case 0:	//single word search
		if (dictonary.count(query))
			output(dictonary[query]);
		else
			notFound();
		break;
	case 1:	//A AND B search
		if(dictonary.count(a) && dictonary.count(b))
			setIntersection(dictonary[a], dictonary[b], result);
		if(!result.empty())
			output(result);
		else
			notFound();
		break;
	case 2:	//A OR B search
		if (dictonary.count(a) && dictonary.count(b))	
		{
			setUnion(dictonary[a], dictonary[b], result);
			output(result);
		}
		else if (dictonary.count(a))
			output(dictonary[a]);
		else if (dictonary.count(b))
			output(dictonary[b]);
		else
			notFound();
		break;
	case 3:	//NOT A search
		outputWholeDoc(getNotA(a));
		break;
	default:break;
	}
	cout << "==========\n";
}

list<int> getNotA(string& A)
{
	list<int> docs;
	int nDoc = documents.size();
	for (int i = 0; i < nDoc; i++)
		docs.push_back(i);
	
	for (auto& i : dictonary[A])
		docs.remove(i.first-1);
	return docs;
}

void outputWholeDoc(const list<int>& docs)
{
	if (docs.empty())
	{
		notFound();
		return;
	}
	int count = 0;
	int size = docs.size()-1;
	for (auto& each : docs)
	{
		if (count == size)
			break;

		for (auto& i : documents[each])	//each line
			cout << i << "\n";
		cout << "----------\n";
		count++;
	}
	for (auto& i : documents[docs.back()])
		cout << i << "\n";
}

void output(const map<int,set<int>>& occ)
{
	for (auto& each : occ)	//pair<int,set<int>>
	{
		for (auto& i : each.second)	//int
			cout << documents[each.first - 1][i - 1] << "\n";
		if (each != (*occ.rbegin()))
			cout << "----------\n";
	}
}

void notFound()
{
	cout << "Sorry, I found nothing.\n";
}

void setIntersection(const map<int, set<int>>& A,const map<int, set<int>>& B, map<int, set<int>>& result)
{
	set<int>a, b;
	for (auto& i : A)
		a.insert(i.first);
	for (auto& i : B)
		b.insert(i.first);
	set<int> c;
	set_intersection(a.begin(), a.end(),
		b.begin(), b.end(),
		inserter(c, c.begin())); 
	//now c has the documents needed
	
	for (auto& each : c)
	{
		set<int> temp;
		set_union(A.at(each).begin(), A.at(each).end(),
			B.at(each).begin(), B.at(each).end(),
			inserter(temp, temp.begin()));
		result[each] = temp;
	}
}

void setUnion(const map<int, set<int>>& A,const map<int, set<int>>& B, map<int, set<int>>& result)
{
	set<int>c;
	for (auto& i : A)
		c.insert(i.first);
	for (auto& i : B)
		c.insert(i.first);

	for (auto& i : c)
	{
		set<int> a, b;
		if (A.count(i))
			a = A.at(i);
		if (B.count(i))
			b = B.at(i);
		set<int> temp;
		set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(temp, temp.begin()));
		result[i] = temp;
	}
}

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	
	int nDocument;
	cin >> nDocument;
	cin.ignore();
	constructInput(nDocument);
	int nQuery;
	cin >> nQuery;
	cin.ignore();
	while (nQuery--)
	{
		string query;
		getline(cin, query);
		queryProcess(query);
	}
	return 0;
}
