#include <cstdio>
#include <queue>
using namespace std;


int outSequence(int n, queue<int>& cards)
{
	for (int i = 0; i < n - 1; i++)
	{
		if(i+1<n-1)
			printf("%d, ", cards.front());
		else
			printf("%d\n", cards.front());
		cards.pop();
		cards.push(cards.front());
		cards.pop();
	}
	return cards.front();
}

void iniQueue(queue<int>& cards,int n)
{
	for (int i = 1; i <= n; i++)
	{
		cards.push(i);
	}
}

int main()
{
	while(true)
	{
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;
		else if (n == 1)
		{
			printf("Discarded cards:\nRemaining card: 1\n");
			continue;
		}
		queue<int> cards;
		iniQueue(cards, n);
		printf("Discarded cards: ");
		n = outSequence(n, cards);
		
		printf("Remaining card: %d\n", n);

	}
}
