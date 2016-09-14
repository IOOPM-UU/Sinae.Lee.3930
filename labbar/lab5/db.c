# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>
# include <time.h>
# include "utils.h"

struct item
{
  char *name;
  char *desc;
  int price;
  int amount;
  char *shelf;
};

typedef struct item item_t;

void print_item(item_t *p)
{
  int first;             //quotient
  int second;            //remainder
  
  first = (p->price)/100;
  second = (p->price)%100;
  printf("\n Name: %s\n Desc: %s\n Price: %d.%d SEK\n Amount: %d\n Shelf: %s\n", p->name, p->desc, first, second, p->amount, p->shelf);
}

item_t make_item(char *n, char *d, int p, int a, char *s)
{
  item_t ptr ={};
  ptr.name = n;
  ptr.desc = d;
  ptr.price = p;
  ptr.amount = a;
  ptr.shelf = s;
  return ptr;
}

item_t input_item()
{
  char *name, *desc;
  int price, amount;
  char *shelf;

  name = ask_question_string("Enter the product name?\n");
  
  desc = ask_question_string("Describe the product\n");
  
  price = ask_question_int("Enter the price?\n");

  amount = ask_question_int("Enter the amount of product?\n");
  
  shelf = ask_question_shelf("Enter the shelf nr.\n");

  item_t product = make_item(name, desc, price, amount, shelf);
  return product;
}

char *magick(char *a1[], char *a2[], char *a3[], int len)
{
  int buf_siz = 255;
  char buf[buf_siz];
  int r1 = rand() % len;
  int r2 = rand() % len;
  int r3 = rand() % len;
  char *p1 = a1[r1];   // (1)framslumpad string från array
  char *p2 = a2[r2]; 
  char *p3 = a3[r3];
  int len1 = strlen(p1);   // length of (1);
  int len2 = strlen(p2);
  int len3 = strlen(p3);

  for (int i = 0; i < len1; i++)
    {
      buf[i] = p1[i];
    }
      buf[len1] = '-';
      
 
  for(int i = 0; i < len2; i++)
    {
      buf[len1+1+i] = p2[i];
    }
      buf[len1+len2+1] =' ';
      
  
  for (int i = 0; i < len3; i++)
    {
      buf[len1+len2+2+i] = p3[i];
    }
      buf[len1+len2+len3+2] = '\0';
       
   
  
  return strdup(buf);
}


void list_db(item_t *items, int no_items)
{
  for (int i = 0; i < no_items; ++i)
  printf("%d.\t %s\n", i+1, items[i].name); 
}
  
void edit_db(item_t *item_nr, int db_size)
{
  int nr;
  do
    {
      nr = ask_question_int("Enter the item nr.:\n");
    }
  while (nr <= 0 || nr > db_size);
    {
      print_item(&item_nr[nr-1]);
      item_t change = input_item();
      item_nr[nr-1] = change;
      print_item(&change);
      printf("\n");
      list_db(item_nr, db_size);
    }
}

void print_menu()
{
  printf("\n");
  printf(" [L]ägga till en vara\n");
  printf(" [T]a bort en vara\n");
  printf(" [R]edigera en vara\n");
  printf(" Ån[g]ra senaste ändringen\n");
  printf(" Lista [h]ela varukatalogen\n");
  printf(" [A]vsluta\n");
  printf("\n");
}

char ask_question_menu()
{
  char *key = "LlTtRrGgHhAa";
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

void add_item_to_db(item_t *db, int *nr_item) //number of items.
{
  item_t add_item = input_item();
  db[*nr_item] = add_item;
  *nr_item = *nr_item + 1;
  print_item(&add_item);
  printf("\n");
  list_db(db, *nr_item);
 
  
}

void remove_item_from_db(item_t *db, int *db_siz)
{
  list_db(db, *db_siz);
  int remove;
  do
    {
      remove = ask_question_int("Enter the nr. you want to remove!\n");
    }
  while (remove <= 0 || remove > *db_siz);

  for(int i = remove; i < *db_siz; ++i)
    {
      db[i-1] = db[i];
    }
  
  *db_siz = *db_siz - 1;
  list_db(db, *db_siz); 
}

void event_loop(item_t *db, int *db_siz)
{

  char meny_key;

  do
    {
      meny_key = ask_question_menu();
      
      if (meny_key == 'L' || meny_key == 'l')
        
      add_item_to_db(db, db_siz);
        
      else if  (meny_key == 'T' || meny_key == 't')
       
      remove_item_from_db(db, db_siz);

      else if (meny_key == 'R' || meny_key == 'r')
        
        edit_db(db, *db_siz);
        
      else if (meny_key == 'G' || meny_key == 'g')
       
        printf("Not yet implemented!\n");
      
      else if (meny_key == 'H' || meny_key == 'h')
        
        list_db(db, *db_siz);
    }
  while (meny_key != 'A');
}



/* old main
  item_t p = { .name = "Fazer milk chocolate", .desc = "Delicious finnish chocolate bar", .price = 2495, .shelf = "A50"};
  print_item(&p);

  printf("\n");
  
  char *na = "milk";
  char *de = "from cow";
  int pr = 1000;
  char *sh = "A47";
  item_t pt = {};
  pt = make_item(na, de, pr, sh);
  print_item(&pt);

  input_item();
  */

int main(int argc, char *argv[])
{
  char *array1[] = { "Milk", "Fresh", "Sweet" }; /// Lägg till!
  char *array2[] = { "Chocolate", "Arla", "Dark" }; /// Lägg till!
  char *array3[] = { "Fruit", "Bread", "Sour dough" }; /// Lägg till!

  item_t db[25]; // Array med plats för 16 varor
  int db_siz = 0;    // Antalet varor i arrayen just nu

  /*
  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
   

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }
  */
    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); /// Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); /// Lägg till storlek
        int price = random() % 200000;
        int amount = random() %200;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, amount, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
    /*
     for (int i = 0; i < db_siz; ++i)
     {
       print_item(&db[i]);
     }
     
     list_db(db, db_siz);

     
     printf("Change the item! - edit_db\n");
     
     edit_db(db, db_siz);

     char ch =  ask_question_menu();
     printf("%c\n", ch);

    
     printf("add_item_to_db\n");
     add_item_to_db(db, &db_siz);
     list_db(db, db_siz);

     remove_item_from_db(db, &db_siz);
     */
    
    event_loop(db, &db_siz);

 
  return 0;
}
