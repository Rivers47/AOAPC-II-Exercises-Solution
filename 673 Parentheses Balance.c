#include <stdio.h>

/*pointer to \0 (EOF) is returned if the string is balanced, otherwise the pointer to the first character that is wrong is returned*/
char* check(char* s)
{
	if (*s == '\0' || *s == ')' || *s == ']')
		return s;

	if (*s == '(')
	{
		char* next = check(s + 1);
		if (*next == ')')
			return check(next + 1);

		return s;
	}
	else if (*s == '[')
	{
		char* next = check(s + 1);
		if (*next == ']')
			return check(next + 1);
		return s;
	}

	/*for non-bracket characters, actually not needed in this question*/
	return check(s + 1);

}


int main()
{
	int n;
	scanf("%d", &n);
	getchar();
	while (n--)
	{
		char str[130];
		gets(str);
		
		if (!*check(str))
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}
