#include <stdio.h>
#include <stdarg.h>

int strlen(char * string)
{
    int count = 0;
    while(string[count] != '\0')
    {
        count++;
    }
    return count;
}


// Shamelessly stolen
char * itoa(int value, char * result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0'; return result;
    }

    char * ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0)
    {
        *ptr++ = '-';
    }

    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    return result;
}

int count_variables(char * string)
{
    int count = 0;
    int length = strlen(string);
    for(int i = 0; i < length; i++)
    {
        if(string[i] == '%' && i != length)
        {
            char next = string[i + 1];
            switch(next)
            {
                case 's':
                case 'd':
                case 'c':
                case 'x':
                    count++;
                    break;
                default:
                    break;
            }
        }
    }
    return count;
}

void print_string(char * string)
{
    while(*string != '\0')
    {
        putc(*string, stdout);
        string++;
    }
}

void print_decimal(int decimal)
{
    char string[sizeof(int) + 1] = {0};
    itoa(decimal, string, 10);
    print_string(string);
}

void print_address(int address)
{
    char number[sizeof(int) + 1] = {0};
    itoa(address, number, 16);

    // TODO: This is dumb. We should be better than this.
    char string[(sizeof(int) + 1) + 2] = {0};
    string[0] = '0';
    string[1] = 'x';
    for(int i = 0; i < strlen(number); i++)
    {
        string[i + 2] = number[i];
    }
    print_string(string);
}

void kprintf(char * string, ...)
{
    va_list valist;
    va_start(valist, string);

    int count = count_variables(string);
    int length = strlen(string);

    for(int i = 0; i < length; i++)
    {
        if(string[i] == '%' && i != length)
        {
            char next = string[i + 1];
            switch(next)
            {
                case 's':
                    print_string(va_arg(valist, char *));
                    i++;
                    break;
                case 'd':
                    print_decimal(va_arg(valist, int));
                    i++;
                    break;
                case 'x':
                    print_address(va_arg(valist, int));
                    i++;
                    break;
                case 'c':
                    // NOTE: GCC was bitching about this being a 'char' type, so just
                    // make it an int to shut GCC up.
                    putc(va_arg(valist, int), stdout);
                    i++;
                    break;
                default:
                    break;
            }
        }
        else
        {
            putc(string[i], stdout);
        }
    }
    va_end(valist);
}
