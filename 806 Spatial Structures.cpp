
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define TEST
using namespace std;
#define uint unsigned int
const int MAX = 64 + 4;

char G[MAX][MAX] = {};  //set to all 0
int size;
void resetG()
{
    memset(G,0,sizeof(G));
}

void showbits(unsigned int x)
{
    for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
        putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

//convert a base 10 number to base 5 string
//in this situation it should only have 1, 2, 3, 4
//every 3 bits a digit, 0 is used to indicate no more route
//the result order is reversed, the root branch is at the highest poistion
int toBase5(int n)
{
    int result = 0;
    while (n > 0)
    {
        result = result * 5 + n%5;
        n /= 5;
    }
    
    return result;
}



void paint(int n, int length)
{
    int x = 0, y = 0; //upper left corner
    while(n>0)
    {
        length /= 2;
        switch(n%5)
        {
            case 1: break;
            case 2: y+=length; break;
            case 3: x+=length; break;
            case 4: x+=length; y+=length; break;
            default: printf("error in print"); return;
        }
        n /= 5;
    }
    //printf("%d %d %d",x,y,length);
    //actually set the grid;
    for(int i = x; i < x+length; i++)
    {
        for(int j = y; j < y+length; j++)
        {
            G[i][j] = '*';
        }
    }
}

bool isSolid(int length, int x, int y)
{

    for(int i = x; i < x+length; i++)
    {
        for(int j = y; j < y + length; j++)
        {
            if(G[i][j] == '0')
                return false;
        }
    }
    return true;
}

void pathToImage()
{
    resetG();
    while (1)
    {
        int n;
        cin >> n;
        if (n == -1)
            break;
        paint(n, size);
    }

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            putchar(G[x][y] == '*' ? '*' : '.');
        }
        putchar('\n');
    }
    cout << '\n';
}

vector<int> paths; //WHAT IS TH EMAXIMUM NUMBER OF ROUTES FOR A IMAGE OF N*N? 
int nBlackNodes;
//divide into four quadrant, see if it's pure color
//path in base 10
//the result is not sorted
void getColour(int length, int path = 0, int x = 0, int y = 0, int depth = 0)
{
    if (isSolid(length, x, y))
    {
        paths.push_back(path);
        nBlackNodes += length*length;
        return;
    }
   
    if (length == 1)
        return;
 
    length /= 2;
    getColour(length, path + pow(5,depth), x, y,depth+1);
    getColour(length, path + pow(5,depth) * 2, x, y + length,depth+1);
    getColour(length, path + pow(5,depth) * 3, x + length, y,depth+1);
    getColour(length, path + pow(5,depth) * 4, x + length, y + length,depth+1);

    return;
}


void imageToPath(int &length)
{
    nBlackNodes = 0;
    paths.clear();
    getColour(length);
    
    sort(paths.begin(),paths.end());
    for(int i = 0; i < paths.size();i++)
    {
        
        cout << paths[i];
        if( (i+1) % 12 == 0 || i == paths.size()-1) cout << '\n';
        else cout << ' ';
    }
    //if(paths.size()%12!=0)cout << '\n';
    cout << "Total number of black nodes = " << paths.size();
    cout << "\n\n";
    
}




int main()
{
    int count=1;
    while(1)
    {
        cin >> size;
        if (size < 0)
        {
            size = ~size + 1; //get the positive number
            

            cout << "Image " << count++ << '\n';
            pathToImage();
        }
        else if (size > 0)  //image to string
        {
            for (int x = 0; x < size; x++)
            {
                cin >> G[x];
            }
            cout << "Image " << count++ << '\n';

            imageToPath(size);
          
        }
        else 
        {
            break;
        }
    }
    
    return 0;
}
