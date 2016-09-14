#ifndef _UTILS_H_
#define _UTILS_H_

extern char *strdup(const char *);

typedef union {
  int i;
  float f;
  char *s;
} answer_t;

typedef bool(*check_func)(char *);

typedef answer_t(*convert_func)(char *);

int read_string(char *buf, int buf_siz);

bool is_number(char *str);

bool not_empty(char *str);

bool is_char(char *str);

int ask_question_int(char *question);

char *ask_question_string(char *question);
//void ask_question_string(char *question, char *buf, int buf_siz);

char *ask_question_shelf(char *question);

void clear_input_buffer();

answer_t ask_question(char *question, check_func check, convert_func convert);

  
#endif
