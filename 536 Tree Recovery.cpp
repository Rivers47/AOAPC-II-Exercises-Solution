#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

char lch[256], rch[256];
char inOrder[256], preOrder[256];
char tree[256];

//inOrder[l1...r1] preOrder[l2...r2]
//ABCDEFG DBACEGF
int build(int l1, int r1, int l2, int r2)
{
	if(l1 > r1)
		return 0;

	int root = preOrder[l2];
	int p = l1;
	while(inOrder[p] != root)
		p++;
	int cnt = p-l1;
	lch[root] = build(l1, p-1, l2+1, l2+cnt);
	rch[root] = build(p+1, r1, l2+cnt+1, r2);
	return root;

}

//traverse using postOrder
void postOrder(int root)
{
	if(root == 0)
		return;
	postOrder(lch[root]);
	postOrder(rch[root]);
	cout << (char)root;
	
}

	

int main()
{
	while(1)
	{
		int n = 256;
		memset(preOrder, 0, n);
		
		if(cin >> preOrder); else break;
		cin >> inOrder;
		for(n = 0; ; n++)
		{
			if(preOrder[n] == 0)
				break;
		}
		build(0, n-1, 0, n-1);
		postOrder(preOrder[0]);
		cout << '\n';
		
	}
	return 0;
	


}
