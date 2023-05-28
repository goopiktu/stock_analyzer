#include <stdio.h>
#include <string.h>

#include "test_price.h"  
#include "numeric_date.c"

typedef char StrDate[11]; 

int linear_search(StrDate key, StrDate DATE[], int ROWS)
{
	int x;
	for(x = 0; x < ROWS; x++) {		
		if(numeric_date(key) == numeric_date(DATE[x]))
			return x;
	}
	return -1;
		
}
	
int binary_search(StrDate key, StrDate DATE[], int ROWS) {
	int low = 0, found = 0;
	int high, mid; 
	high = ROWS - 1;
	
	while(!found && low <= high) {	
		mid = low + (high - low) / 2;
		if(numeric_date(key) == numeric_date(DATE[mid]))
			found = 1;
		else if(numeric_date(key) > numeric_date(DATE[mid]))
			high = mid - 1;
		else 
			low = mid + 1;
	}
	if(found)
		return mid;
	else 
		return -1;
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
	
	int i;
	int index;
	StrDate key;
	
	StrDate test_cases[7] = { TEST_DATE1, TEST_DATE2, TEST_DATE3, TEST_DATE4, TEST_DATE5, TEST_DATE6, TEST_DATE7 };	

	get_input(ROWS, DATE, OHLC, VOLUME);
	
	printf("%s\n", NAME); 
	
    printf("** TEST-01-LINEAR-SEARCH**\n");
    for (i = 0; i < 7; i++) {
        strcpy(key, test_cases[i]);
		index = linear_search(key, DATE, ROWS);
		printf("%d  %12s %3d ", i + 1, key, index);
	
		if (index != -1) { // found	
			printf(" %8.2f", OHLC[index][3]);
		}		  	
		printf("\n");
	}
	printf("\n");

    printf("** TEST-02-BINARY-SEARCH**\n");
	for (i = 0; i < 7; i++) {
        strcpy(key, test_cases[i]);
        

		index = binary_search(key, DATE, ROWS);
		printf("%d  %12s %3d ", i + 1, key, index);
	
		if (index != -1) { // key was found
			printf(" %8.2f", OHLC[index][3]);
		}		 	
		printf("\n");  	
	}

	return 0;
}

