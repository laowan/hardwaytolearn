#include <iostream>

int main()
{
    char ch = 0;
    for (int i = 0; i < 256; i++)
    {
        std::cout << char(ch + i) << "  ";
        std::cout << std::dec << int(ch + i) << "  ";
        std::cout << std::hex << int(ch + i) << std::endl;
    }
}