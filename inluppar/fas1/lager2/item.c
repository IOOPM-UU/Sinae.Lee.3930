#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "item.h"
#include "utils.h"
#include "list.h"
#include "tree.h"

struct item
{
  char *name;
  char *description;
  int price;
  list_t *list; //lista med storage
};

struct storage
{
  char *shelf;    // hyllnummer
  int amount;
};

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } TYPE;
  bool storage_add;
  storage_t *merch_storage;
  storage_t original_storage;
  item_t *merch;
  item_t original;
};

action_t *action_new()
{
    action_t *action = calloc(1, sizeof(action_t));
    action->TYPE = NOTHING;
    return action;
}

void undo_changes(tree_t *tree, action_t *action)
{
  if (action->TYPE == NOTHING)
    {
      printf("There is nothing to undo\n");
    }
  if (action->storage_add == true)
    {
      
      if (action->TYPE == ADD)
        {
          void **remove = calloc(1, sizeof(void **));
          int length = list_length(action->merch->list);
          if (list_remove(action->merch->list, length-1, remove))
            {
              free(*remove);
              free(remove);
              printf("storage add undone\n");
              action->TYPE = NOTHING;
            }
        }

      if (action->TYPE == EDIT)
        {
          
          *action->merch_storage = action->original_storage;
          action->TYPE = NOTHING;
          action->storage_add = false;
        }
    }

  if (action->TYPE == ADD)
    {
      char *added_name = action->merch->name;
      bool undo = tree_remove_leaf(tree, added_name);
      if (undo == true)
        {
          printf("ADD undone\n");
		  action->TYPE = NOTHING;
        }
      
      else
        {
          printf("failed\n");
        }
    }
      
    
  
  if (action->TYPE == EDIT)
    {
      *action->merch = action->original;
      action->TYPE = NOTHING;
      printf("Edit undone\n");
    }
}


storage_t *make_storage(char *shelf, int amount)
{
  storage_t *storage= calloc(1, sizeof(storage));
  if (storage != NULL)
    {
      storage->shelf = shelf;
      storage->amount = amount;
    }
  return storage;
}

void item_free(item_t *item)
{
    if (item != NULL)
    {
        //free(item->storage);
        free(item->description);
        free(item->name);
		list_free(item->list);
        free(item);
    }
    return;
}

char *get_shelf(storage_t *storage)
{
  return storage->shelf;
}

int get_amount(storage_t *storage)
{
  return storage->amount;
}

storage_t *get_storage_add(item_t *item, int index)
{
  list_t *list = item->list;
  return list_get(list, index);
}

char *get_name(item_t *item)
{
  char *name = item->name;
  return name;
}

//new
int item_list_length(item_t *item)
{
  return list_length(item->list);
}

//lagat för add
char *get_shelf_nr(item_t *item, int index)
{
  list_t *list = item->list;
  storage_t *storage = list_get(list, index);
  return storage->shelf;
}

//lagat för add
int *get_storage_amount(item_t *item, int index)
{
  list_t *list = item->list;
  storage_t *storage = list_get(list, index);
  return &storage->amount;
}

char *get_description (item_t *item)
{
  char *description = item->description;
  return description;
}

int get_price (item_t *item)
{
  if (item != NULL)
    {
      return item->price;
    }

  else //item == NULL
    {
      return 0;
    }
}

item_t *make_item(char *name, char *desc, int price, storage_t *storage)
{
  item_t *item = calloc(1, sizeof(item_t));
  if (item != NULL)
    {
      item->name = name;
      item->description = desc;
      item->price = price;
      item->list = list_new();
      list_append(item->list, storage);
    }
  return item;
}

list_t *get_item_list(item_t *item)
{
  return item->list;
}

//make item  with shelf location
item_t *item_on_shelf(char *name, char *desc, int price, char *shelf, int amount)
{
  storage_t *storage = make_storage(shelf, amount);
  
  return make_item(name, desc, price, storage);
}


item_t *input_item()
{
  char *name, *desc;
  int price;
  char *shelf;
  int amount;

  name = ask_question_string("Enter the product name?\n");
  
  desc = ask_question_string("Describe the product\n");
  
  price = ask_question_int("Enter the price?\n");
  
  shelf = ask_question_shelf("Enter the shelf nr.\n");

  amount = ask_question_int("Enter the amount\n");

  item_t *item = item_on_shelf(name, desc, price, shelf, amount);

  return item;
}



void print_item(item_t *item)
{
  int q, r; //qutient, remainder
  q = (item->price)/100;
  r = (item->price)%100;
  char *name = item->name;
  char *description = item->description;
  
 
 

  printf("\n"
         "Name: %s\n"
         "Description: %s\n"
         "Price: %d.%d kr\n"
         "Shelf:\t\tAmount:\n",
         name, description, q, r);
  print_list_storage(item->list);
}

void print_list_storage(list_t *list)
{
  int len = list_length(list);

  for(int i = 0; i<len; ++i)
    {
      storage_t *storage = list_get(list, i);

      printf("%d. %s\t\t%d\n", i+1, storage->shelf, storage->amount);
    }
}

item_t *edit_item_name(item_t *item) //Ändra i trädets ordning också?
{
  //print old name
  item_t *old_item = item; //behövs gamla item för att ångra?
  char *old_name = old_item->name;
  printf("\nCurrent name: %s\n", old_name);
  printf("--------------------------------------------------------\n");
  // ask for new name
  char *new_name = ask_question_string("Enter new name: ");
  
  item->name = new_name;
  printf("\nNew name is: %s\n", new_name);
  return item;
}

item_t *edit_item_desc(item_t *item)
{
  //print old description
  item_t *old_item = item;
  char *old_desc = old_item->description;
  printf("\nCurrent description: %s\n", old_desc);
  printf("--------------------------------------------------------\n");
  //ask for new description
  char *new_desc = ask_question_string("Enter new description: ");
  //insert new description
  item->description = new_desc;
  printf("\nNew description is: %s\n", new_desc);
  return item;
}

item_t *edit_item_price(item_t *item)
{
  //print old price
  item_t *old_item = item;
  int old_price = old_item->price;
  printf("\nCurrent price: %d\n", old_price);
  printf("--------------------------------------------------------\n");
  //ask for new price
  int new_price = ask_question_int("Enter new price: ");
  //insert new price
  item->price = new_price;
  printf("\nNew price is: %d\n", new_price);
  return item;
}

item_t *edit_item_storage(tree_t *tree, item_t *item)
{
	print_list_storage(item->list);
	list_t *shelves_taken = extract_shelves(tree);
	int length = list_length(item->list);
	int index;
	//ask for which storage
	do
	  {
		index = ask_question_int("Which storage do you want to edit?");
	  }
	while(index < 1 || index > length);
	
	storage_t *current_storage = list_get(item->list, index-1);
	
	char *old_shelf = current_storage->shelf;
	int old_amount = current_storage->amount;
	printf("\nCurrent shelf: %s\nCurrent amount: %d\n", old_shelf, old_amount);
    printf("--------------------------------------------------------\n");
	
	//ask for new shelf
  char *new_shelf; // = ask_question_shelf("Enter new shelf: ");
  //check if shelf is available
  bool is_shelf_avail;// = is_shelf_taken(new_shelf, shelves_taken);
  do
    {
      new_shelf = ask_question_shelf("Enter new shelf: ");
      is_shelf_avail = is_shelf_taken(new_shelf, shelves_taken);
    }
  while(is_shelf_avail);
  //ask for new amount
  int new_amount = ask_question_int("Enter new amount: ");
  current_storage->shelf = new_shelf;
  current_storage->amount = new_amount;
  printf("\nNew shelf is: %s\nNew amount is: %d\n", new_shelf, new_amount);
  return item;
  
}

void  print_current_amount(item_t *item, int index)
{
   int *old_amount = get_storage_amount(item, index); 
   printf("\nCurrent amount: %d\n", *old_amount);
   printf("--------------------------------------------------------\n");
}

// increase item amount and display item
item_t *increase_item_amount(item_t *item, int index, int add_amount)
{
    int *old_amount = get_storage_amount(item, index); 
    
    *old_amount = *old_amount + add_amount;
    int new_amount = *old_amount;
    printf("\nNew amount is: %d\n", new_amount);
    return item;
}
 
char *get_item_name(item_t *item)
{
  char *name = item->name;
  return name;
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
        edited_item = edit_item_storage(db, item);
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

// printar ut varulist för remove
void print_list_for_remove (tree_t *db)
{
  list_t *keys = tree_keys(db);
  int length = list_length(keys);
  for (int i = 0; i < length; ++i)
    {
      char *name =list_get(keys, i);
      printf("%d. %s\n", i+1, name);
    }
}

void remove_item(tree_t *db)
{
  print_list_for_remove(db);
  char *name = ask_question_string("Enter the name of the product to remove: \n");
  bool exist = is_item_in_db(db, name);
  if (exist == false){printf("nope, varan finns inte\n");}
  else
    {
      tree_remove(db, name);
      printf("To see the new updated list, press 'l' or 'L'\n");
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

item_t *ask_new_item_desc_price_amount(char *name, char *shelf)
{
	char *description = ask_question_string("Description: \n");
    int price= ask_question_int("Price: \n");
    int amount = ask_question_int("Amount: \n");
            
    item_t *item = item_on_shelf(name, description, price, shelf, amount);
    print_item(item);
	return item;
}

void change_action_to_add_item(item_t *item, action_t *action)
{
	action->TYPE =ADD;
	action->storage_add = false;
    action->merch = item;
}

void ask_add_new_item(tree_t *db, item_t *item, action_t *action)
{
	char answer_to_choice = ask_question_yes_no("\nDo you want add the item?\n");
	if (answer_to_choice == 'Y')
	{
		char *name = get_name(item);
		tree_insert(db, name, item);
		change_action_to_add_item(item, action);
    }        
    if (answer_to_choice == 'N')
    {
		free(item);
    }
}

void change_action_to_edit_storage(item_t *item, int index, int add_amount, action_t *action)
{
	action->original_storage = *get_storage_add(item, index-1);
    action->TYPE = EDIT;
    action->storage_add = true;
              
    increase_item_amount(item, index-1, add_amount);
    print_item(item);

    action->merch_storage = get_storage_add(item, index-1);
}

void ask_add_amount_to_given_shelf(item_t *item, action_t *action)
{
	int list_index = ask_question_int ("\nWhich shelf do you want to change?\n");

    print_current_amount(item, list_index-1);
    int add_amount = ask_question_int("Enter amount:");
    char answer_to_choice = ask_question_yes_no("\nDo you want add the item?\n");
            
    if (answer_to_choice == 'Y' )
    {
        change_action_to_edit_storage(item, list_index, add_amount, action);
    }
    if (answer_to_choice == 'N')
    {
        free(item);
    }
}

void change_action_to_add_storage(item_t *current, action_t *action)
{
	action->TYPE = ADD;
    action->storage_add = true;
    action->merch = current;
}

void ask_add_new_shelf_to_current_item(item_t *current, list_t *item_list, char *shelf, action_t *action)
{
    int amount = ask_question_int("Amount: \n");
                
    storage_t *new_storage = make_storage(shelf, amount);
    list_append(item_list, new_storage);
    print_list_storage(item_list);
                
    char answer_to_choice = ask_question_yes_no("\nDo you want to add the shelf?\n");
    if (answer_to_choice == 'Y')
    {
		change_action_to_add_storage(current, action);
    }
    if (answer_to_choice == 'N')
    {
        free(new_storage);
    }
}

void add_new_item_to_db(tree_t *db, char *name, action_t *action)
{
	char *shelf_input = ask_question_shelf("Enter a shelf nr: \n");
        if (is_shelf_taken_add(db, shelf_input) == false)
        {   
            item_t *item = ask_new_item_desc_price_amount(name, shelf_input);
            ask_add_new_item(db, item, action);
        }
        
        else // is_shelf_taken(db, shelf_input) == true
        {
            shelf_input = ask_question_shelf("\nChoose another shelf\n");
            while(is_shelf_taken_add(db, shelf_input) == true)
            {
                shelf_input = ask_question_shelf("\nPlease choose another shelf\n");
            }
            
            item_t *item = ask_new_item_desc_price_amount(name, shelf_input);
            ask_add_new_item(db, item, action);
        }
}

void ask_new_storage_to_item(tree_t *db, char *name, action_t *action)
{
	item_t *current = item_spec(db, name);
		list_t *item_list = get_item_list(current);
		char *shelf = ask_question_shelf("\nEnter a shelf\n");
    
		if (is_shelf_taken_add(db, shelf) == false)
		{
			ask_add_new_shelf_to_current_item(current, item_list, shelf, action);
		}
		else // shelf is taken
		{
			char *shelf = ask_question_shelf("\nPlease choose another shelf\n");
            while(is_shelf_taken_add(db, shelf) == true)  // is_shelf_taken(db, shelf_input) == true
            {
                shelf = ask_question_shelf("\nPlease choose another shelf\n");
            }
            ask_add_new_shelf_to_current_item(current, item_list, shelf, action);
		}
}

void add_new_shelf_or_increase_amount_to_item(tree_t *db, char *name, action_t *action)
{
	printf("\n%s already exsits. Please read the following information about the item.\n", name);
    item_t *item = item_spec(db, name);
    print_item(item);
        
    char answer = ask_question_yes_no("\nDo you want to use one of these shelves?\n");
    if (answer == 'Y' )
    {
        ask_add_amount_to_given_shelf(item, action);
    }
    if (answer == 'N')
    {
		ask_new_storage_to_item(db, name, action);
	} 
}



void add_goods(tree_t *db, action_t *action)
{
    printf("----------------------");
    printf("\n    Add an item\n");
    printf("----------------------\n");
    
    char *name = ask_question_string("Enter a name: \n");
    
    bool name_exist = is_item_in_db(db, name);
    
    if (name_exist == false)
    {
		add_new_item_to_db(db, name, action);
    }
    if(name_exist == true)
    {
		add_new_shelf_or_increase_amount_to_item(db, name, action);
    }
}








