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

void list_free(list_t *list);

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

int positive_index (int length, int index) // not in file.h yet
{
  int pos_i = length + 1 + index;
  while (pos_i < 0)
    {
      pos_i = length + 1 + pos_i;
    }
  return pos_i;
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
      pos_i = positive_index(length, index);
      value = list_insert(list, pos_i, elem);
      return value;
    }

  else
    {
      return false;
    }
}

/// Example: (assume l == [43, 44, 42, 45])
///
/// int elem;
/// list_remove(l, 1, &elem);  // l = [43, 42, 45], elem == 44
/// list_remove(l, -1, &elem); // l = [43, 42], elem == 45
/// \param elem a pointer to where the element can be stored

bool list_remove(list_t *list, int index, void *elem)
{
  int length = list_length(list);
  int pos_i;
  node_t *temp;
  
  if(list->first == NULL)
    {
      printf("list is empty\n");
      return true;
    }

  if(index >= length)
    {
      printf("Error, index is greater than length of list\n");
      return false;
    }

  if (index < 0)
    {
      pos_i = length + 1 + index;
      bool is_true = list_remove(list, pos_i, elem);
      return is_true;
    }

  //http://quiz.geeksforgeeks.org/delete-a-linked-list-node-at-a-given-position/
  temp = list->first;
  if (index == 0)   //deleting first node
    {
      list->first = temp->next;
      elem = temp->value;
      node_free(temp);
      return true;
    }
  
  for (int i=0; temp !=NULL && i<index-1; i++)
    {
      temp = temp->next;
    }
  node_t *next = temp->next->next;
  elem = temp->next->value;
  node_free(temp->next);
  temp->next = next;
  return true;
}


void list_free(list_t *list)
{
  node_t *current = list->first;
  node_t *prev = current;
  while(current != NULL)
    {
      current = current->next;
      node_free(prev);
      prev = current;
    }
  free(list);
}

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

//http://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
  while(current != NULL)   
    {
      if (count == index)
        return current->value;

      current = current->next;
      count++;
    }
  return current->value;
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


void print_list(list_t *list)
{
  node_t *current = list->first;
  
  while (current != NULL)
    {
      printf("each element: %d\n", *(int *)current->value);
      current = current->next;
    }
}

int main()
{
  list_t *list = list_new();
  /*
  char *string = strdup("Aha");

  list_append(list, string);

  char *get = list_get(list, 0);

  printf("%s\n", get);

  */

  int *i0 = calloc(1, sizeof(int));
  *i0 = 2;
  list_prepend(list, i0);

  int *i1 = calloc(1, sizeof(int));
  *i1 = 10;
  list_append(list, i1);

  //  int *i2 = calloc(1, sizeof(int));
  //*i2 = 11;

  // bool tellme = list_insert(list, -1, i2);
  //printf("insert true if 1 =  %d\n", tellme); //prints 1 if ture

  // int *insert = calloc(1, sizeof(int));
  //*insert = 3;
                       
  // bool value = list_insert(list, 0, insert);
  //printf("insert true if 1 = %d\n", value);

  // int *insert1 = calloc(1, sizeof(int));
  // *insert1 = 4;
                       
  // bool value1 = list_insert(list, 1, insert1);
  //printf("insert true if 1 = %d\n", value1);

  // int *insert2 = calloc(1, sizeof(int));
  //*insert2 = 98;
                       
  // bool value2 = list_insert(list, 5, insert2);
  //printf("insert true if 1 = %d\n", value2);
  
  int *i3 = calloc(1, sizeof(int));
  *i3 = 5;
  list_append(list, i3);

  int *i4 = calloc(1, sizeof(int));
  *i4 = 7;
  list_append(list, i4);

  int *i5 = calloc(1, sizeof(int));
  *i5 = 1;
  list_prepend(list, i5);

  // int *i6 = calloc(1, sizeof(int));
  //*i6 = 0;
  //bool answer = list_insert(list, -5, i6);
  //printf("insert true if 1 = %d\n", answer);
 
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

  // int *r5 = list_get(list, 5);
  // printf("%d\n", *r5);

  //int *r6 = list_get(list, 6);
  // printf("%d\n", *r6);

  //int *r7 = list_get(list, 7);
  //printf("%d\n", *r7);

  //  int *r8 = list_get(list, 8);
  // printf("%d\n", *r8);

  //int *r9 = list_get(list, 9);
  // printf("%d\n", *r9);

 

  

  
  

  printf("listan ska vara 1, 2, 10, 5, 7\n");
  
  
  int size;
  size = list_length(list);
  printf("length är %d\n", size);

  void *elem;
  list_remove(list, -2, &elem);
  list_remove(list, 1, &elem);
  list_remove(list, 2, &elem);
  list_remove(list, 0, &elem);
  
  print_list(list);
   
  
  list_free(list);



  

  
  return 0;
}

