#include <stdlib.h>

long int numeric_date(char *str_date) {
   long int day, month, year;     
   char str[11];      
   int i;
   int ctr;
    
   // Step 1: get the month part from the string  
   strcpy(str, str_date);
   i = 0;
   ctr = 0;
   while (str[i] != '/') {  // find the first '/'
       i++;
       ctr++;
   }       
   
   str[i] = '\0';   
   month = atol(str); // capture the month as a long int 
   
   
   // get the day part from the string
   ctr++; // move 1 character past '/'
   strcpy(str, str_date + ctr);
   i = 0;
   while (str[i] != '/') { // find the second '/'
      i++;
      ctr++;
   }  
   
   str[i] = '\0';
   day = atol(str); // capture the day as a long integer       
       
   // get the year part from the string
   ctr++;  // move 1 character past '/'
   strcpy(str, str_date + ctr);  
   year = atol(str);  // capture the year as a long integer      

   return year * 10000 + month * 100 + day;   
}



