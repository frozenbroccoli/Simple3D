#include <iostream>
#include <stdexcept>
#include <conio.h>
#include "Rendering/Screen.h"


int main() {
    try {
        Screen screen {200, 200};
        Color red {255, 0, 0};
        Color green {0, 255, 0};
        Color blue {0, 0, 255};
        screen.clear();
        screen.display();
        for (int i = 0; i < 100; i++) {
            screen.set_pixel(i, i, red);
            screen.set_pixel(i, 100 - i, green);
            screen.set_pixel(50, i, blue);
        }
        screen.display();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    std::cout << "Press any key to proceed..." << std::endl;
    _getch();
}
