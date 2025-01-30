// 1.) Design a Dependency Injection Framework using the Factory pattern in C++. The framework
// should allow injecting dependencies into objects dynamically at runtime.
// • Implement a Car manufacturing system where engines (PetrolEngine, DieselEngine) are
// injected into Car objects based on runtime configuration.
// • Provide code and explanations.



#include <iostream>
#include <memory>
#include <string>


class Engine {
public:
    virtual void start() = 0;
    
    virtual ~Engine() {}
};

class PetrolEngine : public Engine {
public:
    void start() {
        std::cout << "Petrol Engine started!" << std::endl;
    }

    virtual ~PetrolEngine() {}
};


class DieselEngine : public Engine {
public:
    void start() {
        std::cout << "Diesel Engine started!" << std::endl;
    }
    virtual ~DieselEngine() {}
};


class Car {
private:
    std::shared_ptr<Engine> engine;
public:
   
    explicit Car(std::shared_ptr<Engine> eng) : engine(eng) {}
    
    void startCar() {
        engine->start();
    }
};


class EngineFactory {
public:
    static std::shared_ptr<Engine> createEngine(const std::string& engineType) {
        if (engineType == "Petrol") {
            
            std::shared_ptr<Engine> engine(new PetrolEngine());
            return engine;
        } 
        else if (engineType == "Diesel") {
            std::shared_ptr<Engine> engine(new DieselEngine());
            return engine;
        } 
        else {
            throw std::invalid_argument("Invalid engine type");
        }
    }
};

int main() {
    std::string engineType;
    std::cout << "Enter engine type (Petrol/Diesel): ";
    std::cin >> engineType;
    
    
    std::shared_ptr<Engine> engine = EngineFactory::createEngine(engineType);
    
    Car car(engine);
    car.startCar();
    
    return 0;
}