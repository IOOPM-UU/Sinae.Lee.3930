# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include "utils.h"
# include "list.h"
# include "tree.h"
# include "item.h"

void event_loop(tree_t *db, action_t *action)
{
  char meny_key;
  do
    {
      meny_key = ask_question_menu();
	  
      if(meny_key == 'A')
        {
          add_goods(db, action);
        }
          //edit_item(db, action);
		  
      else if(meny_key == 'L')
        {
          list_items(db);  //list_db
        }
        
      else if (meny_key == 'R')
        {
            remove_item(db);
        }
      else if(meny_key == 'U')
        {
            undo_changes(db, action);
         
        }
		
      else if(meny_key == 'B')
	    {
		  balanced_tree(db);
		  printf("\nTree balanced\n");
		  
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
  item_t *item23 = item_on_shelf("hello kitty", "isn't a cat", 1234, "F90", 5);
  
  
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
  /*
  bool test = tree_remove(db, "glas");
  if (test == true) {printf("glas is gone\n");}
  bool test2 = tree_remove(db, "anka");
  if (test2 == true) {printf("anka is gone\n");}
  bool test3 = tree_remove(db, "apple");
  if (test3 == true) {printf("apple is gone\n");}
  bool test4 = tree_remove(db, "goose");
  if (test4 == true) {printf("goose is gone\n");}
  bool test5 = tree_remove(db, "hello kitty");
  if (test5 == true) {printf("hello kitty is gone\n");}
   */
  action_t *action = action_new();
  event_loop(db, action);
  
  return 0;
}
