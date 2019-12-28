#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <cstring>
//#define printf(...)
using namespace std;

struct cood
{
    char x;
    char y;
};
bool operator==(const cood &a, const cood &b)
{
    return (a.x == b.x) && (a.y == b.y);
}
using state = vector<cood>;

int W, H, N;
char map[16][16];
char proc[16][16]; //1 2 4 8    //processed map, each bit represents a direction, in the order of up, down, left, right
state init, fin;    //initial and final state

void reset()
{
    init.resize(N);
    fin.resize(N);
}

//encode state to a single int
inline int encode(state &s)
{
    int e = 0;
    for (int i = 0; i < N; i++)
    {
        e += ((int)s[i].x << (8 * i)) + ((int)s[i].y << (4 + 8 * i));
    }
    return e;
}

const char mask[] = {15, 1, 2, 4, 8};
const int dx[] = {0, -1, 1, 0, 0}, dy[] = {0, 0, 0, -1, 1};
void generate(state &old, vector<state> &l, state &s, int count);

//check if two robots occupy the same cood or switched cood
//a b are old positions, c d are new positions repectively
inline bool collision(cood& a, cood& b, cood& c, cood& d)   
{
    if (c == d)
        return true;
    if (a == d && b == c)
        return true;

    return false;
}

//generate preceeding states, store the results in l
void newstates(state &old, vector<state> &l)
{
    state s(N);
    generate(old, l, s, N - 1);
}

/*  generate preceeding states recurcively 
    for each genrated state, it is filled backwards */
void generate(state &old, vector<state> &l, state &s, int count)
{
    if (count == 0) //base case
    {
        for (int i = 0; i <= 4; i++)
        {
            if (mask[i] & proc[old[count].x][old[count].y])
            {
                s[count].x = old[count].x + dx[i];
                s[count].y = old[count].y + dy[i];
            }
            else
                continue;
            if (N > 1)
                if (collision(old[0], old[1], s[0], s[1]))
                    continue;
            if (N > 2)
                if (collision(old[0], old[2], s[0], s[2]) || collision(old[1], old[2], s[1], s[2]))
                    continue;
            if (s == old)
                continue;

            l.push_back(s);
        }
        return;
    }

    for (int i = 0; i <= 4; i++)
    {
        if (mask[i] & proc[old[count].x][old[count].y])
        {
            s[count].x = old[count].x + dx[i];
            s[count].y = old[count].y + dy[i];
        }
        else
            continue;

        generate(old, l, s, count - 1);
    }
}

//standard BFS algorithm
int BFS()
{
    queue<pair<state, int>> Q;
    int step = 0;
    Q.push({init, step});
    //set<int> vis;
    vector<bool> vis(2<<24);
    vis[encode(init)] = true;
    while (!Q.empty())
    {
        pair<state, int> s = Q.front();
        Q.pop();
        if (s.first == fin)
            return s.second;

        step = s.second + 1;
        vector<state> lst;
        newstates(s.first, lst);
        for (state &each : lst)
        {
            if (vis[encode(each)])
                continue;
            vis[encode(each)] = true;
            Q.push({each, step});
        }
    }
    return -1;  //this should never happen, since the question gurantees the existence of solution
}

void encodeDirections(int &x, int &y)
{
    proc[x][y] = 0;
    for (int i = 1; i <= 4; i++)
    {
        if (map[x + dx[i]][y + dy[i]] == ' ')
            proc[x][y] += mask[i];
    }
}
void printMap();
int main()
{
    //cin.tie(0);cin.sync_with_stdio(0);
    while (1)
    {
        cin >> W >> H >> N;
        if (!(W || H || N))
            break;
        reset();
        cin.ignore();
        for (int x = 0; x < H; x++)
        {
            for (int y = 0; y < W; y++)
            {
                char c;
                c = getchar();
                switch (c)
                {
                case '#':
                    map[x][y] = '#';
                    break;
                case ' ':
                    map[x][y] = ' ';
                    break;
                case 'a':
                    map[x][y] = ' ';
                    init[0].x = x;
                    init[0].y = y;
                    break;
                case 'b':
                    map[x][y] = ' ';
                    init[1].x = x;
                    init[1].y = y;
                    break;
                case 'c':
                    map[x][y] = ' ';
                    init[2].x = x;
                    init[2].y = y;
                    break;
                case 'A':
                    map[x][y] = ' ';
                    fin[0].x = x;
                    fin[0].y = y;
                    break;
                case 'B':
                    map[x][y] = ' ';
                    fin[1].x = x;
                    fin[1].y = y;
                    break;
                case 'C':
                    map[x][y] = ' ';
                    fin[2].x = x;
                    fin[2].y = y;
                    break;
                default:
                    break;
                }
            }
            cin.ignore();
        }

        for (int x = 0; x < H; x++)
            for (int y = 0; y < W; y++)
                switch (map[x][y])
                {
                case '#':
                    //map[x][y] = 0;
                    break;
                default:
                    encodeDirections(x, y);
                    break;
                }
        //printMap();
        cout << BFS() << endl;
    }
    return 0;
}


void printMap()
{
    for(int x = 0; x < H; x++)
    {
        for(int y = 0; y < W; y++)
        {
            cout << map[x][y];
        }
        cout << '\n';
    }
for(int x = 0; x < H; x++)
    {
        for(int y = 0; y < W; y++)
        {
            cout << '\'' << (int)proc[x][y] << '\'';
        }
        cout << '\n';
    }
}
