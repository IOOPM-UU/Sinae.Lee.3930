#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "list.h"


int init_suite_list(void)
{
  return 0;
}

int clean_suite_list(void)
{
  return 0;
}

void test_list_new(void)
{
  list_t *list = list_new();
  CU_ASSERT_FATAL(list != NULL);
  list_free(list);
}

void test_list_append(void)
{
  list_t *list = list_new();
  CU_ASSERT(list_length(list) == 0);
  list_append(list, "1");
  CU_ASSERT(list_length(list) == 1);
  list_append(list, "2");
  CU_ASSERT(list_length(list) == 2);
  list_free(list);
}

void test_list_prepend(void)
{
  list_t *list = list_new();
  CU_ASSERT(list_length(list) == 0);
  list_prepend(list, "A");
  CU_ASSERT(list_length(list) == 1);
  list_prepend(list, "B");
  CU_ASSERT(list_length(list) == 2);
  list_free(list);
}

// failed on purpose
void test_list_insert(void)
{
  list_t *list = list_new();
  list_insert(list, 0, "0");
  list_insert(list, 1, "1");
  list_insert(list, 2, "2");
  CU_ASSERT(list_insert(list, 2, "5") == true);
  CU_ASSERT(list_insert(list, 10, "4") == true);
  CU_ASSERT(list_insert(list, 3, "") == true);
  list_free(list);
}

// error on purpose
// failed on purpose
void test_list_remove(void)
{
  list_t *list = list_new();
  char *value;
  list_insert(list, 0, "0");
  list_insert(list, 1, "1");
  list_insert(list, 2, "2");
  list_insert(list, 3, "3");
  list_insert(list, 4, "4");
 
  CU_ASSERT_FALSE(list_remove(list, 10, (void **) &value));
  CU_ASSERT(list_remove(list, 1, (void **) &value));
  CU_ASSERT(strcmp(value, "1") == 0);

  CU_ASSERT(list_remove(list, 0, (void **) &value));
  CU_ASSERT(strcmp(value, "0") == 0);

  CU_ASSERT(list_remove(list, 2, (void **) &value));
  CU_ASSERT(strcmp(value, "2") == 0);

  CU_ASSERT(list_remove(list, -1, (void **) &value));
  CU_ASSERT(strcmp(value, "1") == 0);

  CU_ASSERT(list_remove(list, -1, (void **) &value));
  CU_ASSERT(strcmp(value, "4") == 0);

  list_free(list);
}

void test_list_get(void)
{
  list_t *list = list_new();
  list_append(list, "0");
  list_append(list, "1");
  list_append(list, "2");
  CU_ASSERT(strcmp(list_get(list, 0), "0") == 0);
  list_append(list, "3");
  //CU_ASSERT(list_get(list, 10) == NULL);  
  //CU_ASSERT(strcmp(list_get(list, -1), "3") == 0);
  // Cause seg fault on purpose
  CU_ASSERT(strcmp(list_get(list, 2), "2") == 0);
  
  list_free(list);
}

void test_list_first(void)
{
  list_t *list = list_new();
  CU_ASSERT(list_first(list) == NULL);
  list_append(list, "Holy Cow");
  CU_ASSERT(strcmp(list_first(list), "Holy Cow") == 0);
  list_append(list, "1");
  list_append(list, "Ohlala");
  CU_ASSERT(strcmp(list_first(list), "Holy Cow") == 0);
  list_free(list);
}

void test_list_last(void)
{
  list_t *list = list_new();
  CU_ASSERT(list_last(list) == NULL);
  list_append(list, "Spring roll");
  CU_ASSERT(strcmp(list_last(list), "Spring roll") == 0);
  list_append(list, "soy sauce");
  list_append(list, "toodeloo");
  CU_ASSERT(strcmp(list_last(list), "toodeloo") == 0);
  list_free(list);
}

void test_list_length(void)
{
  list_t *list = list_new();
  CU_ASSERT(list_length(list) == 0);
  list_append(list, "Spring roll");
  CU_ASSERT(list_length(list) == 1);
  list_append(list, "Noodle");
  list_append(list, "Spicy");
  CU_ASSERT(list_length(list) == 3);
  list_free(list);  
}

int main()
{
  CU_pSuite pSuiteList = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
      
  pSuiteList = CU_add_suite ("Linked list Suite", init_suite_list, clean_suite_list);
  if(NULL == pSuiteList)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(
    (NULL == CU_add_test(pSuiteList, "list_new()", test_list_new)) ||
    (NULL == CU_add_test(pSuiteList, "list_append", test_list_append)) ||
    (NULL == CU_add_test(pSuiteList, "list_prepend", test_list_prepend)) ||
    (NULL == CU_add_test(pSuiteList, "list_insert", test_list_insert)) ||
    (NULL == CU_add_test(pSuiteList, "list_remove", test_list_remove)) ||
    (NULL == CU_add_test(pSuiteList, "list_get", test_list_get)) ||
    (NULL == CU_add_test(pSuiteList, "list_first", test_list_first)) ||
    (NULL == CU_add_test(pSuiteList, "list_last", test_list_last)) ||
    (NULL == CU_add_test(pSuiteList, "list_length", test_list_length))
     )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
      
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
