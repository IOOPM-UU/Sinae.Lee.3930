#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

extern char *strdup(const char *);

typedef union {
  int i;
  float f;
  char *s;
} answer_t;

typedef bool(*check_func)(char *);

typedef answer_t(*convert_func)(char *);

extern char *strdup(const char *);

/// calculate length of string
///
/// \param str string
/// \returns: length of string
int string_length(char *str);

/// read a string
///
/// \param buf string buffer
/// \param buf_siz size of the buffer
/// \returns: length of buffer
int read_string(char *buf, int buf_siz);

/// check if it is number or not
///
/// \param str string
/// \returns: true or false
bool is_number(char *str);

/// check if string is empty or not
///
/// \param str string
/// \returns: true or false
bool not_empty(char *str);

/// check if it is char or not
///
/// \param str a string
/// \returns: true or false
bool is_char(char *str);

/// ask question for input
///
/// \param question question with char
/// \returns: input integer
int ask_question_int(char *question);

/// ask a question with char
///
/// \param question question in char
/// \returns: input char
char *ask_question_string(char *question);
//void ask_question_string(char *question, char *buf, int buf_siz);

/// ask question shelf with char
///
/// \param question question in char
/// \returns: input char
char *ask_question_shelf(char *question);

/// clear input
void clear_input_buffer();

/// ask question
///
/// \param question question in char
/// \param check function
/// \param convert function
/// \returns: answer
answer_t ask_question(char *question, check_func check, convert_func convert);

/// check if index is more than 20
///
/// \param length the length of list
/// \param index index of list
/// \returns: true or false
bool is_more_than_20(int length, int index);

/// var den gör
///
/// \param length
/// \param index
/// \return
bool is_more_wt_no_remainder(int length, int index) ;

/// Vad den gör
///
/// \param length
/// \param index
/// \return
bool is_more_wt_remainder(int length, int index) ;

/// Show next page
///
/// \param length length of page
/// \param index index of page
/// \returns: true or false
bool show_next_page(int length, int index);

/// Show previous page
///
/// \param length length of page
/// \param index index of page
/// \returns: true or false
bool show_prev_page(int length, int index);

/// Check if anser is valid or not
///
/// \param answer input answer
/// \param valid_answers valid answer
/// \returns: true or false
bool is_answer (char *answer, char *valid_answers);

///  print menu
void print_menu();

/// print menu for editing item
void print_edit_item_menu();

/// print list menu
///
/// \param show_next true or false
/// \param show_prev true or false
void print_list_menu(bool show_next, bool show_prev);

/// ask question for menu
///
/// \returns: char
char ask_question_menu();

/// ask question for editing menu
///
/// \param question question in char
/// \returns: input in char
char ask_question_edit_menu(char *question);

/// ask question for listing menu
///
/// \param show_next true or false
/// \param show_prev true or false
/// \returns: input in char
char ask_question_list_menu(bool show_next, bool show_prev);

/// print question yes or no
void print_yes_or_no();

/// ask yes or no
///
/// \param question question in char
/// \returns: input answer
char ask_question_yes_no(char *question);

/// question for index
///
/// \param input page input that you want to see
/// \param page total page
/// \returns input
int what_index(int input, int page);

/// check if input is valid or not
///
/// \param input input integer
/// \param length length of index
/// \returns: true or false
bool is_input_valid(int input, int length);

/// ask question about index that you want
///
/// \param question question in char
/// \param length list of length
/// \param page the total page
/// \returns: input index
int ask_question_index (char *question, int length, int page);


  
#endif
