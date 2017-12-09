#include <cstdio>
#include <iostream>
using namespace std;



//写一套操作，一共有4*6=24种组合，分别strcmp即可
//rotates the dice so it will produce 24 combinations, and compare them
void rotate(char* str, char d)
{
	
	int i[4];
	switch(d)
	{
	case 'x':
		i[0] = 0;
		i[1] = 4;
		i[2] = 5;
		i[3] = 1;
		break;
	case 'y':
		i[0] = 1;
		i[1] = 2;
		i[2] = 4;
		i[3] = 3;
		break;
	case 'z':
		i[0] = 0;
		i[1] = 3;
		i[2] = 5;
		i[3] = 2;
		break;
	default: break;
	}
	char c = str[i[3]];
	str[i[3]] = str[i[2]];
	str[i[2]] = str[i[1]];
	str[i[1]] = str[i[0]];
	str[i[0]] = c;

}

int strcompare(const char * str1, const char * str2)
{
	for(int i = 0; i < 6; i++)
	{
		if(str1[i] != str2[i])
			return str1[i]-str2[i];
	}
	return 0;

}
bool compare2(char* s1, char* s2, char* cube);
bool compare(char* cube1, char* cube2)
{
		if(compare2(cube1, cube2, cube2))
			return true;
			rotate(cube2,'x');
		if(compare2(cube1, cube2, cube2))
			return true;
			rotate(cube2,'x');
		if(compare2(cube1, cube2, cube2))
			return true;
			rotate(cube2,'x');
		if(compare2(cube1, cube2, cube2))
			return true;
			rotate(cube2,'x');
		//compare2(cube1, cube2, cube2);
			rotate(cube2,'y');
		if(compare2(cube1, cube2, cube2))
			return true;
			rotate(cube2,'y');rotate(cube2,'y');
		if(compare2(cube1, cube2, cube2))
			return true;
		return false;

}

bool compare2(char* s1, char* s2, char* cube)
{
	
	for(int i = 0; i < 4; i++)
	{
		if(!strcompare(s1,s2))
			return true;

		rotate(cube,'z');
	}
	return false;
}


int main()
{
	char cube1[7], cube2[7];
	while(cin.get(cube1,7) && cin.get(cube2,7)) 
	{
		if(compare(cube1, cube2))
			cout <<"TRUE"<<endl;
		else
			cout <<"FALSE"<<endl;
		
		cin.ignore();
	}
	
	
	//system("pause");
	return 0;
}

