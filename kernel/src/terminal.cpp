#include "terminal.hpp"
#include "drivers/vga.hpp"
#include "keyboard.hpp"
#include "utils.hpp"

int cursor_row = 0;
int cursor_col = 0;

const char* commandsList[] = {"help", "calculator", "version"};

void startUserUI()
{
    print(">");
}

void startShell()
{
    char command_buffer[64];
    while (true)
    {
        startUserUI();
        
        print(">");
        
        read_string(command_buffer, sizeof(command_buffer));
        if (stringEquals(command_buffer, "help"))
        {
            print("commands: ");
            for (int i=0;i < sizeof(commandsList);i++)
            {
                print(commandsList[i]);
            }
        }
    }
}