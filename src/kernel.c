#include "kernel.h"
#include <stdint.h>
#include <stddef.h>

uint16_t *video_mem = 0;
uint16_t terminal_row;
uint16_t terminal_col;

uint16_t terminal_make_char (char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_put_char (int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char (c, colour);
}

void terminal_write_char (char c, char colour) 
{
    terminal_put_char(terminal_col, terminal_row, c, colour);
    terminal_col++;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row++;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*) (0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y<VGA_HEIGHT; y++) {
        for (int x = 0; x<VGA_WIDTH; x++) {
            terminal_put_char(x, y, ' ', 0);
        }
    }
}

size_t strlen(const char* str) 
{
    size_t len=0;
    while (str[len])
    {
        len++;
    }
    return len;
}

void print(const char *str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_write_char(str[i], 15);
    }
}
void kernel_main()
{
    
    terminal_initialize();
    print("Hello World!");
}