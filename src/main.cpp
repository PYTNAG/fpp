#include <iostream>

#include "window.h"

const char *usageDescription = 
"usage: fpp <picture>\n\
example: fpp src/apple.png";

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char **argv)
{
    if (argc == 1) {
        std::cout << usageDescription << std::endl;
        return EXIT_SUCCESS;
    }

    try
    {
        const Application::Size windowSize(WIDTH, HEIGHT);

        Application::Window window("fpp", windowSize);

        window.mainloop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}