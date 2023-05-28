/*
    Do NOT forget to encode your name, section and date of submission.
    
	LASTNAME1, FIRSTNAME1: LIOBING, ALDWIN BENNETT                SECTION: S11A
    LASTNAME2, FIRSTNAME2: TUCO, KEVIN                            SECTION: S11A
    
    DATE SUBMITTED     :
	
	Make sure that you do the following:
	
	1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 02-C5.c -o 02-C5.exe	   
  
   	   where 02 is an example group number and C5 is the Challenge number.
  
  	   You must replace 02 with your own group number!
  
	2. RUN the program's exe file in the command line with input and output (I/O) redirection.
	
	   		Example: CCPROG2> 02-C5 < AMZN.txt > 02-C5-OUTPUT.txt	   

       The text file 02-C5-OUTPUT.txt will contain the actual output of your program.
       
    3. COMPARE your program's output your program with the accompanying C5-EXPECTED.txt file using bbtest.c.
    
	    In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
		Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C5-EXPECTED.txt 02-C5-OUTPUT.TXT > 02-C5-BBTEST.txt
			
		The output file 02-C5-BBTEST.txt contains the results of the comparison.  If you see Differences = 0
		towards the end of the file, then it means that your program's output matches the expected output.
		Otherwise, if you see a Differences value higher than 0, then there's a strong probability that you
		either have a logical error in your program, or you did NOT follow the MP specifications (including
		the directions in this file).
		
		Debug your C source file, and redo the steps above until you get Differences = 0.
		
		Take note, however, that Differences = 0 does NOT necessarily mean that your solutions is 100% logically
		correct.  The bbtest.exe only tests if two files have the same contents.  It is not meant to test the logic
		of your C program.
	
	4. TEST your solution using the stock historical data for other companies other than AMZN.txt.  Note that there
	   are no expected output files provided for other companies.  You'll have to figure out how to verify the 
	   correctness of your program's output on your own. 
*/

#include <stdio.h>
#include <string.h>

#include "test_price.c"  // read and understand the contents of this file

/* Do NOT include other files. */ 


/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. Similar to Challenge #2, you must apply arrays and strings in solving Challenge #5.	
	2. Do NOT use struct data type yet for this particular challenge.
	3. Segregate your program's logic into multiple functions.  Non-compliance will result to a
	   5 point deduction for this Challenge.
	4. Document your codes with SENSIBLE comments.
	5. You are NOT allowed to use library functions that were NOT discussed in our subject.
*/


/* 
	You may #define any constants that you need below this comment.
*/



/*
    You may declare any typedef that you need below this comment.
*/

// StrDate alias is to be used with a string that represents a date
typedef char StrDate[11]; 



/*
    TO DO: Define the functions that you need below this comment.  You are the one responsible in deciding
    what should be the function's 
        a. return data type
        b. name
        c. formal parameters
        d. local variables and statements inside the body.

	You SHOULD write a SENSIBLE comment describing briefly what the function is supposed to accomplish BEFORE
	the function definition itself.
*/
int linear_search(StrDate key, StrDate DATE[], int ROWS)
{
	int x;
	for(x = 0; x < ROWS; x++)
	{		
		if(numeric_date(key) == numeric_date(DATE[x]))
			return x;
	}
	return -1;
		
}
	
int binary_search(StrDate key, StrDate DATE[], int ROWS)
{
	int low = 0, found = 0;
	int high, mid; 
	high = ROWS - 1;
	
	while(!found && low <= high)
	{	
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

void get_input(int ROWS, StrDate DATE[], double OHLC[][4], double VOLUME[])
{
	int x, y;
	for(x = 0; x < ROWS; x++)
	{
		scanf("%s", DATE[x]);
		//printf("%s\t\t", DATE[x]);
		
		for(y = 0; y < 4; y++)
		{
			scanf("%lf", &OHLC[x][y]);
			//printf("%.2f\t\t", OHLC[x][y]);
		}
		scanf("%lf", &VOLUME[x]);
		//printf("%.2f\n", VOLUME[x]);
	}
}
/*
	TO DO: Complete the body of the main() function.
*/
int
main() {
	
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

