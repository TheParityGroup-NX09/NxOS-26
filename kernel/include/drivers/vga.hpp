#ifndef VGA_HPP
#define VGA_HPP

void print(char c, unsigned char color);
void print(char c);

void print(const char* text, unsigned char color);
void print(const char* text);

void print(int num, unsigned char color);
void print(int num);

void print(double num, unsigned char color);
void print(double num);

void printnl(char c, unsigned char color);
void printnl(char c);

void printnl(const char* text, unsigned char color);
void printnl(const char* text);

void printnl(int num, unsigned char color);
void printnl(int num);

void printnl(double num, unsigned char color);
void printnl(double num);

void printnll(char c, unsigned char color);
void printnll(char c);

void printnll(const char* text, unsigned char color);
void printnll(const char* text);

void printnll(int num, unsigned char color);
void printnll(int num);

void printnll(double num, unsigned char color);
void printnll(double num);

void clear_screen();

#endif
