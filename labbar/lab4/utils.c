# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>
# include "utils.h"

void clear_input_buffer()
{
  int c;
  do
    {
      c = getchar();   //clear_input_buffer()
    }
  while (c != '\n' && c != EOF);
}

/*
int ask_question_int(char *q)
{
  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", q);
      conversions = scanf("%d", &result);
      clear_input_buffer();
      putchar('\n');
    }
  while(conversions < 1);
  return result;
}
*/

int read_string(char *buf, int buf_siz)
{ 
  int c;
  for (int i = 0; i < (buf_siz - 1); i++)  //In this condition, run the loop.
    {
      c = getchar();                      //Tar char, men läser aschii. hej => [h, e, j] h=65 
      buf[i] = c;                        //buf = [h, e, j] och [i] är index

      if (c == '\n')                     // '\n' radbryt
        {
          buf[i] = '\0';                  // '\0' sista i array
          return i;
        }
    }
  do
    {
      c = getchar();
    }
  while(c != '\n');
  buf[buf_siz-1] = '\0';

  return buf_siz-1;
}

bool is_number(char *str) 
{ int len = strlen(str);
  int i;
  for (i = 0; i < len; i++)
    {
      if (isdigit(str[i]) == false)
                  {
                    return false;
                   }
    }
    return true;
}
/*
void ask_question_string(char *q, char *buf, int buf_siz)
{
  int conversions = 0;
  do
    {
      printf("%s\n", q);
      conversions = read_string(buf, buf_siz);
    }

  while(conversions < 1);  
}
*/

/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_char(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++)
    {
        if (isdigit(str[0]) == false)
        {
            return true;
        }
        
        else if(isdigit(str[i]))
        
    }
    
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
  int buf_siz = 50;
  char buf[buf_siz];
  int read = 0;
  answer_t i;
  while(read < 1)
    {
      printf("%s\n", question);
      read = read_string(buf, buf_siz);
      if (read > 0 && check(buf))
        {
          i = convert(buf);
        }
      else
        read = 0;
    }
  return i;
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).s;
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i; // svaret som ett heltal
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, is_char, (convert_func) strdup).s;
}


