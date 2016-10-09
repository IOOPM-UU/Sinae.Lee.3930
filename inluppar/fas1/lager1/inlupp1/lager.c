# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include "utils.h"
# include "list.h"
# include "tree.h"
# include "item.h"



typedef struct action action_t;

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } TYPE;
  item_t *added;    //add
  item_t *edited;    // edit
  item_t *old;   //edit
  //item_t *removed;
  list_t *origin_list;
  bool exist;
};

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

char *answer_to_shelf_question(tree_t *db) 
{
  char *input = ask_question_shelf("Enter the shelf:");

  while (is_shelf_taken(db, input) == true)
    {
      printf("Please enter another shelf\n");
      free(input);
      input =  ask_question_shelf("Enter the shelf:");
    }

  return input;
}

//visar innehållet av item
void *item_spec(tree_t *db, char *name)
{
  return search_data_in_tree(db, name);
}




bool aux_list_items(tree_t *db, int index) //prints out the keys, in-order
{
	printf("\n========= List of items ========\n");
	
	list_t *keys = tree_keys(db);
	int length = list_length(keys);
	bool show_next;// = show_next_page(length, index);
	bool show_prev;// = show_prev_page(length, index);
	int count = 0; // kanske inte behövs, kanske räcker med index % 20
	int prev_i = index;
       
	if (length == 0)
	{
		printf("\nThe tree is empty\n");
		return false;
	}
	
	for (; index < length && count < 20; ++index) // byta ut count < 20 mot index % 20 < 20
	{
		char *key = list_get(keys, index);
		printf("%d.\t%s\n", index % 20 + 1, key);
		++count;
	}
	printf("\nItem's index from %d to %d\n", prev_i, index-1);
	
	show_next = show_next_page(length, index);
	show_prev = show_prev_page(length, index);
	
	if (length <= 20)
	{
          char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'E')
		{
			printf("Edit item\n");
			return true;
		}
		if (answer == 'D')
		{
                  printf("\n"
                         "Display item\n");
                  
                  int index_nr = ask_question_int("\n"
                                                  "Please enter the item number\n");
                  int item_nr = index_nr - 1;

                  char *item_name = strdup((char *)list_get(keys, item_nr));

                  void *item_show = item_spec(db, item_name);
                  print_item(item_show);
                  
                  
                  return true; //eller false för att återgå till list?
		}
		if (answer == 'B')
		{
			return false;
		}
		printf("\nInvalid input 1\n");
		aux_list_items(db,index - (index % 20));
		return true;
	}
	
	if (length > 20 && index == 20) //there's 21 items or more
	{
		char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'N')
		{
                  aux_list_items(db,index);
                          
                  return true;
		}
		if (answer == 'E')
		{
			printf("Edit item\n");
			return true;
		}
                
		if (answer == 'D'&& answer != 'N')
		{
                  printf("Display item\n");

                  int index_nr = ask_question_int("\n"
                                                  "Please enter the item number\n");
                  int item_nr = index_nr -1;

                  char *item_name = strdup((char *)list_get(keys, item_nr));

                  void *item_show = item_spec(db, item_name);
                  print_item(item_show);
                  
                  return true; // eller false
		}

		if (answer == 'B')
		{
			return false;
		}
		printf("\nInvalid input 2\n");
		aux_list_items(db, index - 20);
		return true;
	}
	
	if (length > 20 && index > 20 && index % 20 == 0)
	{

		char answer = ask_question_list_menu(show_next, show_prev);
		if( answer == 'N')
		{
			aux_list_items(db,index);
			return true;
		}
		if (answer == 'P')
		{
			aux_list_items(db, index-40);
			return true;
		}
		if (answer == 'E')
		{
			printf("Edit item 2\n");
			return true;
		}
		if (answer == 'D')
		{
                  printf("Display item\n");
                        
                  return true; //eller false
		}
		if (answer == 'B')
		{
			return false;
		}
		printf("\nInvalid input 3\n");
		aux_list_items(db, index - 20);
		return true;
	}
	
	if (length > 20 && index > 20 && index % 20 != 0)
	{

		char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'P')
		{
			aux_list_items(db,index - (index%20)-20);
			return true;
		}
		if (answer == 'E')
		{
			printf("Edit item 3\n");
			return true;
		}
		if (answer == 'D')
		{
			printf("Display item\n");
                        
                        int index_nr = ask_question_int("\n"
                                                        "Please enter the item number\n");
                        int item_nr = index_nr+20-1 ;

                        char *item_name = strdup((char *)list_get(keys, item_nr));
                        void *item_show = item_spec(db, item_name);
                        print_item(item_show);
                  
			return true; //eller false
		}
		if (answer == 'B')
		{
			return false;
		}
		printf("\nInvalid input 4\n");
		aux_list_items(db,index - (index%20));
		return true;
	}
	
	if (aux_list_items(db, index)) // if true
	{
		return true;
	}
	return false;
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
		aux_list_items(db, 0);
	}
}


void add_goods(tree_t *db)
{
  printf("----------------------");
  printf("\n    Add an item\n");
  printf("----------------------\n");

  char *name = ask_question_string("Enter a name: \n");
  char *shelf_input = ask_question_shelf("Enter shelf nr: \n");

  bool name_exist = is_item_in_db(db, name);
  bool shelf_exist = is_shelf_taken(db, shelf_input);
  
  if (name_exist == false && shelf_exist == false)
    {
      char *description = ask_question_string("Description: \n");
      int price= ask_question_int("Price: \n");
      int amount = ask_question_int("Amount: \n");

      item_t *item = item_on_shelf(name, description, price, shelf_input, amount);
      print_item(item);
      
      char *answer_to_choice = ask_question_string("Do you want add the item?\n"
                                                   "[Y]es\n"
                                                   "[N]o\n"
                                                   "[E]dit\n");
      if (answer_to_choice[0] == 'Y' || answer_to_choice[0] == 'y')
        {
          tree_insert(db, name, item);
          //event_loop
        }
      
      if (answer_to_choice[0] == 'N' || answer_to_choice[0] == 'n')
        {
          free(item);
          //event_loop
        }

      //  if (answer_to_choice[0] == 'E' || answer_to_choice[0] == 'e')
      // edit_item();
      // event_loop()  
    }
  //if item already exist in db men inte på "shelf_input"
  if(name_exist == true && shelf_exist == false)
    {
      printf("%s already exsits. Please read the following information about the item.\n", name);
      print_item(item_spec(db, name));
      char *answer = ask_question_string("Do you want to put the item on the same shelf?\n"
                                         "[Y]\n"
                                         "[N]o\n");
      if (answer[0] == 'Y' || answer[0] == 'y')
        {
          void *item = item_spec(db, name);
          increase_item_amount(item);
          print_item(item);
          char *answer_to_choice = ask_question_string("Do you want add the item?\n"
                                                       "[Y]es\n"
                                                       "[N]o\n"
                                                       "[E]dit\n");
          
        

          if (answer_to_choice[0] == 'Y' || answer_to_choice[0] == 'y')
            {
              tree_insert(db, name, item);
              //event_loop
            }

          if (answer_to_choice[0] == 'N' || answer_to_choice[0] == 'n')
            {
              free(item);
              //event_loop
            }

          //if (answer_to_choice[0] == 'E' || answer_to_choice[0] == 'e')
          // edit_item();
        }

      if (answer[0] == 'N' || answer[0] == 'n')
        {
          char *description = ask_question_string("Description: \n");
          int price = ask_question_int("Price: \n");
          int amount = ask_question_int("Amount: \n");
          
          item_t *item = item_on_shelf(name, description, price, shelf_input, amount);
          print_item(item);
          
          char *answer = ask_question_string("Do you want add the item?\n"
                                             "[Y]es\n"
                                             "[N]o\n"
                                             "[E]dit\n");
          if (answer[0] == 'Y' || answer[0] == 'y')
            {
              tree_insert(db, name, item);
              //event_loop
            }
          
          if (answer[0] == 'N' || answer[0] == 'n')
            {
              free(item);
              //event_loop
            }
              
          //  if (answer_to_choice[0] == 'E' || answer_to_choice[0] == 'e')
        } 
    }

  if (name_exist == false && shelf_exist == true)
    {
      printf("There isn't %s but %s is taken\n", name, shelf_input);
      printf("Go to add_goods again\n");
      add_goods(db);
    }

  if (name_exist == true && shelf_exist == true)
    {
      printf("There is already %s and %s is already taken\n", name, shelf_input);
      printf("Go to the menu \n");
      // event_loop
    }
}
    

int main()
{
  tree_t *db = tree_new();

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

  item_t *item13 = item_on_shelf("lejon", "hane", 1234, "Z90", 5);
  item_t *item14 = item_on_shelf("tiger", "hona", 1234, "N90", 5);
  item_t *item15 = item_on_shelf("glas", "putsad", 1234, "E90", 5);
  item_t *item16 = item_on_shelf("glass", "mjuk", 1234, "O90", 5);
  item_t *item17 = item_on_shelf("mobil", "apple", 1234, "K90", 5);
  item_t *item18 = item_on_shelf("anka", "Kalle", 1234, "U90", 5);
  item_t *item19 = item_on_shelf("goose", "hud", 1234, "B90", 5);
  item_t *item20 = item_on_shelf("little monkey", "crazy", 1234, "X90", 5);
  item_t *item21 = item_on_shelf("kaffe", "arabica", 1234, "S90", 5);
  item_t *item22 = item_on_shelf("jabba the hutt", "tjockis", 1234, "T90", 5);
  item_t *item23 = item_on_shelf("hello kitty", "isn't cat", 1234, "F90", 5);
  
  
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
  tree_insert(db, "lejon", item13);
  tree_insert(db, "tiger", item14);
  tree_insert(db, "glas", item15);
  tree_insert(db, "glass", item16);
  tree_insert(db, "mobil", item17);
  tree_insert(db, "anka", item18);
  tree_insert(db, "goose", item19);
  tree_insert(db, "little monkey", item20);
  tree_insert(db, "kaffe", item21);
  tree_insert(db, "jabba the hutt", item22);
  tree_insert(db, "hello kitty", item23);
 
 
  
  // void *itemshow = item_spec(db, "hallon");
  //print_item(itemshow);

  
  // add_goods(db);

  //index = 1 
  //int tell = twenty_items(db, 4);  
  //printf("%d\n", tell);


  //int ja = show_page_of_items(db, 4);
  //printf("%d\n", ja);

  list_items(db);
  // char *ans =  answer_to_shelf_question(db);
  //printf("%s\n", ans);

  
}
