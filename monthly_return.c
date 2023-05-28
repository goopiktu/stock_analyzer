#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "company_struct.h"
#include "numeric_date.c"  

int GetYear(StrDate date) {
	return atol(date+6);
}

int GetMonth(StrDate date) {
	char temp[3] = "";
	temp[0] = date[0];  
	temp[1] = date[1];	
	return atol(temp);
}

int GetDay(StrDate date) {
	char temp[3] = "";
	temp[0] = date[3];	
	temp[1] = date[4];	
	return atol(temp);
}

/* (r = rows)(d = date)(o = OHLC)(v = volume)*/
void get_input(C_data *c)
{
	int x, y;
	scanf("%s", c->Name);
	scanf("%d", &c->rows);
	for(x = 0; x < c->rows; x++)
	{
		scanf("%s", c->shd.date[x]);
		for(y = 0; y < 4; y++)
		{
			scanf("%lf", &c->shd.OHLC[x][y]);
		}
		scanf("%lf", &c->shd.volume[x]); 
	}
}



void comp_monthly_return(C_data c)
{
	int x, counter;
	int start, end;
	double PL, PPL;
	start = c.rows - 1;
	counter = 0;
	PL = 0;
	PPL = 0;

	for(x = c.rows - 1; x >= 0; x--)
	{
		if(GetMonth(c.shd.date[x]) != GetMonth(c.shd.date[start]) || x == 0)
		{
			end = x + 1;
			if(x == 0)
			{
				end = 0;
			}
			counter++;
			PL = c.shd.OHLC[end][3] - c.shd.OHLC[start][3];
			PPL = PL/c.shd.OHLC[start][3] * 100;
			printf("%2d  %s  %.2lf  %s  %.2lf %8.2lf %11lf\n", counter, c.shd.date[start], c.shd.OHLC[start][3], c.shd.date[end], c.shd.OHLC[end][3], PL, PPL);
			start = x;
		}
	}	
}

int
main() {	
	C_data stock; 
	

	get_input(&stock); 
	
	printf("%s\n", stock.Name);      
	printf("%d\n", stock.rows);                                       
    printf("\n");
	
	
    comp_monthly_return(stock); 

	return 0;
}