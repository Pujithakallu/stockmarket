#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <chrono>
#include <iomanip>
#include <sstream>

// Forward declarations
class Command;

// Utility function to get current timestamp
/*std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}*/

// Device base class
class Device {
public:
    explicit Device(std::string name) : name(std::move(name)), isOn(false) {}
    virtual ~Device() = default;

    virtual void turnOn() {
        isOn = true;
        std::cout << " - " << name << " turned ON" << std::endl;
    }

    virtual void turnOff() {
        isOn = false;
        std::cout << " - " << name << " turned OFF" << std::endl;
    }

    bool getState() const { return isOn; }
    const std::string& getName() const { return name; }

protected:
    std::string name;
    bool isOn;
};

// Concrete devices
class Light : public Device {
public:
    explicit Light(const std::string& name) : Device(name), brightness(0) {}

    void turnOn() override {
        Device::turnOn();
        brightness = 100;
        std::cout << "Brightness set to " << brightness << "%" << std::endl;
    }

    void turnOff() override {
        Device::turnOff();
        brightness = 0;
        std::cout << "Brightness set to " << brightness << "%" << std::endl;
    }

    void setBrightness(int level) {
        brightness = level;
        std::cout << " - " << name 
                  << " brightness set to " << brightness << "%" << std::endl;
    }

private:
    int brightness;
};

class Fan : public Device {
public:
    explicit Fan(const std::string& name) : Device(name), speed(0) {}

    void turnOn() override {
        Device::turnOn();
        speed = 1;
        std::cout << "Speed set to " << speed << std::endl;
    }

    void turnOff() override {
        Device::turnOff();
        speed = 0;
        std::cout << "Speed set to " << speed << std::endl;
    }

    void setSpeed(int newSpeed) {
        speed = newSpeed;
        std::cout<< " - " << name 
                  << " speed set to " << speed << std::endl;
    }

private:
    int speed;
};

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getDescription() const = 0;
};

// Concrete commands for Light
class LightOnCommand : public Command {
public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->turnOn();
    }

    void undo() override {
        light->turnOff();
    }

    std::string getDescription() const override {
        return "Turn on " + light->getName();
    }

private:
    std::shared_ptr<Light> light;
};

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->turnOff();
    }

    void undo() override {
        light->turnOn();
    }

    std::string getDescription() const override {
        return "Turn off " + light->getName();
    }

private:
    std::shared_ptr<Light> light;
};

// Concrete commands for Fan
class FanOnCommand : public Command {
public:
    explicit FanOnCommand(std::shared_ptr<Fan> fan) : fan(std::move(fan)) {}

    void execute() override {
        fan->turnOn();
    }

    void undo() override {
        fan->turnOff();
    }

    std::string getDescription() const override {
        return "Turn on " + fan->getName();
    }

private:
    std::shared_ptr<Fan> fan;
};

class FanOffCommand : public Command {
public:
    explicit FanOffCommand(std::shared_ptr<Fan> fan) : fan(std::move(fan)) {}

    void execute() override {
        fan->turnOff();
    }

    void undo() override {
        fan->turnOn();
    }

    std::string getDescription() const override {
        return "Turn off " + fan->getName();
    }

private:
    std::shared_ptr<Fan> fan;
};

// Smart Home Controller
class SmartHomeController {
public:
    void executeCommand(std::shared_ptr<Command> command) {
        if (command) {
            command->execute();
            commandHistory.push(command);
            std::cout << "Executed: " << command->getDescription() << std::endl;
        }
    }

    void undo() {
        if (!commandHistory.empty()) {
            auto command = commandHistory.top();
            command->undo();
            commandHistory.pop();
            std::cout << "Undone: " << command->getDescription() << std::endl;
        } else {
            std::cout << "No commands to undo" << std::endl;
        }
    }

    void showHistory() const {
        std::cout << "\nCommand History:" << std::endl;
        std::stack<std::shared_ptr<Command>> temp = commandHistory;
        int count = 1;
        while (!temp.empty()) {
            std::cout << count++ << ". " << temp.top()->getDescription() << std::endl;
            temp.pop();
        }
    }

private:
    std::stack<std::shared_ptr<Command>> commandHistory;
};

// Test function
void testSmartHome() {
    // Create the controller
    SmartHomeController controller;

    // Create devices
    auto livingRoomLight = std::make_shared<Light>("Living Room Light");
    auto bedroomLight = std::make_shared<Light>("Bedroom Light");
    auto ceilingFan = std::make_shared<Fan>("Ceiling Fan");

    // Create commands
    auto livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    auto bedroomLightOn = std::make_shared<LightOnCommand>(bedroomLight);
    auto bedroomLightOff = std::make_shared<LightOffCommand>(bedroomLight);
    auto fanOn = std::make_shared<FanOnCommand>(ceilingFan);
    auto fanOff = std::make_shared<FanOffCommand>(ceilingFan);

    std::cout << "=== Smart Home Automation Demo ===\n" << std::endl;

    // Execute some commands
    controller.executeCommand(livingRoomLightOn);
    controller.executeCommand(bedroomLightOn);
    controller.executeCommand(fanOn);

    std::cout << "\n=== Current Command History ===\n";
    controller.showHistory();

    // Undo last command
    std::cout << "\n=== Undoing Last Command ===\n";
    controller.undo();

    // Execute more commands
    controller.executeCommand(livingRoomLightOff);
    controller.executeCommand(bedroomLightOff);

    std::cout << "\n=== Final Command History ===\n";
    controller.showHistory();

    // Undo multiple commands
    std::cout << "\n=== Undoing Multiple Commands ===\n";
    controller.undo();
    controller.undo();
    controller.undo();
}

int main() {
    testSmartHome();
    return 0;
}