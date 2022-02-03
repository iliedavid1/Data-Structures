#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
	int x;
	int y;
	int r;
} cerc;

int distance(int x1, int y1, int x2, int y2)
{
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int chck_inter(int r1, int r2, int distance)
{
	int r_distance = (r1 + r2) * (r1 + r2);
	if (distance > r_distance)
		return 0;
	if (distance < (r1 - r2) * (r1 - r2))
		return 1;
	return 1;

}

int main()
{
	int n;
	int i, j;
	cerc *arr;

	scanf("%d", &n);

	arr = (cerc *)malloc(n * sizeof(cerc));

	for (i = 0; i < n; i++) {
		int x1, y1, r1;
		scanf("%d %d %d", &x1, &y1, &r1);
		arr[i].x = x1;
		arr[i].y = y1;
		arr[i].r = r1;
	}

	int nr = 0;

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			int dist = distance(arr[i].x, arr[i].y, arr[j].x, arr[j].y);
			if (chck_inter(arr[i].r, arr[j].r, dist) == 1)
				nr++;
		}
	}

	printf("%d\n", nr);

	free(arr);

    return 0;
}
