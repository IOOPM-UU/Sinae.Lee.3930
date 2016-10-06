# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include "utils.h"
# include "list.h"
# include "tree.h"
# include "item.h"



//typedef struct action action_t;



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

list_t *extract_storage(tree_t *db)
{
  list_t *list_of_storage = list_node_data(db);
  if (db == NULL)
    {
      printf("The database is empty\n");
      return NULL;
    }

  else
    return list_of_storage;
}

list_t *extract_shelves(tree_t *db)
{
  list_t *list_of_shelves = list_node_shelf(db);
  return list_of_shelves;
}

bool is_shelf_taken(tree_t *db, char *shelf)
{
  char *temp;
  list_t *shelf_list = extract_shelves(db);
  int length = list_length(shelf_list);

  for (int i = 0; i < length; i++)
    {
      temp = list_get(shelf_list, i);
      if (strcmp(temp, shelf) == 0)
        {
          printf("%s is already taken\n", shelf);
          return true;
        }
    }
  
  return false;
}

/*
//shelf som är upptagen för varan
char *answer_to_shelf_question(tree_t *db, char *name, char *shelf_question)
{
  char *shelf_input = ask_question_shelf(shelf_question);

  if (is_shelf_taken_by_item(db, name, shelf_input) == true)
    {
      printf("%s is taken by %s\n", shelf_input, name);
      shelf_input = ask_question_shelf(shelf_question);
    }
  return shelf_input;
}
*/

int sublist_items(tree_t *db, int i) //prints out the keys, in-order
{
	printf("\n========= List of items ========\n");
	list_t *keys = tree_keys(db);
	int length = list_length(keys);
	int count = 0; // kanske inte behövs, kanske räcker med i % 20
	
	if (length == 0)
	{
		printf("\nThe tree is empty\n");
		return 0;
	}
	
	for (; i < length && count < 20; ++i, ++count)
	{
		char *key = list_get(keys, i);
		printf("%d.\t%s\n", i % 20 + 1, key);
	}
	//printf("i is %d\n",i);
	if (length < 20)
	{
		char *answer = ask_question_string("\n[E]dit an item\n"
										   "[B]ack to menu\n");
		if (answer[0] == 'E' || answer[0] == 'e')
		{
			printf("Edit item\n");
		}
		if (answer[0] == 'B' || answer[0] == 'b')
		{
			return 0;
		}
	}
	
	if (length > 20 && i == 20) //there's 21 items or more
	{
		char *answer = ask_question_string("\n[N]ext page\n"
										   "[E]dit an item\n"
										   "[B]ack to menu\n");
		if (answer[0] == 'N' || answer[0] == 'n')
		{
			sublist_items(db,i);
		}
		if (answer[0] == 'E' || answer[0] == 'e')
		{
			printf("Edit item\n");
		}
		if (answer[0] == 'B' || answer[0] == 'b')
		{
			return 0;
		}
	}
	if (length > 20 && i > 20 && i % 20 == 0)
	{
		printf("i is %d", i);
		char *answer = ask_question_string("\n[N]ext page\n"
								   "[P]revious page\n"
								   "[E]dit an item\n"
								   "[B]ack to menu\n");
		if( answer[0] == 'N' || answer[0] == 'n')
		{
			sublist_items(db,i);
		}
		if (answer[0] == 'P' || answer[0] == 'p')
		{
			sublist_items(db, i-40);
		}
		if (answer[0] == 'E' || answer[0] == 'e')
		{
			printf("Edit item 2\n");
		}
		if (answer[0] == 'B' || answer[0] == 'b')
		{
			return 0;
		}
	}
	if (length > 20 && i % 20 != 0)
	{
		printf("i is %d\n",i);
		printf("mod 20 is %d\n", i % 20);
		printf("i - i mod 20 is %d\n", i - (i%20));
		char *answer = ask_question_string("\n[P]revious page\n"
										   "[E]dit an item\n"
										   "[B]ack to menu\n");
		if (answer[0] == 'P' || answer[0] == 'p')
		{
			sublist_items(db,i - (i%20)-20);
		}
		if (answer[0] == 'E' || answer[0] == 'e')
		{
			printf("Edit item 3\n");
		}
		if (answer[0] == 'B' || answer[0] == 'b')
		{
			return 0;
		}
	}
	return 0;
}

void list_items(tree_t *db)
{
	int db_size = tree_size(db);
	if (db_size == 0)
	{
		printf("The database is empty\n");
	}
	
	if(db_size > 0)
	{
		sublist_items(db, 0);
	}
}




/*

bool is_shelf_taken(tree_t *db, item_t *item)
{
  char *name_in;
  list_t *list_of_item = tree_keys(db); //list of item
  int length = list_length(list_of_item);
  for (int i = 0; i < length; ++i)
    {
      name_in = list_get(list_of_item, i);
      char *input_name = item->name;

      if(strcmp(input_name, name_in) == 0)
        {
          printf("%s is taken\n", item->shelf_control->shelf_nr);
          return true;
        }
    }
  
  return false;
}
*/

/*
void add_goods(tree_t *db)
{
  printf("----------------------");
  printf("\n    Add an item\n");
  printf("----------------------\n");

  char *name = ask_question_string("Name: \n");
  // char *shelf_input = ask_question_shelf("Shelf nr: \n");
  bool exist = is_item_in_db(db, name);
  // bool taken = is_shelf_taken(db, shelf_input);
  if (exist == false)
    {
      char *shelf_input = ask_question_shelf("Shelf nr: \n");
      if(shelf_input == );
      char *description = ask_question_string("Description: \n");
      int price = ask_question_int("Price: \n");
      int amount = ask_question_int("Amount: \n");

      item_t *item = item_on_shelf(name, description, price, shelf_input, amount);

      print_item(item);
      
      char *answer_to_choice = ask_question_string("Do you want add the item?\n"
                                                   "[Y]es\n"
                                                   "[N]o\n"
                                                   "[E]dit\n");
      if (answer_to_choice[0] == 'Y' || answer_to_choice[0] == 'y')
        {
          tree_insert2(db, name, item);
          // ask_menu
        }
      
      if (answer_to_choice[0] == 'N' || answer_to_choice[0] == 'n')
        {
          free(item);
          //ask_menu
        }
      
      
      //  if (answer_to_choice[0] == 'E' || answer_to_choice[0] == 'e')
       // {
       // edit_item();
       // ask_menu;
       // }
      
    }
  
  //if item already exist in db 
  else
    {
      
    }
}
*/


void display_goods(tree_t *db);


int main()
{
  tree_t *db = tree_new();
  /*
  storage_t *st1 = make_storage("A23", 5);
  storage_t *st2 = make_storage("D10", 1);
  storage_t *st3 = make_storage("B23", 2);
  storage_t *st4 = make_storage("C23", 1);
  storage_t *st5 = make_storage("F23", 3);

  tree_insert(db, "apple", st1);
  tree_insert(db, "honey", st2);
  tree_insert(db, "cola", st3);
  tree_insert(db, "cow", st4);
  tree_insert(db, "pig", st5);
  */

  item_t *item1 = item_on_shelf("apple", "red", 4550, "A23", 2);
  item_t *item2 = item_on_shelf("bulle", "sugar high", 5550, "B21", 1);
  item_t *item3 = item_on_shelf("cat", "fluffy", 3000, "C21", 1);
  item_t *item4 = item_on_shelf("pig", "pinky", 2457, "D21", 3);
  item_t *item5 = item_on_shelf("cow", "moo", 3120, "K21", 4);
  item_t *item6 = item_on_shelf("bird", "tiny", 3120, "L21", 4);

  item_t *item7 = item_on_shelf("cola", "fizzy", 4550, "E23", 2);
  item_t *item8 = item_on_shelf("wolf", "animal", 5550, "T21", 1);
  item_t *item9 = item_on_shelf("dog", "voff", 3000, "M21", 1);
  item_t *item10 = item_on_shelf("hallon", "sour", 2457, "P21", 3);
  item_t *item11 = item_on_shelf("zebra", "sabanah", 3120, "G21", 4);
  item_t *item12 = item_on_shelf("sparv", "bird", 3120, "W21", 4);
  
  
  tree_insert(db, "apple", item1);
  tree_insert(db, "bulle", item2);
  tree_insert(db, "cat", item3);
  tree_insert(db, "pig", item4);
  tree_insert(db, "cow", item5);
  tree_insert(db, "bird", item6);
  tree_insert(db, "cola", item7);
  tree_insert(db, "wolf", item8);
  tree_insert(db, "dog", item9);
  tree_insert(db, "hallon", item10);
  tree_insert(db, "zebra", item11);
  tree_insert(db, "sparv", item12);
  
  

  int t_size = tree_size(db);
  printf("tree size is %d\n", t_size);
  

  

  bool exist1 = is_shelf_taken(db, "W21");
  printf("%d \n", exist1);

  bool exist2 = is_shelf_taken(db, "C21");
  printf("%d \n", exist2);

  bool exist3 = is_shelf_taken(db, "B21");
  printf("%d \n", exist3);

  bool exist4 = is_shelf_taken(db, "K21");
  printf("%d \n", exist4);

  bool exist5 = is_shelf_taken(db, "L21");
  printf("%d \n", exist5);

  
  
  list_t *l = extract_shelves(db);
  
  int l_length = list_length(l);
  printf("%d\n", l_length);

 
  
  print_list(l);
}
