#ifndef HEADERS_H // во избежание дублирования кода
#define HEADERS_H

int find_needed_bracket (int start, int end, char* list_for_find, char bracket, char symbol);

int element(int l_st_number, int l_end_number, char* line, int depth);       

int text_with_brackets(int l_st_number, int l_end_number, char* line, int depth);

int reading_file(string FileName, char* Array);

#endif