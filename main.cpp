#include "CTurtle.hpp"
#include <iostream>
#include <vector>

namespace ct = cturtle;

void perform_actions (ct::Turtle& turtle, std::vector<int> actions) {
    // do all actions in the vector
    for (int action : actions) {
        if (action == 0) {
            turtle.forward(10);
        } else if (action == 1) {
            turtle.right(90);
        } else if (action == 2) {
            turtle.left(90);
        } else if (action == 3) {
            turtle.right(180);
        } else {
            std::cout << "Action: " << action << std::endl;
            throw std::runtime_error("Error: unknown action");
        }
    }
}

int select_transition (int heading) {
    if (heading == 0) {
        return 1; // facing right
    } else if (heading == 270) {
        return -1; // nothing // facing down
    } else if (heading == 180) {
        return 2; // facing left
    } else if (heading == 90) {
        return 3; // facing up
    } else {
        std::cout << "Heading: " << heading << std::endl;
        throw std::runtime_error("Error: unknown heading");
    }
}

int main(){
    // initialize stuff
    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);
    int heading;
    int next_transition;

    turtle.speed(ct::TS_SLOWEST);

    // this vector will contain all turtle actions
    std::vector<int> actions;

    // initial action and transition
    actions = {0};
    next_transition = 1;
    perform_actions(turtle, actions);

    // loop to draw the fractal
    for (int i = 0; i < 15; i++) {
        // point the turtle downwards
        turtle.setheading(270);

        // perform the recorded actions
        perform_actions(turtle, actions);

        // update the actions by doubling with the correct transition
        std::vector<int> new_actions;
        new_actions.reserve(actions.size() * 2 + 1);

        new_actions.insert(new_actions.end(), actions.begin(), actions.end());
        heading = static_cast<int>(turtle.heading()) % 360;
        if (heading < 0) {
            heading += 360;
        }
        if (next_transition != -1) {
            new_actions.push_back(next_transition);
        }
        next_transition = select_transition(heading);
        new_actions.insert(new_actions.end(), actions.begin(), actions.end());

        actions = new_actions;

        // print the current itearation
        std::cout << "Iteration: " << i << std::endl;
        
        // debug
        if (false) {
            std::cout << "Actions: ";
            for (int action : actions) {
                std::cout << action << " ";
            }
            std::cout << "Heading: " << heading << std::endl;
            std::getchar();
        }
    }

    // wait for user input so the image is not closed
    std::getchar();

    // close the turtle graphics window
    scr.bye();

    return 0;
}