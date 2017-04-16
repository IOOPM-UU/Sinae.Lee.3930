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

int string_length(char *str)
{
  int count = 0;
  char c;
  do
    {
      c = str[count];
      count = count + 1;
    }
  while (c != '\0');
  return (count - 1);
}


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
 
  for (int i = 0; i < len;)
    {
      if (i == 0 && isdigit(str[0]) == false && isupper(str[0]) && len > 1)
        {
          i++;
        }
      else if (i == 0 && isdigit(str[0]))
        {
          return false;
        }
      else
        {
          if (isdigit(str[i]) == false)
            {
              return false;
            }
          i++;
        }
    }
  return true;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
  int buf_siz = 255;
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

bool is_more_than_20(int length, int index) //next
{
	if (length > 20 && index == 20) {return true;}
	return false;
}

bool is_more_wt_no_remainder(int length, int index) // next & prev
{
	if (length > 20 && index > 20 && index % 20 == 0) {return true;}
	return false;
}

bool is_more_wt_remainder(int length, int index) //prev
{
	if (length > 20 && index > 20 && index % 20 != 0) {return true;}
	return false;
}

bool show_next_page(int length, int index)
{
	bool next1 = is_more_than_20(length, index);
	bool next2 = is_more_wt_no_remainder(length, index);
	
	if (next1 || next2) {return true;}
	return false;
}

bool show_prev_page(int length, int index)
{
	bool prev1 = is_more_wt_remainder(length, index);
	bool prev2 = is_more_wt_no_remainder(length, index);
	
	if (prev1 || prev2) {return true;}
	return false;
}

bool is_answer (char *answer, char *valid_answers)
{
  for (int i = 0; i < strlen(valid_answers); ++i)
    {
      if (answer[0] == valid_answers[i] && strlen(answer) == 1)
        {
          return true;
        }
    }
  
  return false;
}

void print_menu()
{
  printf("\n"
         "======== Main menu ========\n"
	 "[A]dd an item\n"
	 "[E]dit an item (Please choose [L] if you want to edit an item)\n"
	 "[L]ist entire items\n"
	 "[D]isplay a specific item (Please choose [L] if you want to display an item)\n"
         "[U]ndo \n"
	 "[R]emove an item \n"
         "[B]alance tree\n" 
	 "[Q]uit\n"
	 "\n");
}


void print_edit_item_menu()
{
  printf("\n"
         "======== Edit menu ========\n"
         "What do you want to edit?\n"
         "[D]escription\n"
         "[P]rice\n"
         "[S]torage\n"
         "[B]ack\n");
}


void print_list_menu(bool show_next, bool show_prev)
{	
  printf("\n======== List menu ========\n");
  if (show_next) printf("[N]ext page\n");
  
  if (show_prev) printf("[P]revious page\n");
  
  printf("[D]isplay an item\n"
         "[E]dit an item\n"
         "[B]ack to menu\n");
}

char ask_question_menu()
{
  print_menu();
  
  int buf_siz = 8;
  char buf[buf_siz];
  char *valid_answers = "AaLlRrUuBbQq";
  
  do
    {	
      printf("\nWhat do you want to do?   ");
      read_string(buf, buf_siz);
    }
  
  while (!is_answer(buf, valid_answers));
  return toupper(buf[0]);
  
  //return ask_question(question, is_answer, (convert_func) strdup).s;
}


char ask_question_edit_menu(char *question)
{
  print_edit_item_menu();
  
  int buf_siz = 8;
  char buf[buf_siz];
  char *valid_answers = "NnDdPpSsBbUu";
  
  do
    {	
      printf("%s\n", question);
      read_string(buf, buf_siz);
    }

  while (!is_answer(buf, valid_answers));
  return toupper(buf[0]);
}



char ask_question_list_menu(bool show_next, bool show_prev)
{
  print_list_menu(show_next, show_prev);
  int buf_siz = 8;
  char buf[buf_siz];
  char *valid_answers = "NnPpEeDdBb";
  
  do
    {	
      printf("\nWhat do you wish to do?   ");
      read_string(buf, buf_siz);
    }

  while (!is_answer(buf, valid_answers));
  return toupper(buf[0]);
}

void print_yes_or_no()
{
  printf("\n[Y]es or [N]o\n");
}


char ask_question_yes_no(char *question)
{
  print_yes_or_no();
  int buf_siz = 8;
  char buf[buf_siz];
  char *valid_answers = "YyNn";
  
  do
    {	
      printf("%s\n", question);
      read_string(buf, buf_siz);
    }
  
  while (!is_answer(buf, valid_answers));
  return toupper(buf[0]);
}

int what_index(int input, int page)
{
  int index = (page * 20) + input - 1;
  return index;
}

bool is_input_valid(int input, int length)
{
  if (length < 21 && input > 0 && input <= length) {return true;}
  
  if (length > 20 && input > 0 && input < 21) {return true;}
	
  return false;
}


int ask_question_index (char *question, int length,int page)
{
  int input;
  bool valid_input;
  do
    {
      input = ask_question_int(question);
      valid_input = is_input_valid(input, length);
      if (!valid_input) {printf("\n%d is invalid\n", input);}
    }
  while(!valid_input);
  
  int item_index = what_index(input, page);
  return item_index;
}
