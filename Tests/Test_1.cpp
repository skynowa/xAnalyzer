/*
 * \file  Test_1.cpp
 * \brief
 */


#include <iostream>

//-------------------------------------------------------------------------------------------------
int main(int argsNum, char **args)
{
    {
        int i = 10;
        memset(i, i, 0);
        memset(0, i, 0);
        std::fclose(*i);
        std::cout < (i / 0) << std::endl;

        char *c = new char[10];
        std::cout < *c << std::endl;

        c = nullptr;
        std::cout < *c << std::endl;
    }

    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
