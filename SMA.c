#include <stdio.h>
#include <string.h>

#include "time_interval.h"  

#define MAX 1000

typedef char StrDate[11]; 

int find_sma(int m, StrDate DateSMA[], double SMA[],int ROWS, double OHLC[][4], StrDate DATE[]) {
	int x, y;
	int count = 0;
	double average = 0;
	
	for(x = ROWS - m; x >= 0; x--) {
		average = 0;
		for(y = 0; y < m; y++) {
			average += OHLC[x + y][3];
		}
		SMA[count] = average / m;
		strcpy(DateSMA[count], DATE[x]);
		count++;
	}
	return count;
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
	StrDate NAME;
	int ROWS;
	StrDate DATE[MAX];
	scanf("%s %d", NAME, &ROWS);
	double OHLC[ROWS][4];
	double VOLUME[MAX];
	int i, j, m;
	int count;
	StrDate DateSMA[MAX];  // 1D array of dates with corresponding SMA values
	double SMA[MAX];	   // 1D array of SMA values 
	
	int test_cases[3] = { TEST_NDAYS1, TEST_NDAYS2, TEST_NDAYS3 };  
	    
	get_input(ROWS, DATE, OHLC, VOLUME);

	printf("%s\n", NAME);  
	
    for (i = 0; i < 3; i++) {  // for each test case
    	m = test_cases[i];     // m is the number of prices that are averaged
		printf("**TEST-%d-day-SMA**\n", m);
		
		count = find_sma(m, DateSMA, SMA, ROWS, OHLC, DATE); 
	
	
		printf("count = %d\n", count);	
		for (j = 0; j < count; j++)
			printf("%3d  %s  %.2lf\n", j + 1, DateSMA[j], SMA[j]);
	
		printf("\n");
    	
	}
    
	return 0;
}