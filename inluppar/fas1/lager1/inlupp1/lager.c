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
  enum { NOTHING, ADD, REMOVE, EDIT } type;
  char *add;
  item_t *edited;    
  item_t *old;   
};

action_t *action_new(void)
{
  action_t *action = calloc(1, sizeof(action_t));
  if (action)
    {
      action->type = NOTHING;
    }
  return action;
}


void action_edit(action_t *action, item_t *item)
{
  if(action->type == EDIT)
    {
      item_free(action->old);
      action->edited = NULL;
    }
  action->type = EDIT;
  action->edited = item;
  action->old = copy_item(item);
  return;
}


void action_add(action_t *action, char *name)
{
  if (action->type == ADD)
    {
      free(action->add);
    }
  action->type = ADD;
  action->add = strdup(name);
  return;
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


bool name_check(tree_t *db, char *new_name);

int amount_of_pages(int length)
{
  int max_elements = length - 1;
  int page = (max_elements - (max_elements % 20)) / 20;
  return page;
	
}

//visar innehållet av item
void *item_spec(tree_t *db, char *name)
{
  return search_data_in_tree(db, name);
}

item_t *display_item(tree_t *tree, list_t *keys, int item_index) 
{
  char *item_name = (char *)list_get(keys, item_index);
  
  void *item_show = item_spec(tree, item_name);
  printf("\n==== Item display ====\n\n");
  print_item(item_show);
  printf("\n\n\n\n\n");
  return item_show;
}

item_t *get_item(tree_t *tree, list_t *keys, int item_index)
{
  char *item_name = (char *)list_get(keys, item_index);
  item_t *edit_item = item_spec(tree, item_name);
  return edit_item;
}

bool edit_menu_loop(tree_t *db, item_t *item)
{
  char meny_key;
  char y_n_key;
  item_t *edited_item;
  
  //list_t *shelves_taken = list_node_shelf(db);
  
  //do
    //{

      meny_key = ask_question_edit_menu("\nWhat do you wish to edit?");
      
	  if(meny_key == 'N')
        {
		  /*edited_item = edit_item_name(item);
		  y_n_key = ask_question_yes_no("\nDo you wish to continue edit item?");
		  if (y_n_key == 'Y')
		  {
			  edit_menu_loop(db, edited_item);
			  return true;
		  }
		  if(y_n_key == 'N') return false;*/
		  printf("\n!!!! NOT YET IMPLEMENTED !!!!\n");
		  return false;
        }
		
      else if(meny_key == 'D')
        {
          edited_item = edit_item_desc(item);
		  y_n_key = ask_question_yes_no("\nDo you wish to continue edit item?");
		  if (y_n_key == 'Y')
		  {
			  edit_menu_loop(db, edited_item);
			  return true;
		  }
		  if(y_n_key == 'N') return false;
        }
		
      else if(meny_key == 'P')
        {
          edited_item = edit_item_price(item);
		  y_n_key = ask_question_yes_no("\nDo you wish to continue edit item?");
		  if (y_n_key == 'Y')
		  {
			  edit_menu_loop(db, edited_item);
			  return true;
		  }
		  if(y_n_key == 'N') return false;
        }
		
      else if(meny_key == 'S')
        {
          edited_item = edit_item_shelf(db, item);
		  y_n_key = ask_question_yes_no("\nDo you wish to continue edit item?");
		  if (y_n_key == 'Y')
		  {
			  edit_menu_loop(db, edited_item);
			  return true;
		  }
		  if(y_n_key == 'N') return false;
        }
		
      else if(meny_key == 'A')
        {
          edited_item = edit_item_amount(item);
		  y_n_key = ask_question_yes_no("\nDo you wish to continue edit item?");
		  if (y_n_key == 'Y')
		  {
			  edit_menu_loop(db, edited_item);
			  return true;
		  }
		  if(y_n_key == 'N') return false;
        }
	  else if(meny_key == 'B') return false;
    //}
  //while(meny_key != 'B');  // back	
  	if (edit_menu_loop(db, item)) // if true
	{
		return true;
	}
	return false;
}





bool aux_list_items(tree_t *db, int index, int page) //prints out the keys, in-order
{
	//printf("\n\n\n\n\n\n\n\n");
	printf("\n========= List of items ========\n");
	
	list_t *keys = tree_keys(db);
	int length = list_length(keys);
	bool show_next;// = show_next_page(length, index);
	bool show_prev;// = show_prev_page(length, index);
	int count = 0;// kanske inte behövs, kanske räcker med index % 20
	//int page = 0;
	int prev_i = index;
	int max_pages = amount_of_pages(length) + 1;
	
	
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
	printf("\nItem's index from %d to %d", prev_i, index - 1);
	printf("\tYou are on page %d of %d\n", page+1, max_pages);
	
	show_next = show_next_page(length, index);
	show_prev = show_prev_page(length, index);
	
	if (length <= 20)
	{
		char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'E')
		{
			printf("Edit item\n");
			int item_index = ask_question_index("Which item do you want to edit?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			item_t *edit_item = get_item(db, keys, item_index);
			
			edit_menu_loop(db, edit_item);
			return true;
		}
		if (answer == 'D')
		{
			int item_index = ask_question_index("Which item do you want to display?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			return true; //eller false för att återgå till menu?
		}
		if (answer == 'B')
		{
			printf("\n\n\n\n\n\n\n\n");
			return false;
		}
		printf("\nInvalid input 1\n");
		aux_list_items(db,index - (index % 20), page);
		return true;
	}
	
	if (length > 20 && index == 20) //there's 21 items or more
	{
		char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'N')
		{
			aux_list_items(db,index, page+1);
			return true;
		}
		if (answer == 'E')
		{
			printf("Edit item\n");
			int item_index = ask_question_index("Which item do you want to edit?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			item_t *edit_item = get_item(db, keys, item_index);
			
			edit_menu_loop(db, edit_item);
			return true;
		}
		if (answer == 'D')
		{
			int item_index = ask_question_index("Which item do you want to display?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			return true;
		}
		if (answer == 'B')
		{
			printf("\n\n\n\n\n\n\n\n");
			return false;
		}
		printf("\nInvalid input 2\n");
		aux_list_items(db, index - 20, page);
		return true;
	}
	
	if (length > 20 && index > 20 && index % 20 == 0)
	{

		char answer = ask_question_list_menu(show_next, show_prev);
		if( answer == 'N')
		{
			aux_list_items(db,index,page+1);
			return true;
		}
		if (answer == 'P')
		{
			aux_list_items(db, index-40,page-1);
			return true;
		}
		if (answer == 'E')
		{
			printf("Edit item\n");
			int item_index = ask_question_index("Which item do you want to edit?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			item_t *edit_item = get_item(db, keys, item_index);
			
			edit_menu_loop(db, edit_item);
			return true;
		}
		if (answer == 'D')
		{
			int item_index = ask_question_index("Which item do you want to display?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			return true;
		}
		if (answer == 'B')
		{
			printf("\n\n\n\n\n\n\n\n");
			return false;
		}
		printf("\nInvalid input 3\n");
		aux_list_items(db, index - 20, page);
		return true;
	}
	
	if (length > 20 && index > 20 && index % 20 != 0)
	{

		char answer = ask_question_list_menu(show_next, show_prev);
		if (answer == 'P')
		{
			aux_list_items(db,index - (index%20)-20, page-1);
			return true;
		}
		if (answer == 'E')
		{
			printf("Edit item\n");
			int item_index = ask_question_index("Which item do you want to edit?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			item_t *edit_item = get_item(db, keys, item_index);
			
			edit_menu_loop(db, edit_item);
			return true;
		}
		if (answer == 'D')
		{
			int item_index = ask_question_index("Which item do you want to display?", length, page);
			printf("\n\n");
			display_item(db, keys, item_index);
			return true;
		}
		if (answer == 'B')
		{
			printf("\n\n\n\n\n\n\n\n");
			return false;
		}
		printf("\nInvalid input 4\n");
		aux_list_items(db,index - (index%20), page);
		return true;
	}
	
	if (aux_list_items(db, index, page)) // if true
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
      aux_list_items(db, 0, 0);
    }
}

bool is_shelf_taken_add(tree_t *db, char *shelf)
{
  char *temp;
  list_t *shelf_list = extract_shelves(db);
  int length = list_length(shelf_list);

  for (int i = 0; i < length; i++)
    {
      temp = list_get(shelf_list, i);
      if (strcmp(temp, shelf) == 0)
        {
          printf("\n"
                 "%s is already taken\n", shelf);
          return true;
        }
    }
  
  return false;
}

void add_goods(tree_t *db)
{
  printf("----------------------");
  printf("\n    Add an item\n");
  printf("----------------------\n");

  char *name = ask_question_string("Enter a name: \n");
  //char *shelf_input = ask_question_shelf("Enter shelf nr: \n");

  bool name_exist = is_item_in_db(db, name);
  // bool shelf_exist = is_shelf_taken(db, shelf_input);
  
  if (name_exist == false)
    {
      char *shelf_input = ask_question_shelf("Enter a shelf nr: \n");
      if (is_shelf_taken_add(db, shelf_input) == false)
        {
          char *description = ask_question_string("Description: \n");
          int price= ask_question_int("Price: \n");
          int amount = ask_question_int("Amount: \n");

          item_t *item = item_on_shelf(name, description, price, shelf_input, amount);
          print_item(item);
      
          char *answer_to_choice = ask_question_string("\n"
                                                       "Do you want add the item?\n"
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

      else // is_shelf_taken(db, shelf_input) == true
        {
          shelf_input = ask_question_shelf("\n"
                                           "Choose another shelf\n");
          while(is_shelf_taken_add(db, shelf_input) == true) 
            {
              shelf_input = ask_question_shelf("\n"
                                         "Please choose another shelf\n");
            }
          char *description = ask_question_string("Description: \n");
          int price= ask_question_int("Price: \n");
          int amount = ask_question_int("Amount: \n");

          item_t *item = item_on_shelf(name, description, price, shelf_input, amount);
          print_item(item);

          char *answer_to_choice = ask_question_string("\n"
                                                       "Do you want add the item?\n"
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
    }
  //if item already exist in db men inte på "shelf_input"
  if(name_exist == true)
    {
      printf("\n"
             "%s already exsits. Please read the following information about the item.\n", name);
      item_t *existing_item = item_spec(db, name);
      print_item(existing_item);
      int list_index = ask_question_int ("\n"
                                         "Which shelf do you want to change amount?\n");
 
      char *answer = ask_question_string("\n"
                                         "Are you sure?\n"
                                         "[Y]\n"
                                         "[N]o\n");

      if (answer[0] == 'Y' || answer[0] == 'y')
        {
          void *item = item_spec(db, name);
          increase_item_amount(item, list_index-1);
          print_item(item);
          char *answer_to_choice = ask_question_string("\n"
                                                       "Do you want add the item?\n"
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
          item_t *current = item_spec(db, name);
          list_t *item_list = get_item_list(current);
          char *shelf = ask_question_shelf("\n"
                                           "Enter a shelf\n");
          if (is_shelf_taken_add(db, shelf) == false)
            {
              
              // char *description = ask_question_string("Description: \n");
              // int price = ask_question_int("Price: \n");
              int amount = ask_question_int("Amount: \n");

              storage_t *new_storage = make_storage(shelf, amount);
              list_append(item_list, new_storage);
              print_list_storage(item_list);
              
              
          
              char *answer = ask_question_string("\n"
                                                 "Do you want add the item?\n"
                                                 "[Y]es\n"
                                                 "[N]o\n"
                                                 "[E]dit\n");
              if (answer[0] == 'Y' || answer[0] == 'y')
                {
                  tree_insert(db, name, current);
                  //event_loop
                }
              
              if (answer[0] == 'N' || answer[0] == 'n')
                {
                  free(new_storage);
                  //event_loop
                }
            
              //  if (answer_to_choice[0] == 'E' || answer_to_choice[0] == 'e')
            }

          else // shelf is taken
            {
              char *shelf = ask_question_shelf("\n"
                                               "Please choose another shelf\n");
              while(is_shelf_taken_add(db, shelf) == true)  // is_shelf_taken(db, shelf_input) == true
                {
                  shelf = ask_question_shelf("\n"
                                             "Please choose another shelf\n");
                }

              char *description = ask_question_string("Description: \n");
          int price= ask_question_int("Price: \n");
          int amount = ask_question_int("Amount: \n");

          item_t *item = item_on_shelf(name, description, price, shelf, amount);
          print_item(item);

          char *answer_to_choice = ask_question_string("\n"
                                                       "Do you want add the item?\n"
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
        }
    }
}


void undo_action_add(tree_t *db, action_t *action)
{
  if (action->type == ADD)
    {

      bool t = tree_remove_leaf(db, action->add);
      if(t)
        {
          
          printf("%s is removed\n", action->add);
        }

      else
        {
          printf("Coming soon. We don't have tree_remove\n");
        }
      
    }

  if (action->type == EDIT)
  return;
  
}

void event_loop(tree_t *db)//, action_t *action)
{
  char meny_key;
  do
    {
      meny_key = ask_question_menu();
	  
      if(meny_key == 'A')
        {
			add_goods(db);
        }
          //edit_item(db, action);
		  
      else if(meny_key == 'L')
        {
          list_items(db);  //list_db
        }
		  
      else if(meny_key == 'U')
        {
			printf("\n!!!! NOT YET IMPLEMENTED !!!!\n");
          //undo(action);
        }
		
      else if(meny_key == 'R')
        {
          printf("!!!! NOT YET IMPLEMENTED !!!!\n");
        }
    }
	
  while(meny_key != 'Q');  // quit program, exit
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
  item_t *item11 = item_on_shelf("zebra", "savannah", 3120, "G21", 4);
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
 
  
  
  
  event_loop(db);
 
  return 0;
}
