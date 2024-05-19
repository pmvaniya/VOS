#include "include/vga.h"
#include "include/stdint.h"

uint16 column = 0, line = 0;
uint16 *const vga = (uint16 *const)0xB8000;
const uint16 defaultColor = (COLOR_LIGHT_GREY << 8) | (COLOR_BLACK << 12);
uint16 currentColor = defaultColor;

void ResetVGA()
{
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for (uint16 y = 0; y < height; y++)
    {
        for (uint16 x = 0; x < width; x++)
        {
            vga[y * width + x] = ' ' | defaultColor;
        }
    }
}

void newLine()
{
    if (line < height - 1)
    {
        line++;
        column = 0;
    }
    else
    {
        scrollUp();
        column = 0;
    }
}

void scrollUp()
{
    for (uint16 y = 0; y < height; y++)
    {
        for (uint16 x = 0; x < width; x++)
        {
            vga[(y - 1) * width + x] = vga[y * width + x];
        }
    }

    for (uint16 x = 0; x < width; x++)
    {
        vga[(height - 1) * width + x] = ' ' | currentColor;
    }
}

void print(const char *s)
{
    while (*s)
    {
        switch (*s)
        {
        case '\n':
            newLine();
            break;

        case '\r':
            column = 0;
            break;

        case '\t':
            if (column == width)
            {
                newLine();
            }
            uint16 tabLen = 4 - (column % 4);
            while (tabLen != 0)
            {
                vga[line * width + (column++)] = ' ' | currentColor;
                tabLen--;
            }
            break;

        default:
            if (column == width)
            {
                newLine();
            }

            vga[line * width + (column++)] = *s | currentColor;
            break;
        }

        s++;
    }
}

void printd(int num)
{
    int pos = 0, rem = 0;
    char str[16];

    while (num > 0)
    {
        switch (num % 10)
        {
        case 0:
            str[pos] = '0';
            break;

        case 1:
            str[pos] = '1';
            break;

        case 2:
            str[pos] = '2';
            break;

        case 3:
            str[pos] = '3';
            break;

        case 4:
            str[pos] = '4';
            break;

        case 5:
            str[pos] = '5';
            break;

        case 6:
            str[pos] = '6';
            break;

        case 7:
            str[pos] = '7';
            break;

        case 8:
            str[pos] = '8';
            break;

        case 9:
            str[pos] = '9';
            break;

        default:
            break;
        }

        num = num / 10;
        pos++;
    }

    str[pos] = '\0';

    while (pos >= 0)
    {
        putc(str[pos]);
        pos--;
    }
}

void putc(char c)
{
    char str[] = {c, '\0'};
    print(str);
}
