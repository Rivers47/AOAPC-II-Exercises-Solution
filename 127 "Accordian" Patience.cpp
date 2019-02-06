#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <utility>
#include <cassert>
//#define TEST
using namespace std;

//<face, suit>
#define card pair<char, char>
#define deck list<stack<card>>

bool operator==(card a, card b)
{
	if (a.second == b.second || a.first == b.first)
		return true;
	return false;
}

#ifdef TEST
const void printDeck(deck &d)
{
	for (auto &i : d)
		cout << i.top().first << i.top().second << ' ';
	cout << '\n';
}
#endif

void simulate(deck &D)
{
	auto it = D.begin();
	auto it1 = it;
	auto it3 = it;

	for (int i = 0; it != D.end();)
	{
		//the first two times the card can only be moved on to the left
		//this loop is kind of hardcode
		for (; i < 2; i++)
		{
			it1 = it;
			it++;
			//so that it1 = it - 1

			if ((*it).top() == (*it1).top())
			{
				//move the card
				(*it1).push((*it).top());
				(*it).pop();
				if ((*it).empty())
					D.erase(it);

				it = D.begin();
				i = 0;

#ifdef TEST
				printDeck(D);
#endif
				continue;
			}
			if(it == D.end())
				return;
		}

		it1 = it3 = it;
		it++;
		advance(it3, -2); //it already ++ed, so only -2 not -3 for it3

		if ((*it).top() == (*it3).top())
		{
			(*it3).push((*it).top());
			(*it).pop();
			if ((*it).empty())
				D.erase(it);

			//if a move is made, the whole loop has to start over
			it = D.begin();
			i = 0; //reset i if
#ifdef TEST
			printDeck(D);
#endif
			continue;
		}

		if ((*it).top() == (*it1).top())
		{
			//move the card
			(*it1).push((*it).top());
			(*it).pop();
			if ((*it).empty())
				D.erase(it);

			it = D.begin();
			i = 0;
#ifdef TEST
			printDeck(D);
#endif
			continue;
		}
	}

	return;
}

int main()
{
	cin.tie(0);cin.sync_with_stdio(0);

	while (1)
	{
		deck d;
		int count = 52;
		while (count--)
		{
			string s;
			cin >> s;
			if (s[0] == '#')
				return 0;
			card c = card(s[0],s[1]);
			stack<card> t;
			t.push(c);
			d.push_back(t); //put this card into the list, why is deque used???
		}
		simulate(d);
		if(d.size() > 1)
			cout << d.size() << " piles remaining:";
		else
			cout << d.size() << " pile remaining:";
		
		for (auto &i : d)
			cout << ' ' << i.size();
		cout << '\n';
	}
	return 0;
}
