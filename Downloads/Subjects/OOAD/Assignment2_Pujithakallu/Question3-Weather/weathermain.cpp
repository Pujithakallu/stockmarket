#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>
#include <deque>
#include <numeric>
class WeatherData;

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void update(const WeatherData& weatherData) = 0;
    virtual std::string getName() const = 0;
};
class WeatherData {
public:
    void registerObserver(WeatherObserver* observer) {
        if (observer != nullptr) {
            auto it = std::find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) {
                observers.push_back(observer);
                std::cout << "Registered observer: " << observer->getName() << std::endl;
            }
        }
    }

    void removeObserver(WeatherObserver* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Removed observer: " << observer->getName() << std::endl;
        }
    }

    void notifyObservers() const {
        for (const auto& observer : observers) {
            observer->update(*this);
        }
    }

    void setMeasurements(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }

private:
    void measurementsChanged() {
        notifyObservers();
    }

    std::vector<WeatherObserver*> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;
};


class DisplayObserver : public WeatherObserver {
public:
    void update(const WeatherData& weatherData) override {
        std::cout << "\n=== Current Weather Conditions ===\n"
                  << "Temperature: " << std::fixed << std::setprecision(1) 
                  << weatherData.getTemperature() << "°C\n"
                  << "Humidity: " << weatherData.getHumidity() << "%\n"
                  << "Pressure: " << weatherData.getPressure() << " hPa\n"
                  << "================================\n";
    }

    std::string getName() const override {
        return "Display Observer";
    }
};


class MobileAlertObserver : public WeatherObserver {
public:
    explicit MobileAlertObserver(float threshold) : temperatureThreshold(threshold) {}

    void update(const WeatherData& weatherData) override {
        if (weatherData.getTemperature() > temperatureThreshold) {
            std::cout << "\n MOBILE ALERT: Temperature above threshold!\n"
                      << "Current: " << std::fixed << std::setprecision(1) 
                      << weatherData.getTemperature() << "°C\n"
                      << "Threshold: " << temperatureThreshold << "°C\n";
        }
    }

    std::string getName() const override {
        return "Mobile Alert Observer";
    }

private:
    float temperatureThreshold;
};


class StatisticsObserver : public WeatherObserver {
public:
    void update(const WeatherData& weatherData) override {
        temperatures.push_back(weatherData.getTemperature());
        if (temperatures.size() > maxReadings) {
            temperatures.pop_front();
        }

        if (!temperatures.empty()) {
            float avg = std::accumulate(temperatures.begin(), temperatures.end(), 0.0f) / 
                       temperatures.size();
            float min = *std::min_element(temperatures.begin(), temperatures.end());
            float max = *std::max_element(temperatures.begin(), temperatures.end());

            std::cout << "\n=== Temperature Statistics ===\n"
                      << "Average: " << std::fixed << std::setprecision(1) << avg << "°C\n"
                      << "Minimum: " << min << "°C\n"
                      << "Maximum: " << max << "°C\n"
                      << "Readings: " << temperatures.size() << "\n"
                      << "===========================\n";
        }
    }

    std::string getName() const override {
        return "Statistics Observer";
    }

private:
    std::deque<float> temperatures;
    static const size_t maxReadings = 10;  
};


void testWeatherSystem() {
    
    WeatherData weatherStation;

    
    DisplayObserver display;
    MobileAlertObserver mobileAlert(30.0f);  
    StatisticsObserver stats;

    
    weatherStation.registerObserver(&display);
    weatherStation.registerObserver(&mobileAlert);
    weatherStation.registerObserver(&stats);

    
    std::cout << "\nSimulating weather changes...\n";
    
    
    weatherStation.setMeasurements(25.5f, 65.0f, 1013.2f);
    
    weatherStation.setMeasurements(32.7f, 70.0f, 1012.5f);
    
    weatherStation.removeObserver(&mobileAlert);
    
    weatherStation.setMeasurements(28.4f, 72.0f, 1011.8f);
    weatherStation.setMeasurements(27.9f, 68.0f, 1012.1f);
    
    weatherStation.registerObserver(&mobileAlert);
    
    weatherStation.setMeasurements(31.2f, 66.0f, 1013.5f);
}

int main() {
    testWeatherSystem();
    return 0;
}