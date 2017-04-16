# include "list.h"


typedef struct link link_t;

struct link
{                 
  void *value;
  link_t *next;    
};

struct list{             

  link_t *first;
  link_t *last;
};


link_t *link_new(void *value, link_t *next)
{
  link_t *link = calloc(1, sizeof(link_t));
  if (link == NULL)
    {
      printf("The link is empty\n");
      return NULL;
    }
  else
    {
      link->value = value;
      link->next = next;
    }
  return link;
}

void link_free(link_t *link)
{
  free(link);
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

void list_free(list_t *list)
{
  link_t *current = list->first;
  link_t *prev = current;
  while(current != NULL)
    {
      current = current->next;
      link_free(prev);
      prev = current;
    }
  free(list);
}

void list_append(list_t *list, void *elem)
{
  link_t *append_link = link_new(elem, NULL);
  
  if(list->first == NULL)
    {
      list->first = list->last = append_link;
    }
  else
    {
      list->last->next = append_link;
      list->last = append_link;
    }
}

void list_prepend(list_t *list, void *elem)
{
  link_t *prepend_link = link_new(elem, list->first);

  if (list->first == NULL)
    {
      list->first = list->last = prepend_link;
    }

  else
    {
      list->first = prepend_link;
    }
}

int positive_index (int length, int index)
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
  link_t *new_link = link_new(elem, NULL); // make a new node to be inserted
  link_t *temp = list->first;

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
              new_link->next = temp->next;
              temp->next = new_link;
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

list_t *list_insert2(list_t *list, int index, void *elem)
{
  int pos_i;
  int i;
  int length = list_length(list);
  link_t *new_link = link_new(elem, NULL); // make a new node to be inserted
  link_t *temp = list->first;

  if(index > length)
    {
      printf("Impossible idex\n");
    }

  if (index == 0)
    {
      list_prepend(list, elem);
      return list;
    }

  if (index == length)
    {
      list_append(list, elem);
      return list;
    }

  if (index > 0)
    {
      for (i=1; i <= index; i++)
        {
          if (i == index)
            {
              new_link->next = temp->next;
              temp->next = new_link;
            }
          else
            {
              temp = temp->next;
            }
        }
      return list;
    }

  if(index < 0)
    {
      pos_i = positive_index(length, index);
      list_insert(list, pos_i, elem);
      return list;
    }

  else
    return list;
}


bool is_shelf_taken(char *shelf, list_t *list)
{
    char *temp;
    int length = list_length(list);
    
    for (int i = 0; i < length; i++)
    {
        temp = list_get(list, i);
        if (strcmp(temp, shelf) == 0)
        {
            printf("\n"
                   "%s is already taken\n", shelf);
            return true;
        }
    }
    
    return false;
}



/// Example: (assume l == [43, 44, 42, 45])
///
/// int elem;
/// list_remove(l, 1, &elem);  // l = [43, 42, 45], elem == 44
/// list_remove(l, -1, &elem); // l = [43, 42], elem == 45
/// \param elem a pointer to where the element can be stored

bool list_remove(list_t *list, int index, void **elem)
{
  int length = list_length(list);
  int pos_i;
  link_t *temp;
  
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
      *elem = temp->value;
      link_free(temp);
      return true;
    }
  
  for (int i=0; temp != NULL && i<index-1; i++)
    {
      temp = temp->next;
    }
  link_t *next = temp->next->next;
  *elem = temp->next->value;
  link_free(temp->next);
  temp->next = next;
  return true;
}

void *list_get(list_t *list, int index)
{
  int length = list_length(list);
  int count = 0;
  link_t *current = list->first;

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
}

void *list_first(list_t *list)
{
  link_t *cursor = list->first;

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
  link_t *cursor = list->last;

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
  link_t *current = list->first;
  
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
  link_t *current = list->first;
  
  while (current != NULL)
    {
      printf("%s\n", (char *)current->value);
      current = current->next;
    }
}
/*
list_t *split_list_first_half(list_t *list)
{
	int length = list_length(list);
	int half = length / 2;
	list_t *first_half = list_new();
	void *elem;
	for (int i = 0; i < half; ++i)
	{
		*elem = list_get(list, i);
		list_append(first_half, elem);
	}
	printf("length: %d", list_length(first_half));
	return first_half;
}

list_t *split_list_second_half(list_t *list)
{
	int length = list_length(list);
	int half = length / 2;
	void *elem;
	for (int i = 0; i != half; ++i)
	{
		list_remove(list, 0, &elem);
	}
	printf("length: %d", list_length(list));
	return list;
}


int main()
{
	
  list_t *list = list_new();
  
  char *string = strdup("Aha");

  list_append(list, string);

  char *get = list_get(list, 0);

  printf("%s\n", get);

  
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

  int *insert = calloc(1, sizeof(int));
  *insert = 3;
                       
  list_t *l = list_insert2(list, 0, insert);
  printf("insert true if 1 = %d\n", value);

  int *insert1 = calloc(1, sizeof(int));
  *insert1 = 4;
                       
  list_t *l2 = list_insert2(l, 1, insert1);
  //printf("insert true if 1 = %d\n", value1);

  int *insert2 = calloc(1, sizeof(int));
  *insert2 = 98;
                       
  list_t *l3 = list_insert2(l2, 2, insert2);
  //printf("insert true if 1 = %d\n", value2);
  
  int *i3 = calloc(1, sizeof(int));
  *i3 = 5;
  list_append(l3, i3);

  int *i4 = calloc(1, sizeof(int));
  *i4 = 7;
  list_append(l3, i4);

  int *i5 = calloc(1, sizeof(int));
  *i5 = 1;
  list_prepend(l3, i5);

  // int *i6 = calloc(1, sizeof(int));
  *i6 = 0;
  //bool answer = list_insert(list, -5, i6);
  //printf("insert true if 1 = %d\n", answer);
 
  int *r0 = list_get(l3, 0);
  printf("%d\n", *r0);

  int *r1 = list_get(l3, 1);
  printf("%d\n", *r1);

  int *r2 = list_get(l3, 2);
  printf("%d\n", *r2);

  int *r3 = list_get(l3, 3);
  printf("%d\n", *r3);

  int *r4 = list_get(l3, 4);
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

  //  printf("listan ska vara 1, 2, 10, 5, 7\n");
  
  
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



  


	list_t *test = list_new();
	list_t *test2 = list_new();
	
	int *ett = calloc(1, sizeof(int));
	*ett = 1;
	int *tva = calloc(1, sizeof(int));
	*tva = 2;
	int *tre = calloc(1, sizeof(int));
	*tre = 3;
	int *fyra = calloc(1, sizeof(int));
	*fyra = 4;
	int *fem = calloc(1, sizeof(int));
	*fem = 5;
	list_append(test, ett);
	list_append(test, tva);
	list_append(test, tre);
	list_append(test, fyra);
	list_append(test, fem);
	
	int *ett1 = calloc(1, sizeof(int));
	*ett1 = 1;
	int *tva2 = calloc(1, sizeof(int));
	*tva2 = 2;
	int *tre3 = calloc(1, sizeof(int));
	*tre3 = 3;
	int *fyra4 = calloc(1, sizeof(int));
	*fyra4 = 4;
	int *fem5 = calloc(1, sizeof(int));
	*fem5 = 5;
	list_append(test2, ett1);
	list_append(test2, tva2);
	list_append(test2, tre3);
	list_append(test2, fyra4);
	list_append(test2, fem5);
	
	print_list(test);
	printf("\n\n");
	print_list(split_list_first_half(test));
	printf("\n\n");
	print_list(split_list_second_half(test2));
  
  return 0;
}*/

