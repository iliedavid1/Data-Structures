#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stack.h"

int main(void)
{
	stack_t *stack = st_create(sizeof(char));
	int nr_para;
	/*para1 pentru paranteze normale, para2 pentru paranteze patrate
	**para3 pentru acolade
	*/
	int para1 = 0, para2 = 0, para3 = 0;
	scanf("%d\n", &nr_para);
	char para;
	for (int i = 0; i < nr_para; i++) {
		scanf("%c", &para);
		st_push(stack, &para);
	}
	while (st_is_empty(stack) == 0) {
		/* adaugam 1 la variabilele paranteze daca aceasta este
		** inchisa pentru ca noi verificam incepand cu ultimul 
		** element pe care il adaugam in stack (am stat ceva sa ma prind de asta)
		*/
		if (*(char *)st_peek(stack) == ')')
			para1++;
		if (*(char *)st_peek(stack) == '(')
			para1--;
		if (*(char *)st_peek(stack) == ']')
			para2++;
		if (*(char *)st_peek(stack) == '[')
			para2--;
		if (*(char *)st_peek(stack) == '}')
			para3++;
		if (*(char *)st_peek(stack) == '{')
			para3--;
		st_pop(stack);
		
		if (para1 < 0 || para2 < 0 || para3 < 0) {
			printf("Nu e bun1\n");
			return 0;
		}
	}

	if (para1 > 0 || para2 > 0 || para3 > 0) {
		printf("Nu e bun\n");
		return 0;
	}

	printf("E bun\n");
	return 0;
}