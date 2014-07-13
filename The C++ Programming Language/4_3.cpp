#include <iostream>

enum E
{
    E_ONE,
    E_TWO,
    E_THREE
};

int main()
{
    std::cout << "bool " << sizeof(bool) << std::endl;
    std::cout << "char " << sizeof(char) << std::endl;
    std::cout << "int " << sizeof(int) << std::endl;
    std::cout << "short int " << sizeof(short int) << std::endl;
    std::cout << "long int " << sizeof(long int) << std::endl;
    std::cout << "float " << sizeof(float) << std::endl;
    std::cout << "double " << sizeof(double) << std::endl;
    std::cout << "long double " << sizeof(long double) << std::endl;
    std::cout << "enum E " << sizeof(E) << std::endl;
}