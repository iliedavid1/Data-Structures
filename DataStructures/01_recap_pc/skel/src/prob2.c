#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void)
{
	int n, m;
	int i, j;
	
	char line1[MAX];
	fgets(line1, MAX, stdin);
	sscanf(line1, "%d %d", &n, &m);
	
	char **arr;
	arr = (char **)malloc(n * sizeof(char *));
	for (i = 0; i < n; i++) {
		arr[i] = (char *)malloc(m * sizeof(char));
	}

	for (i = 0; i < n; i++) {
		char line[MAX];
		fgets(line, MAX, stdin);
		char *token = strtok(line, " \n");
		arr[i][0] = token[0];
		for (j = 1; j < m; j++) {
			token = strtok(NULL, " \n");
			arr[i][j] = token[0];
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (arr[i][j] == 'B') {
				arr[i][j] = 'X';
				for (int k = 0; k < n; k++) {
					if (arr[k][j] == 'B')
						continue;
					arr[k][j] = 'X';
				}

				for (int k = 0; k < m; k++) {
					if (arr[i][k] == 'B')
						continue;
					arr[i][k] = 'X';
				}
			}
		}
	}

	int ok = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (arr[i][j] == 'E') {
				ok = 1;
				printf("Exista inamici\n");
				return 1;
			}
		}
	}

	printf("Nu exista inamici\n");

	for (i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
	return 0;
}