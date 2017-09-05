#include "kprintf.h"

void simple_example()
{
    kprintf("Hello, %s!\nForest eats %d hamburgers a day.\n", "Test", 9);
}

int main(int argc, char** argv)
{
    simple_example();
    return 0;
}
