#include <iostream>
#include <string>

int main()
{
    int count = 4;
    std::string* stringArray = new std::string[count];
    for (int i = 0; i < count; i++)
    {
        std::cin >> stringArray[i];
    }

    for (int i = 0; i < count; i++)
    {
        std::cout << "stringArray[" << i << "] = " << stringArray[i] << std::endl;
    }

    delete [] stringArray;
    return 0;
}