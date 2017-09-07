#include "kprintf.h"

void simple_example()
{
    char * foo = "Test pointer for address";
    kprintf("String, %s!\nDecimal %d\nAddress %x\nChar %c\n", "Test", 9, &foo, 'a');
}

int main(int argc, char** argv)
{
    simple_example();
    return 0;
}
