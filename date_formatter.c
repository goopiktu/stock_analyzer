#include<stdio.h>
#include<string.h>

typedef char str[11];

void Date_format(str DATE) {

	int x;
	if(DATE[2] != '/') {
		for(x = 10; x >= 0 ; x--) {
			DATE[x + 1] = DATE[x];
		}
		DATE[0] = '0';
	}

	if(DATE[5] != '/') {
		for(x = 10; x > 2 ; x--) {
			DATE[x + 1] = DATE[x];
		}
		DATE[3] = '0';
	}

	if(strlen(DATE) < 10) {
		DATE[8] = DATE[6];
		DATE[9] = DATE[7];
		DATE[6] = '2';
		DATE[7] = '0';
	}
}

int main() {
	int x, y, ROWS;
	str NAME;
	scanf("%s %d", NAME, &ROWS);
	
	double OHLC[ROWS][4];
	str DATE[ROWS];
	double VOLUME[ROWS];
	
	printf("%s %d\n", NAME, ROWS);
	for(x = 0; x < ROWS; x++) {
		scanf("%s", DATE[x]);
		Date_format(DATE[x]);
		printf("%s\t\t", DATE[x]);
			for(y = 0; y < 4; y++) {
				scanf("%lf", &OHLC[x][y]);
				printf("%.2f\t\t", OHLC[x][y]);
			}
		scanf("%lf", &VOLUME[x]);
		printf("%.2f\n", VOLUME[x]);
	}
	//printf("%s", DATE[0]);
	return 0;
}