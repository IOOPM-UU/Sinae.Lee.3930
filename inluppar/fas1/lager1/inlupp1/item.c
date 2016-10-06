#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "item.h"
#include "utils.h"
#include "list.h"

typedef struct item item_t;

typedef struct storage storage_t;

struct item    // tree
{
  char *name;
  char *description;
  int price;
  storage_t *storage;   //storage
  list_t *list; // lista med storage
};

struct storage
{
  char *shelf;    // hyllnummer
  int amount;
};

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

char *get_shelf(storage_t *storage)
{
  return storage->shelf;
}

int get_amount(storage_t *storage)
{
  return storage->amount;
}

char *get_name(item_t *item)
{
  return item->name;
}

char *get_shelf_nr(item_t *item)
{
  if (item != NULL)
    {
      storage_t *storage = item->storage;
      char *shelf = storage->shelf;    //problem
      return shelf;
    }

  else
    {
      printf("There is no such item\n");
      return NULL;
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
      item->storage = storage;
    }
  return item;
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
  storage_t *storage = item->storage;
  char *shelf = get_shelf(storage);
  int amount = get_amount(storage);

  printf("Name: %s\n"
         "Description: %s\n"
         "Price: %d.%d kr\n"
         "Shelf: %s\n"
         "Amount: %d\n",
         name, description, q, r, shelf, amount);
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


item_t *edit_item_name(item_t *item) //Ändra i trädets ordning också?
{
	//print old name
	item_t *old_item = item; //behövs gamla item för att ångra?
	char *old_name = old_item->name;
	printf("\nCurrent name: %s\n", old_name);
	printf("--------------------------------------------------------\n");
	// ask for new name
	char *new_name = ask_question_string("Enter new name: ");
	//check if new name isn't already on the database
	//bool is_name_available = name_check(db, new_name);
	//insert new name
	//if(is_name_available == true)
	//{
		item->name = new_name;
		printf("\nNew name is: %s\n", new_name);
	//}
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

item_t *edit_item_shelf(item_t *item)
{
	//print old shelf
	item_t *old_item = item;
	char *old_shelf = get_shelf(old_item->storage); //old_item->storage_control->storage_nr;
	printf("\nCurrent shelf: %s\n", old_shelf);
	printf("--------------------------------------------------------\n");
	//ask for new shelf
	char *new_shelf = ask_question_shelf("Enter new shelf: ");
	//check if shelf is available
	//bool is_shelf_avail = shelf_check(db, new_shelf);
	//insert new shelf
	//if (is_shelf_avail == true)
	//{
		item->storage->shelf = new_shelf;
		printf("\nNew shelf is: %s\n", new_shelf);
	//}
	return item;
}

item_t *edit_item_amount(item_t *item)
{
	//print old amount
	item_t *old_item = item;
	int old_amount = get_amount(old_item->storage); //old_item->storage_control->amount;
	printf("\nCurrent amount: %d\n", old_amount);
	printf("--------------------------------------------------------\n");
	//ask for new amount
	int new_amount = ask_question_int("Enter new amount: ");
	//insert new amount
	item->storage->amount = new_amount;
	printf("\nNew amount is: %d\n", new_amount);
	return item;
}
