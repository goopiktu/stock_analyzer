#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "company_struct.c"
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

void get_input(C_data *c) {
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

void DCA(C_data c, double fda) {
	int x;
	int start = 0, counter = 0;
	double total_shares_bought = 0, shares_bought = 0, total_buy_amount = 0, PL = 0;
	// shares_bought = fda / c.shd.OHLC[][3];
	for(x = c.rows - 1; x >= 0; x--)
	{
		if(GetMonth(c.shd.date[x]) != GetMonth(c.shd.date[start]))
		{
			shares_bought = fda / c.shd.OHLC[x][3];
			total_shares_bought = total_shares_bought + shares_bought;
			counter++;
			start = x;
			printf("%2d  %s	 %.2lf  %lf  %lf\n", counter, c.shd.date[start], c.shd.OHLC[start][3], shares_bought, total_shares_bought);
		}
	}
	total_buy_amount = counter * fda;
	PL = c.shd.OHLC[0][3] * total_shares_bought - total_buy_amount;
	printf("\n");
    printf("Number of buy transactions = %d\n", counter);
	printf("Total buy amount = %.2lf\n", total_buy_amount);
	printf("Total number of shares bought = %lf\n", total_shares_bought);
	printf("Average price per share = %lf\n", total_buy_amount / total_shares_bought);
	 
	printf("\n");
	printf("Sell date = %s\n", c.shd.date[0]);
	printf("Sell price = %.2lf\n", c.shd.OHLC[0][3]);
	printf("Sell amount = %lf\n", c.shd.OHLC[0][3] * total_shares_bought);
	printf("P/L = %lf\n", PL);
	printf("%%P/L = %lf\n", PL / total_buy_amount * 100);
}

main() {
	C_data stock; // example: stockType stock;
	
	double fda; // this variable stores the value of the Fixed Dollar Amount

	get_input(&stock); 
                                    
	printf("%s\n", stock.Name);      
	printf("%d\n", stock.rows);                                            
    printf("\n");
	
	fda = 100.00;                    
	printf("FDA = %.2lf\n", fda);
	printf("\n");

    DCA(stock, fda); 
								
	return 0;
}


