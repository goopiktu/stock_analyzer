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

void PortPerformance(StrFile file, StrDate RefDate){
    FILE *fp,*fp2;
    Port File[MAX];
    int i=0;
    //Open both the input and output file
    if((fp = fopen(file,"r")) == NULL){
        fprintf(stderr, "ERROR: %s does not exist.\n",file);
    }else{
        StrFile FileOut;
        strcpy(FileOut,"15-");
        strcat(FileOut,file);
        fp2 = fopen(FileOut,"a");
        //Add the first line of the output file
        fprintf(fp2, "PORTFOLIO PERFORMANCE AS OF %s\n\n",RefDate);
        while(fscanf(fp,"%s %lf %s",File[i].name,
                                                 &File[i].shares,
                                                 File[i].shareDate)==3)
                                                 {//Scans the input file one row at a time
            FindPerformance(fp2, File[i].name, File[i].shareDate, RefDate,
            File[i].shares);
        }
        fclose(fp);
        fclose(fp2);
    }
}
//Calculates all the values needed for the output one row of portfolio performance
void FindPerformance(FILE *fp2, StrStock StockName, StrDate ShareDate, StrDateRefDate, double shares) {
    FILE *fp;
    stoD Stock;
    int i;
    double rdprice,sdprice;
    //Finds the stock data that the shares were bought from
    StrFile FileStock;
    strcpy(FileStock,"SHD/");
    strcat(FileStock, StockName);
    strcat(FileStock, ".txt");
    //Opens and scans the stock data
    fp = fopen(FileStock,"r");
    fscanf(fp,"%s", Stock.name);
    fscanf(fp,"%d", &Stock.row);
    for (i = 0; i < Stock.row; i++) {
        fscanf(fp, "%s %lf %lf %lf %lf %lf", Stock.Stor[i].Date,
                                                                &Stock.Stor[i].Open,
                                                                &Stock.Stor[i].High,
                                                                &Stock.Stor[i].Low,
                                                                &Stock.Stor[i].Close,
                                                                &Stock.Stor[i].Volume);
    }

    rdprice = Stock.Stor[BinarySearch(RefDate, &Stock)].Close;
    sdprice = Stock.Stor[BinarySearch(ShareDate, &Stock)].Close;
    PrintPerformance(fp2, rdprice, sdprice, Stock.name, shares, ShareDate);
    fclose(fp);
}
//Prints one row of portfolio performance
void PrintPerformance(FILE *fp, double rdprice, double sdprice, StrStock StockName, double shares, StrDate buyDate) {
    double PL,PPL;
    PL = rdprice-sdprice;
    PPL = PL/sdprice*100;
    fprintf(fp,"%-7s %11lf %s %13lf %13lf %13lf %13lf\n",StockName, shares, buyDate, sdprice, rdprice, PL, PPL);
}

int BinarySearch(StrDate date_key, stoD *ptr_stock) {//Finds and returns the index of the key date
    int low = 0, found = 0;
    int high, mid;
    high = ptr_stock->row - 1;
    while(!found && low <= high) {
        mid = low + (high - low) / 2;
        if(numeric_date(date_key) == numeric_date(ptr_stock->Stor[mid].Date))
            found = 1;
        else if(numeric_date(date_key) > numeric_date(ptr_stock->Stor[mid].Date))
            high = mid - 1;
        else
            low = mid + 1;
    }
    if(found)
        return mid;
    else
        return 0;
}

int main() {
    char portfolio_filename[100];
    char reference_date[11];

    PortPerformance("PORTFOLIO.txt", "10/29/2021");

    printf("Input the name of your test portfolio file: ");
    scanf("%s", portfolio_filename); 


    printf("Input a reference date in MM/DD/YYYY format: ");
    scanf("%s", reference_date);

    PortPerformance(portfolio_filename, reference_date);
    return 0;
}