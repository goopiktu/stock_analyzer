#include <stdio.h>
#include <string.h>

typedef char StrDate[11]; 

// To get minimun
int find_min(double OHLC[][4], int ROWS) {
	int x;
	int min_index = 0;
	for(x = 0; x < ROWS; x++) {
		if(OHLC[x][2] < OHLC[min_index][2]) {
			min_index = x;	 
		}
	}
	return min_index;
}

// To get maximum
int find_max(double OHLC[][4], int ROWS) {
	int x;
	int max_index = 0;
	for(x = 0; x < ROWS; x++) {
		if(OHLC[x][1] > OHLC[max_index][1]) {
			max_index = x;
		}
	}
	return max_index;
}

void get_input(int ROWS, StrDate DATE[], double OHLC[][4], double VOLUME[]) {
	int x, y;
	for(x = 0; x < ROWS; x++) {
		scanf("%s", DATE[x]);
		//printf("%s\t\t", DATE[x]);
		
		for(y = 0; y < 4; y++) {
			scanf("%lf", &OHLC[x][y]);
			//printf("%.2f\t\t", OHLC[x][y]);
		}
		scanf("%lf", &VOLUME[x]);
		//printf("%.2f\n", VOLUME[x]);
	}
}

int main() {
	
	int ROWS;
	StrDate NAME;
	scanf("%s %d", NAME, &ROWS);
	double OHLC[ROWS][4];
	StrDate DATE[ROWS];
	double VOLUME[ROWS];

	int min_index;
	int max_index;
	
	get_input(ROWS, DATE, OHLC, VOLUME);
		
    min_index = find_min(OHLC,ROWS);
	max_index = find_max(OHLC,ROWS);
	    
	printf("%s\n", NAME);   
	
    printf("%d %s %.2f\n", min_index, DATE[min_index], OHLC[min_index][2]);

	printf("%d %s %.2f\n", max_index, DATE[max_index], OHLC[max_index][1]);
    	
	return 0;
}
