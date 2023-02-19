#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char color)
{
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color)
{
    video_mem[y * VGA_WIDTH + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color)
{
    if (c == '\n')
    {
        terminal_row++;
        terminal_col = 0;
        return;
    }
    
    terminal_putchar(terminal_col, terminal_row, c, color);

    terminal_col++;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row++;
    }
    
}

void terminal_initialize()
{
    video_mem = (uint16_t*) 0xB8000;

    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            // video_mem[i * VGA_WIDTH + j] = terminal_make_char(' ', 0);
            terminal_putchar(j, i, ' ', 0);
        }
    }
    
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }
    return len;
}

void print(const char* str)
{
    // for (size_t i = 0; i < strlen(str); i++) // 这句会导致打印很多行同样的字符串,目前不知原因
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
    // char* p = (char*) str;
    // while(p)
    // {
    //     terminal_writechar(*p, 15);
    //     p++;
    // }
}

extern void problem();

void kernel_main()
{
    // char* video_mem = (char*)(0xB8000);
    // video_mem[0] = 'A';
    // video_mem[1] = 3;
    // video_mem[2] = 'C';
    // video_mem[3] = 4;

    // uint16_t* video_mem = (uint16_t*)(0xB8000);
    // video_mem[0] = 0x0341; // little endian

    // video_mem[0] = terminal_make_char('A', 3);

    terminal_initialize();
    // video_mem[0] = terminal_make_char('A', 15);
   
    // terminal_writechar('A', 15);
    // terminal_writechar('B', 15);
    print("Hello World\nThis is a KimOS kernel!");

    initialize_idt();
    //enable the system interrupts
    enable_interrupt();

    // problem();

    // outb(0x60, 0xff);
}

