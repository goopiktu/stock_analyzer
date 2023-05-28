#include<stdio.h>
#include<string.h>

typedef char str[11];
int find_min(double OHLC[][4], int ROWS) {
	int x;
	int min_index = 0;
	// To get minimun
	for(x = 0; x < ROWS; x++) {
		if(OHLC[x][2] < OHLC[min_index][2]) {
			min_index = x;
		}
	}
	return min_index;
}

int find_max(double OHLC[][4], int ROWS) {
	int x;
	int max_index = 0;
	// To get maximum
	for(x = 0; x < ROWS; x++) {
		if(OHLC[x][1] > OHLC[max_index][1]) {
			max_index = x;
		}
	}
	return max_index;
}

int main() {
	int min, max;
	int x, y, ROWS;
	str NAME;
	scanf("%s %d", NAME, &ROWS);
	double OHLC[ROWS][4];
	str DATE[ROWS];
	double VOLUME[ROWS];
	printf("%s\n", NAME);

	for(x = 0; x < ROWS; x++) {
		scanf("%s", DATE[x]);
		for(y = 0; y < 4; y++) {
			scanf("%lf", &OHLC[x][y]);
		}
		scanf("%lf", &VOLUME[x]);
	}

	min = find_min(OHLC,ROWS);
	printf("%d %s %.2f\n", min, DATE[min], OHLC[min][2]);
	max = find_max(OHLC,ROWS);
	printf("%d %s %.2f\n", max, DATE[max], OHLC[max][1]);
	
	return 0;
}