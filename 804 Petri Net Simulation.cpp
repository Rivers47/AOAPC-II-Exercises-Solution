#include <iostream>
#include <vector>
#include <map>
#include <bitset>
using namespace std;

int NP, NT, NF;

vector<int> P; //places and number of tokens in them

//a single transition
struct t
{

    map<int, int> input, output;
    
    bool isActive()
    {
        for (auto &i : input)
        {
            if (P[i.first] < i.second)
                return false;
        }
        return true;
    }
    bool fire()
    {
        if (isActive())
        {
            for (auto &i : input)
                P[i.first] -= i.second;
            for (auto &i : output)
                P[i.first] += i.second;
            return true;
        }
        return false;
    }
};
vector<t> T;

void simulate(int &kase)
{
    int cycle = NF;
    bool fired = false;

    //repeatedly fire all the transitions
    while (NF)
    {
        fired = false;
        for (int i = 0; i < NT; i++) //for each transition
        {
            while (NF && T[i].fire()) //keep fire the transition as long as possible
            {
                fired = true;
                --NF;
            }
        }
        if (!fired) //if no transition is fired for a whole period
            break;
    }

    cout << "Case " << kase << ": ";
    if (NF > 0)
        cout << "dead after " << cycle - NF << " transitions\n";
    else
        cout << "still live after " << cycle << " transitions\n";
    cout << "Places with tokens:";
    for (int i = 1; i <= NP; ++i)
    {
        if (P[i])
            cout << " " << i << " (" << P[i] << ")";
    }
    cout << "\n\n";
}

int main()
{
    //cin.tie(0);cin.sync_with_stdio(0);
    int kase = 1;
    while (1)
    {
        cin >> NP;
        if (NP == 0)
            return 0;

        P.resize(NP + 1);
        for (int i = 1; i <= NP; ++i)
            cin >> P[i];
        cin >> NT;

        T.clear();
        T.resize(NT);

        //input transitions
        for (int i = 0; i < NT; ++i)
        {
            for (int t;;)
            {
                cin >> t;
                if (t < 0) //could be faster since all input comes before ouputs
                    T[i].input[-t]++;
                else if (t > 0)
                    T[i].output[t]++;
                else //each line ends with 0
                    break;
            }
        }

        cin >> NF;
        simulate(kase);
        kase++;
    }

    return 0;
}
