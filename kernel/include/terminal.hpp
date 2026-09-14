#ifndef TERMINAL_HPP
#define TERMINAL_HPP

extern int cursor_row;
extern int cursor_col;

void print(char c);
void print(const char* text);
void print(int num);
void print(double num);
void printnl(const char* text);
void read_string(char* buffer, int max_length);

#endif
