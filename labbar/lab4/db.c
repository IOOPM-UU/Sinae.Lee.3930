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
  char *shelf;
};

typedef struct item item_t;

void print_item(item_t *pi)
{
  int first;             //quotient
  int second;            //remainder
  first = (pi->price)/100;
  second = (pi->price)%100;
  printf("\n Name: %s\n Desc: %s\n Price: %d.%d SEK\n Shelf: %s\n", pi->name, pi->desc, first, second, pi->shelf);
}

item_t make_item(char *n, char *d, int p, char *s)
{
  item_t ptr ={};
  ptr.name = n;
  ptr.desc = d;
  ptr.price = p;
  ptr.shelf = s;
  return ptr;
}

item_t input_item()
{
  char *name, *desc;
  int price;
  char *shelf;

  name = ask_question_string("Enter the product name?\n");
  
  desc = ask_question_string("Describe the product\n");
  
  price = ask_question_int("Enter the price?\n");
  
  shelf = ask_question_shelf("Enter the shelf nr.\n");

  item_t product = make_item(name, desc, price, shelf);
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
  printf("%d.\t %s\n", no_items+1, items->name); 
}
  
void edit_db(item_t *item_nr, int db_size)
{
  int nr = 0;
  while (nr < 1)
    {
      int nr = ask_question_int("Enter the item nr.:\n");
      if (nr > 0 && nr <= db_size)
        {
          print_item(&item_nr[nr-1]);
          item_t change = input_item();
          item_nr[nr-1] = change;
        }
    }
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
  char *array1[] = { "Milk", "Fazer", "Sweet" }; /// Lägg till!
  char *array2[] = { "Chocolate", "Arla", "Bitter" }; /// Lägg till!
  char *array3[] = { "Ruccola", "Dole", "Fresh" }; /// Lägg till!

  item_t db[16]; // Array med plats för 16 varor
  int db_siz = 0;    // Antalet varor i arrayen just nu

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

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); /// Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); /// Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     for (int i = 0; i < db_siz; ++i)
     {
       print_item(&db[i]);
     }
     for (int i = 0; i < db_siz; ++i)
     {
       list_db(&db[i], i);
     }

       
     

  }
  edit_db(db, db_siz);
  return 0;
}
