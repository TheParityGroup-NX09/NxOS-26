#include "keyboard.hpp"
#include "io.hpp"
#include "drivers/vga.hpp"
#include "terminal.hpp"

static const char scancode_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};

char get_key()
{
    unsigned char status = inb(0x64);
    if (status & 0x01)
    {
        unsigned char scancode = inb(0x60);
        if (scancode < 128)
        {
            return scancode_map[scancode];
        }
    }
    return 0;
}

void keyboard_handler()
{
    char c = get_key();
    if (c != 0)
    {
        print(c);
    }
}

void read_string(char* buffer, int max_length)
{
    int index = 0;
    while (index < max_length - 1)
    {
        char c = get_key();
        if (c == 0)
        {
            continue;
        }
        if (c == '\n')
        {
            print('\n');
            break;
        }
        if (c == '\b')
        {
            if (index > 0)
            {
                index--;
                if (cursor_row > 0)
                {
                    cursor_row--;
                    volatile char* video_memory = (volatile char*)0xB8000;
                    int video_idx = (cursor_col * 80 + cursor_row) * 2;
                    video_memory[video_idx] = ' ';
                    video_memory[video_idx + 1] = 0x07;
                }
            }
            continue;
        }
        buffer[index] = c;
        print(c);
        index++;
    }
    buffer[index] = '\0';
}