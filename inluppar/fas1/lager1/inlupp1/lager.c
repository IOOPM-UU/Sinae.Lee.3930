# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include "utils.h"
# include "list.h"
# include "tree.h"

typedef struct item item_t;

typedef struct shelf shelf_t;

typedef struct action action_t;

struct item    // tree
{
  char *name;
  char *description;
  int price;
  list_t *shelf_check;   //shelf
  list_t *amount_check;   //amount
};


struct shelf
{
  char *shelf_id;    // hyllnummer
  int amount;
};

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } TYPE;
  item_t *added;    //add
  item_t *edited;    // edit
  item_t *original;   //edit
  item_t *removed;
  bool exist;
};


void check_shelf(list_t *shelf_check)  // printa ut  hyllnummer
{
  int i;
  int length = list_length(shelf_check);
  shelf_t *shelf;

  for(i = 0; i < length; i++)
    {
      shelf = list_get(shelf_check, i);
      printf("Shelf %s\n", shelf->shelf_id); 
    }
}
void check_amount(list_t *amount_check) //printa ut amount
{
  int i;
  int length = list_length(amount_check);
  shelf_t *amount;

  for(i = 0, i < length; i++)
    {
      amount = list_get(amount_check, i);
      printf("Amount %d\n", amount->amount);
    }
  
}
                 
bool check_exist(); // tree_t *db, char *shelf

item_t *input_item(tree_t *db)
{
  char *name, *desc, *shelf;
  int price;
  item_t *item = get_tree_key(db);
  bool exist = check_exist();
  list_t *shelf_control;
  //item_t *item =  en funktion som gräver  tree_get

  if (item == NULL)
    {
      name = ask_question_string("Enter the product name?\n");
      desc = ask_question_string("Describe the product\n");
      price = ask_question_int("Enter the price?\n");
      // shelf = ask_question_shelf("Enter the shelf nr.\n");
    }
  
}

void add_item(tree_t *db, action_t *action)
{
  
}

void print_item(item_t *item)
{
  int heltal = (item->price)/100;
  int decimal = (item->price)%100;
  char *name = item->name;
  char *desc = item->description;
  list_t *shelf_control = item->shelf_control;  

  printf("\n Name: %s\n", name);
  printf("Desc: %s\n", desc);
  printf("Price: %d.%d\n", heltal, decimal);
  // printf("Shelf: %s\n", shelf);
  //printf("Amount: %d\n", amount);

  
  
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

char *ask_question_shelf(char *question)
{
  return ask_question(question, is_char, (convert_func) strdup).s;
}

void print_menu()
{
  printf("\n");
  printf(" [A]dd an item\n");
  printf(" [E]dit an item\n");
  printf(" [L]ist entire items\n");
  printf(" [D]isplay a specific item\n");
  printf(" [R]emove an item\n");
  printf(" [U]ndo\n");
  printf(" [Q]uit\n");
  printf("\n");
}


char ask_question_menu()
{
  char *key = "AaEeLlDdRrUuQq";
  int i = 0;   // index till key
  char *answer;  
  int check = 0; //signal till loop
  char ch;
  
  print_menu();

  while (check == 0)  
    {
      answer = ask_question_string("Enter the key!\n");
      if (strlen(answer) == 1)
        {
          for (i = 0; i < strlen(key); i++)
            {
              if(answer[0] == key[i])
                {
                  ch = toupper(answer[0]);
                  check = 1;  // slutar loppa när det är ett rätt svar
                }
            }
        }
    }
  return ch;
}

void edit_item(tree_t *db, action_t *action);
void list_items(tree_t *db, action_t *action);
void display_item(tree_t *db, action_t *action);
void undo(action_t *action);
void remove_item();

void event_loop(tree_t *db, action_t *action)
{
  char meny_key;
  do
    {
      meny_key = ask_question_menu();
      if(meny_key == 'A' || meny_key == 'a')
        {
          add_item(db, action);
        }
      else if(meny_key == 'E' || meny_key == 'e')
        {
          edit_item(db, action);
        }
      else if(meny_key == 'L' || meny_key == 'l')
        {
          list_items(db, action);  //list_db
        }
      else if(meny_key == 'D' || meny_key == 'd')
        {
          display_item(db, action);
        }
      else if(meny_key == 'U' || meny_key == 'u')
        {
          undo(action);
        }
      else if(meny_key == 'R' || meny_key == 'r')
        {
          printf("Not implemented\n");
        }
    }
  while(meny_key != 'Q');  // quit program, exit
}


int main()
{
  printf("Inventory management 1.0\n ================================\n\n");
  tree_t *data_base = tree(new);
  
