#include "CTurtle.hpp"
#include <iostream>
#include <vector>

namespace ct = cturtle;

int main(){
    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);

    turtle.speed(ct::TS_SLOWEST);

    std::vector<int> actions;

    actions.push_back(0);

    for (int i = 0; i < 15; i++) {
        
        for (int action : actions) {
            
            if (action == 0) {
                turtle.forward(100);
            } else if (action == 1) {
                turtle.right(90);
            } else if (action == 2) {
                turtle.left(90);
            }
        }
        std::cout << i << std::endl;
        
        actions.push_back(1);
    }

    std::getchar();

    scr.bye();
    return 0;
}