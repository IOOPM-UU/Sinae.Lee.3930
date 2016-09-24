# include "list.h"

typedef struct node node_t;

struct node
{                 
  void *value;
  node_t *next;    
};

struct list{             

  node_t *first;
  node_t *last;
};


node_t *node_new(void *value, node_t *next)
{
  node_t *node = calloc(1, sizeof(node_t));
  if (node == NULL)
    {
      printf("The node is empty\n");
      return NULL;
    }
  else
    {
      node->value = value;
      node->next = next;
    }
  return node;
}

void node_free(node_t *node)
{
  free(node);
}

list_t *list_new()
{
  list_t *empty_list = calloc(1, sizeof(list_t)); 
  if (empty_list == NULL)
    return NULL;
  empty_list->first = NULL;
  empty_list->last = NULL;
  return empty_list;
}



void list_append(list_t *list, void *elem)
{
  node_t *append_node = node_new(elem, NULL);
  
  if(list->first == NULL)
    {
      list->first = list->last = append_node;
    }
  else
    {
      list->last->next = append_node;
      list->last = append_node;
    }
}

void list_prepend(list_t *list, void *elem)
{
  node_t *prepend_node = node_new(elem, list->first);

  if (list->first == NULL)
    {
      list->first = list->last = prepend_node;
    }

  else
    {
      list->first = prepend_node;
    }
}


bool list_insert(list_t *list, int index, void *elem)
{
  int pos_i;
  int i;
  bool value;
  int length = list_length(list);
  node_t *new_node = node_new(elem, NULL); // make a new node to be inserted
  node_t *temp = list->first;

  if(index > length)
    {
      return false;
    }

  if (index == 0)
    {
      list_prepend(list, elem);
      return true;
    }

  if (index == length)
    {
      list_append(list, elem);
      return true;
    }

  if (index > 0)
    {
      for (i=1; i <= index; i++)
        {
          if (i == index)
            {
              new_node->next = temp->next;
              temp->next = new_node;
              return true;
            }
          else
            {
              temp = temp->next;
            }
        }
    }

  if(index < 0)
    {
      pos_i = length + 1 + index;
      value = list_insert(list, pos_i, elem);
      return value;
    }

  else
    {
      return false;
    }
}



bool list_remove(list_t *list, int index, void *elem);


void *list_get(list_t *list, int index)
{
  int length = list_length(list);
  int count = 0;
  node_t *current = list->first;

  if(index == 0)
    {
      return list_first(list);
    }

  if(index == length)
    {
      return list_last(list);
    }

  while(current != NULL)
    {
      if (count == index)
        return current->value;

      current = current->next;
      count++;
    }
  return current->value;
  /*
  if(index < 0 && index < length)
    {
      int pos_i = length + 1 + index;
      void *elem = list_get(list, pos_i);
      return elem;
    }
  */
}

void *list_first(list_t *list)
{
  node_t *cursor = list->first;

  if (cursor == NULL)
    {
      return NULL;
    }

  else 
    {
      return cursor->value;
    }
}

void *list_last(list_t *list)
{
  node_t *cursor = list->last;

  if (cursor == NULL)
    {
      return NULL;
    }
  
  else
    return cursor -> value;
    
}

int list_length(list_t *list)
{
  int length = 0;
  node_t *current = list->first;
  
  if (current == NULL)
    {
      length = 0;
      return length;
    }

  else
    {
      while(current != NULL)
        {
          ++length;
          current = current->next;
        }
      return length;
    }
}





 

int main()
{
  list_t *list = list_new();
  
  char *string = strdup("Aha");

  list_append(list, string);

  char *get = list_get(list, 0);

  printf("%s\n", get);

 // free(string);
 

  int *i0 = calloc(1, sizeof(int));
  *i0 = 2;
  list_prepend(list, i0);

  int *i1 = calloc(1, sizeof(int));
  *i1 = 10;
  list_append(list, i1);

  int *i2 = calloc(1, sizeof(int));
  *i2 = 11;

  bool tellme = list_insert(list, -1, i2);
  printf("insert true if 1 =  %d\n", tellme); //prints 1 if ture

  int *i3 = calloc(1, sizeof(int));
  *i3 = 5;
  list_append(list, i3);

  int *i4 = calloc(1, sizeof(int));
  *i4 = 7;
  list_append(list, i4);

  int *i5 = calloc(1, sizeof(int));
  *i5 = 1;
  list_prepend(list, i5);

  // våran list = [1, 2, Aha,  10, 11, 5, 7]
  
  int *r0 = list_get(list, 0);
  printf("%d\n", *r0);

  int *r1 = list_get(list, 1);
  printf("%d\n", *r1);

  int *r2 = list_get(list, 2);
  printf("%d\n", *r2);

  int *r3 = list_get(list, 3);
  printf("%d\n", *r3);

  int *r4 = list_get(list, 4);
  printf("%d\n", *r4);

  int *r5 = list_get(list, 5);
  printf("%d\n", *r5);

  int *r6 = list_get(list, 6);
  printf("%d\n", *r6);

  printf("listan ska vara 1, 2, weird number for string Aha, 10, 11, 5, 7\n");
  
  
  int size;
  size = list_length(list);
  printf("length är 7. return %d\n", size);

  
  

  
  
  return 0;
}

