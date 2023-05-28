#ifndef C6_DEFINED 
    
   #define C6_DEFINED  (1)


#define MAX_ROWS 1000

typedef char StrDate[11]; 
typedef char StrStock[6];

struct shd{
	StrDate date[MAX_ROWS];  /* to store the date */
	double OHLC[MAX_ROWS][4]; /* to store the Open, High, Low, and Close values */
	double volume[MAX_ROWS]; /*  to store the volume */
};

typedef struct shd SHD;

struct c_data{   /* (c = company) */
	StrStock Name;
	int rows;
	SHD shd;
};

typedef struct c_data C_data;
   
#endif
