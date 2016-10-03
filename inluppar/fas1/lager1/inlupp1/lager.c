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

//typedef struct action action_t;

struct item    
{
  char *name;
  char *description;
  int price;
  shelf_t *shelf_control;
};

struct shelf
{
  char *shelf_nr; 
  int amount;
};

shelf_t *make_shelf(char *shelf_nr, int amount)
{
  shelf_t *shelf = calloc(1, sizeof(shelf_t));
  if (shelf == NULL)
    {
      printf("The shelf is NULL\n");
      return NULL;
    }

  else
    {
      shelf->shelf_nr = shelf_nr;
      shelf->amount = amount;
    }
  return shelf;
}

char *get_shelf_nr(shelf_t *shelf)
{
  return shelf->shelf_nr;
}

int get_amount(shelf_t *shelf)
{
  return shelf->amount;
}

// without shelf specification
item_t *make_item(char *name, char *desc, int price, shelf_t *shelf)
{
  item_t *item = calloc(1, sizeof(item_t));
  if (item != NULL)
    {
      item->name = name;
      item->description = desc;
      item->price = price;
      item->shelf_control = shelf;
    }
  return item;
}

// with shelf location
item_t *item_on_shelf(char *name, char *desc, int price, char *shelf_nr, int amount)
{
  shelf_t *shelf = make_shelf(shelf_nr, amount);
  return make_item(name, desc, price, shelf);
}

item_t *input_item()
{
  char *name, *desc;
  int price;
  char *shelf_nr;
  int amount;

  name = ask_question_string("Enter the product name?\n");
  
  desc = ask_question_string("Describe the product\n");
  
  price = ask_question_int("Enter the price?\n");
  
  shelf_nr = ask_question_shelf("Enter the shelf nr.\n");

  amount = ask_question_int("Enter the amount\n");

  item_t *item = item_on_shelf(name, desc, price, shelf_nr, amount);
  return item;
  
}

void print_item(item_t *item)
{
  int q, r; //qutient, remainder
  q = (item->price)/100;
  r = (item->price)%100;
  char *name = item->name;
  char *description = item->description;
  shelf_t *shelf = item->shelf_control;
  char *shelf_nr = get_shelf_nr(shelf);
  int amount = get_amount(shelf);

  printf("Name: %s\n"
         "Description: %s\n"
         "Price: %d.%d kr\n"
         "Shelf: %s\n"
         "Amount: %d\n",
         name, description, q, r, shelf_nr, amount);
}

void print_menu()
{
  printf("\n[A]-Add a new item\n"
         "[R]-Remove an item\n"
         "[E]-Edit an item\n"
         "[U]-Undo\n"
         "[D]-Display an item\n"
         "[P]-Print list\n"
         "[Q]-Quit\n");

}

bool is_answer_edit_item (char *answer)
{
  char *valid_capital_answers = "NDPSA";
  char *valid_lowercase_answers = "ndpsa";
  
  for (int i = 0; i < strlen(valid_capital_answers); ++i)
    {
      if (answer[0] == valid_capital_answers[i] && strlen(answer) == 1)
        {
          return true;
        }
      if (answer[0] == valid_lowercase_answers[i] && strlen(answer) == 1)
        {
          return true;
        }
    }
  
  return false;
}

bool is_item_in_db(tree_t *db, char *name) // name som vi matar in  
{
  return is_key_in_tree(db, name);
}

bool is_shelf_taken(tree_t *db, char *name, char *shelf)
{
  return is_data_in_tree(db, name, shelf);
}

char *answer_to_shelf_question(tree_t *db, char *name, char *shelf_question)
{
  char *shelf_input = ask_question_shelf(shelf_question);

  if (is_shelf_taken(db, name, shelf_input) == true)
    {
      printf("%s is taken by %s\n", shelf_input, name);
      shelf_input = ask_question_shelf(shelf_question);
    }
  return shelf_input;
}

/*
void add_goods(tree_t *db)
{
  char *name = ask_question_string("Name:");
  if (is_item_in_db(db, name) == true)
    {
      printf("%s already exist.\n", name);
      char *shelf_nr = answer_to_shelf_question(db, name, "Shelf nr: ");
      int amount = ask_question_int("Amount:");
      
    }

  else if(is_item_in_db(db, name) == false && is_shelf_taken(db, name, 
    {
      char *description = ask_question_string("Description:");
      int price = ask_question_int("Price:");
      
      
    }
      
}
*/

void display_goods(tree_t *db, int i);

int main()
  {
    printf("Welcome to warehouse management 1.0\n ====================================\n");
    print_menu();
    tree_t *db = tree_new();
    shelf_t *s1 = make_shelf("A23", 4);
    shelf_t *s2 = make_shelf("A24", 5);
    shelf_t *s3 = make_shelf("A35", 6);
    //item_t *i1 = item_on_shelf("honey", "bee", 2459, "A23", 4);
    tree_t *db1;
    db1 = tree_insert2(db, "apple", s1);

    tree_t *db2;
    db2 = tree_insert2(db1, "chocola", s2);

    tree_t *db3;
    db3 = tree_insert2(db2, "kola", s3);
    
    
     int size = tree_size(db3);
    printf("%d\n", size);
    
    bool finns;
    finns = is_item_in_db(db3, "kola");
    printf("%d\n", finns);


    bool shelf;
    shelf = is_shelf_taken(db3, "kola", "A35");
    printf("%d\n", shelf);

    item_t *goods = item_on_shelf("apple", "red, crisp fruit", 4556, "A23", 6);

    print_item(goods);

    
  }
