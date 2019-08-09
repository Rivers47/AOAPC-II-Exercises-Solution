#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <list>
#include <cassert>
#define NDEBUG
#ifdef NDEBUG
#define printf(...)
#endif

using namespace std;

queue<char> deck;    //holds at most 52 elements
list<list<char>> piles{7};  //each pile is a list, easy for add/remove
int count = 0;

//how to test repeat states? fast slow pointer
struct state
{
    queue<char> q;
    list<list<char> > p;
    const bool operator == (const state& a)
    {
        if( this->q == a.q 
         && this->p == a.p)
            return true;
        return false;
    }
    const bool operator != (const state& a)
    {
        return !(*this==a);
    }
};
vector<state> S;
void printPile(list<char>& pile)
{
    for(auto it = pile.begin(); it != pile.end(); it++)
    {
        printf("%d ",*it);
    }
    printf("\n");
}

void pap(int index = -1)
{
    printf("deck: \n");
    if (index == -1)
    {
        queue<char> q(deck);
        while (!q.empty())
        {
            printf("%d ", q.front());
            q.pop();
        }
        printf("\n");
        int i = 1;
        printf("card %d:\n", count + 1);
        for (auto it = piles.begin(); it != piles.end(); it++)
        {   
            printf("pile %d: ", i++);
            printPile(*it);
        }
    }
    else
    {
        queue<char> q(S[index].q);
        while (!q.empty())
        {
            printf("%d ", q.front());
            q.pop();
        }
        printf("\n");
        int i = 1;
        printf("card %d:\n", count + 1);
        for (auto it = S[index].p.begin(); it != S[index].p.end(); it++)
        {
            printf("pile %d: ", i++);
            printPile(*it);
        }
    }
    printf("\n");
}

void input()
{
    while(!deck.empty()) deck.pop();
    piles.clear();
    piles.resize(7);
    S.clear();
    count = 0;
    
    for(int i = 0,n; i < 52; i++)
    {
        //cout << i << flush;
        scanf("%d",&n);
        deck.push((char)n);
    }
}

bool check(list<char>& pile)
{
    if(pile.size() < 3) return false;
    auto b1 = pile.begin(), b2 = b1;
    b2++;
    auto e1 = pile.rbegin(), e2 = e1, e3 = ++e2;
    e3++;

    if((*b1 + *b2 + *e1) % 10 == 0)
    { 
        deck.push(*b1); deck.push(*b2); deck.push(*e1);
        pile.erase(b1); pile.erase(b2); pile.pop_back();
    }
    else if((*b1 + *e1 + *e2) % 10 == 0)
    {
        deck.push(*b1); deck.push(*e2); deck.push(*e1);
        pile.erase(b1); pile.pop_back(); pile.pop_back();
    }
    else if((*e1 + *e2 + *e3) % 10 == 0)
    {
        deck.push(*e3); deck.push(*e2); deck.push(*e1);
        pile.pop_back();pile.pop_back();pile.pop_back();
    }
    else 
        return false;
    return true;
}

//deal a card, remove cards if applicable, set the iterator to the next pile
void deal(list<list<char>>::iterator& pile, int step = 1)
{
    //auto pile = piles.begin();
    while(step--)
    {
        (*pile).push_back(deck.front());
        deck.pop();
        #ifndef NDEBUG
        pap();
        #endif
        while(check(*pile));

        if((*pile).size() == 0)    
            pile = piles.erase(pile);
        else
            pile++;
        if(pile == piles.end())
            pile = piles.begin();
        
        assert(piles.empty() || pile != piles.end());
    }

}

//-1 win, 0 lose, >0 draw
int play()
{
    input();
    auto pile = piles.begin();
    int i = 0;  //single step
    while(1)
    {
        deal(pile); count++;
        S.push_back({deck,piles});  //you don't need to store every state, but it's easier to debug
        assert(S.size() == count);
        //pap();
        if(piles.empty())  return -1;
        if(deck.empty()) return 0;
        if(count%2 == 0)
        {
            printf("%d %d\n",i,count);
            if(S[i++] == S[count-1])
                return i;
        }
    }
}

int isLoop()
{
    int fast,slow;
    fast = slow = 0;
    while(fast < S.size()-1)
    {
        slow++;
        fast+=2;
        printf("%d %d\n",slow,fast);
        if(S[fast] == S[slow])
            break;
    }
    if(fast >= S.size()-1) return 0;
    fast = 0;
    while(S[slow] != S[fast])
    {
        fast++;
        slow++;
    }
    printf("fast: %d\n",fast);
    return fast;
}

int main()
{
    //cin.tie(0);cin.sync_with_stdio(0);
    while (cin.peek() != '0')
    {
        int result = play();
        switch(result)
        {
            case 0: cout << "Loss: " << count << '\n'; break;
            case -1: cout << "Win : " << count << '\n'; break;
            default: cout << "Draw: " << result+1 << '\n'; break;
        }
        cin.ignore(10, '\n');
    }

    return 0;
}
