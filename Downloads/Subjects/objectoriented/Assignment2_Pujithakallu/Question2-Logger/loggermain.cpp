#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <memory>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class LogEntry {
public:
    LogEntry(LogLevel level, const std::string& message, 
            const std::chrono::system_clock::time_point& timestamp)
        : level(level), message(message), timestamp(timestamp) {}

    std::string getLevelString() const {
        switch (level) {
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

    std::string getTimestampString() const {
        auto time_t = std::chrono::system_clock::to_time_t(timestamp);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::string toString() const {
        return "[" + getTimestampString() + "] " + getLevelString() + ": " + message;
    }

    LogLevel level;
    std::string message;
    std::chrono::system_clock::time_point timestamp;
};

class Logger {
public:
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;  
        return instance;
    }

    void info(const std::string& message) {
        log(LogLevel::INFO, message);
    }

    void warning(const std::string& message) {
        log(LogLevel::WARNING, message);
    }

    void error(const std::string& message) {
        log(LogLevel::ERROR, message);
    }

    std::vector<LogEntry> getAllLogs() const {
        std::lock_guard<std::mutex> lock(mutex);
        return logs;
    }

    std::vector<LogEntry> getLogsByLevel(LogLevel level) const {
        std::lock_guard<std::mutex> lock(mutex);
        std::vector<LogEntry> filteredLogs;
        for (const auto& log : logs) {
            if (log.level == level) {
                filteredLogs.push_back(log);
            }
        }
        return filteredLogs;
    }

    void clearLogs() {
        std::lock_guard<std::mutex> lock(mutex);
        logs.clear();
    }

private:
    Logger() = default;  
    std::vector<LogEntry> logs;
    mutable std::mutex mutex;  

    void log(LogLevel level, const std::string& message) {
        auto now = std::chrono::system_clock::now();
        LogEntry entry(level, message, now);
        
        {
            std::lock_guard<std::mutex> lock(mutex);
            logs.push_back(entry);
        }
        
       
        std::cout << entry.toString() << std::endl;
    }
};


void testLogger() {
    
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();

    
    std::cout << "Testing singleton behavior:\n";
    std::cout << "logger1 address: " << &logger1 << "\n";
    std::cout << "logger2 address: " << &logger2 << "\n";
    std::cout << "Instances are the same: " << (&logger1 == &logger2 ? "true" : "false") << "\n\n";

    std::cout << "Testing logging functionality:\n";
    logger1.info("Application started");
    logger1.warning("Memory usage is high");
    logger1.error("Failed to connect to database");
    logger2.info("User logged in");

    std::cout << "\nAll logs:\n";
    auto allLogs = logger1.getAllLogs();
    for (const auto& log : allLogs) {
        std::cout << log.toString() << "\n";
    }

    
    std::cout << "\nWarning logs only:\n";
    auto warningLogs = logger1.getLogsByLevel(LogLevel::WARNING);
    for (const auto& log : warningLogs) {
        std::cout << log.toString() << "\n";
    }

    
    logger1.clearLogs();
    std::cout << "\nAfter clearing logs:\n";
    std::cout << "Log count: " << logger1.getAllLogs().size() << "\n";
}

int main() {
    testLogger();
    return 0;
}