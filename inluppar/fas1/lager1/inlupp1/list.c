# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>
# include "list.h"



/// !! OBS -- du kommer att behöva ändra lite i denna fil. 
/// !! Detta är en lista som endast hanterar heltal. Men det 
/// !! kommer inte att räcka för oss här eftersom vi skall ha
/// !! andra data (vilka??) i vår (enda) lista. 



struct list{             

  struct node *first;
  struct node *last;
};

struct node
{                  
  void *elem;        // elem stored in the node. void * we can store whatever we like
  struct node *next;     // pointer pointing to the next node in the list(for linked list), null for last node
};

struct node  *node_new(void *element, struct node *next)
{
  
  struct node *n = malloc(sizeof(struct node));
  if (n == NULL)
    return NULL;
  n->elem = element;
  n->next = next;      
  return n;
}

/// Creates a new list
///
/// \returns: empty list
list_t *list_new()
{
  list_t *l = malloc(sizeof(struct list)); 
  if (l == NULL)
    return NULL;
  l->first = NULL;
  l->last = NULL;
  return l;
}

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the integer to be appended
void list_append(list_t *list, int elem)
{
  struct node *newElem = node_new(&elem, list->last);
  
  if (list == NULL)
    {
     list->last = list->first = newElem;
    }
  else
    {
      list->last->next = newElem;
      list->last = newElem;
    }
}

/// Inserts a new element at the beginning of the list
///
/// \param list pointer to the list
/// \param elem the integer to be prepended
void list_prepend(list_t *list, int elem)
{
  struct node *newElem = node_new(&elem, list->first);
  
  if (list == NULL)
    {
      list->first = list->last = newElem;
    }

  else
    {
      list->first = newElem;
    }
  
}


/// A convenience for list_get(list, 0)
int *list_first(list_t *list)
{
  struct node *f_cursor = list->first;

  if (f_cursor == NULL)
    return NULL;

  else
    return f_cursor->elem;

}

/// A convenience for list_get(list, -1)
int *list_last(list_t *list)
{
  struct node *l_cursor = list->last;

  if (l_cursor == NULL)
    return NULL;

  else
    return l_cursor->elem;
}
