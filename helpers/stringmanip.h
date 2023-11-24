#ifndef STRINGMANIP_H
#define STRINGMANIP_H

char** str_split(char *str, char splitBy);

int str_length(const char *str);

int str_array_count(char **arr);

int str_cmp(char *str, char *cmpStr);

int str_to_int(char *str, int *result);

#endif
