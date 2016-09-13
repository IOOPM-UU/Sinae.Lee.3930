# include <stdio.h>
# include <string.h>
# include <stdio.h>
#include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>
# include "utils.h"
# include <time.h>

// gcc -std=c11 -Wall utils.c guess.c

int main(void)    //funkar även med int argc, char *argv[]
{
  int tries;
  srand (time(NULL));
  int n = rand() % 20;                  
  int g;                                //guess
  char *name;
 
  name = ask_question_string("Skriv in ditt namn:\n");
  printf("Du %s, jag tänker på ett tal ... kan du gissa vilket?\n", name);
  g = ask_question_int("");
  
  for(tries = 1; tries <= 15; tries++)
    {

      if (g == n)
        {
          printf("Bingo!\n");
          printf("Det tog %s %d gissningar att komma fram till %d\n", name, tries, n);
          return 0;
        }
      
      else if (g > n)
        {
          g = ask_question_int("För stort!");
          
        }

      else
        {
          g = ask_question_int("För litet!");
        }
      
    }

 
  printf("Nu har du slut på gissningar! Jag tänkte på %d!\n", n);
    
  return 0;
}
      
