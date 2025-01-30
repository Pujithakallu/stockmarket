// 2.) Design a State Pattern to model a Traffic Light System in C++.
// • The traffic light transitions between states (Red, Green, Yellow) based on timers.
// • Each state should define its behavior, including the next state and its duration.
// • Write a simulation program to demonstrate the transitions over time.


#include <iostream>
#include <thread>
#include <chrono>

class TrafficLightState {
public:
    virtual void handle() = 0;
    virtual ~TrafficLightState() = default;
};

class TrafficLightContext {
    TrafficLightState* state;
public:
    TrafficLightContext(TrafficLightState* initialState) : state(initialState) {}
    
    void setState(TrafficLightState* newState) {
        state = newState;
    }
    
    void changeState() {
        state->handle();
    }
};

class RedState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Red Light: Stop!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); 
    }
};

class GreenState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Green Light: Go!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); 
    }
};

class YellowState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Yellow Light: Caution!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); 
    }
};

int main() {
    RedState red;
    GreenState green;
    YellowState yellow;

    TrafficLightContext lightContext(&red);

    // traffic light cycle
    for (int i = 0; i < 3; ++i) {
        lightContext.changeState();  // Red
        lightContext.setState(&green);
        lightContext.changeState();  // Green
        lightContext.setState(&yellow);
        lightContext.changeState();  // Yellow
        lightContext.setState(&red);
    }

    return 0;
}

