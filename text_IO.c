#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "company_struct.h"
#include "numeric_date.c"  

int GetYear(char *date) {
	return atol(date+6);
}

int GetMonth(char *date) {
	char temp[3] = "";
	
	temp[0] = date[0];  
	temp[1] = date[1];	
	return atol(temp);
}

int GetDay(char *date) {
	char temp[3] = "";
	
	temp[0] = date[3];	
	temp[1] = date[4];	
	return atol(temp);
}


void get_month(StrDate c, char* new_date) {
	char months[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

	strcpy(new_date,c+6);
	strcat(new_date,"-");
	strcat(new_date,months[GetMonth(c)-1]);
	strcat(new_date,"-");
	new_date[9] = c[3];
	new_date[10] = c[4];
}


void file_read(char* symbol, C_data* c) {
	FILE *fp;
	int x;
	fp = fopen(symbol, "r");
	fscanf(fp,"%s %d\n\n",c->Name,&c->rows);
	for (x = 0; x < c->rows; x++)
	{
		fscanf(fp,"%s",c->shd.date[x]);
		fscanf(fp,"%lf %lf %lf %lf",&c->shd.OHLC[x][0], &c->shd.OHLC[x][1], &c->shd.OHLC[x][2], &c->shd.OHLC[x][3]);
		fscanf(fp,"%lf",&c->shd.volume[x]);
	}
	fclose(fp);
}

void file_write(char* symbol, C_data c)
{
	FILE *fp;
	char new_date[12];
	int x;
	fp = fopen(symbol, "w");
	fprintf(fp,"%s %d\n\n",c.Name,c.rows);
	for (x = 0; x < c.rows; x++)
	{
		get_month(c.shd.date[x], new_date);
		fprintf(fp,"%s ",new_date);
		fprintf(fp,"%.2lf %.2lf %.2lf %.2lf",c.shd.OHLC[x][0], c.shd.OHLC[x][1], c.shd.OHLC[x][2], c.shd.OHLC[x][3]);
		fprintf(fp,"%.2lf\n",c.shd.volume[x]);
	}
	fclose(fp);
}

void chal(char* symbol)
{
	
	FILE *fp;
	C_data c;
	char new_file_input[100];
	char new_file_output[100];

	strcpy(new_file_input, "");
	strcat(new_file_input, symbol);
	strcat(new_file_input, ".txt");

	strcpy(new_file_output, "");
	strcat(new_file_output, symbol);
	strcat(new_file_output, ".txt");


	fp = fopen(new_file_input, "r");
	if(fp == NULL)
	{
		printf("ERROR: %s does not exist.\n", symbol);
		return;
	}
	else
	{
		file_read(new_file_input, &c);
		file_write(new_file_output, c);
	}
	fclose(fp);

}

int main() {
	char symbol[8];


	chal("AMZN");

	chal("XYZ");  

	printf("Input the stock symbol: ");
	scanf("%s", symbol);  

	chal(symbol); 

	return 0;
}