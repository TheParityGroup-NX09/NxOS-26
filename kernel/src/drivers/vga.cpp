#include "vga.hpp"
#include "terminal.hpp"

unsigned char VGA_BLACK = 0x0;
unsigned char VGA_BLUE = 0x1;
unsigned char VGA_GREEN = 0x2;
unsigned char VGA_RED = 0x4;
unsigned char VGA_YELLOW = 0xE;
unsigned char VGA_PINK = 0xD;
unsigned char VGA_WHITE = 0x7;
unsigned char VGA_GREY = 0x8;

unsigned char defaultCOLOR = 0x7;

void clear_screen()
{
    volatile char* video_memory = (volatile char*)0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2)
    {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    cursor_row = 0;
    cursor_col = 0;
}

void print(char c, unsigned char color)
{
    volatile char* video_memory = (volatile char*)0xB8000;
    
    if (c == '\n')
    {
        cursor_row = 0;
        cursor_col++;
    }
    else
    {
        int index = (cursor_col * 80 + cursor_row) * 2;
        video_memory[index] = c;
        video_memory[index + 1] = color;
        cursor_row++;
    }

    if (cursor_row >= 80)
    {
        cursor_row = 0;
        cursor_col++;
    }
}

void print(char c)
{
    print(c, defaultCOLOR);
}

void print(const char* text, unsigned char color)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        print(text[i], color);
    }
}

void print(const char* text)
{
    print(text, defaultCOLOR);
}

void print(int num, unsigned char color)
{
    char buf[32];
    int i = 0;

    if (num == 0)
    {
        print('0', color);
        return;
    }

    if (num < 0)
    {
        print('-', color);
        num = -num;
    }

    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        print(buf[j], color);
    }
}

void print(int num)
{
    print(num, defaultCOLOR);
}

void print(double num, unsigned char color)
{
    if (num < 0.0)
    {
        print('-', color);
        num = -num;
    }

    int ipart = (int)num;
    print(ipart, color);
    print('.', color);

    double fpart = num - (double)ipart;
    for (int i = 0; i < 4; i++)
    {
        fpart *= 10.0;
        int digit = (int)fpart;
        print((char)(digit + '0'), color);
        fpart -= digit;
    }
}

void print(double num)
{
    print(num, defaultCOLOR);
}

void printnl(char c, unsigned char color)
{
    print(c, color);
    print('\n', color);
}

void printnl(char c)
{
    printnl(c, defaultCOLOR);
}

void printnl(const char* text, unsigned char color)
{
    print(text, color);
    print('\n', color);
}

void printnl(const char* text)
{
    printnl(text, defaultCOLOR);
}

void printnl(int num, unsigned char color)
{
    print(num, color);
    print('\n', color);
}

void printnl(int num)
{
    printnl(num, defaultCOLOR);
}

void printnl(double num, unsigned char color)
{
    print(num, color);
    print('\n', color);
}

void printnl(double num)
{
    printnl(num, defaultCOLOR);
}

void printnll(char c, unsigned char color)
{
    print('\n', color);
    print(c, color);
}

void printnll(char c)
{
    printnll(c, defaultCOLOR);
}

void printnll(const char* text, unsigned char color)
{
    print('\n', color);
    print(text, color);
}

void printnll(const char* text)
{
    printnll(text, defaultCOLOR);
}

void printnll(int num, unsigned char color)
{
    print('\n', color);
    print(num, color);
}

void printnll(int num)
{
    printnll(num, defaultCOLOR);
}

void printnll(double num, unsigned char color)
{
    print('\n', color);
    print(num, color);
}

void printnll(double num)
{
    printnll(num, defaultCOLOR);
}
