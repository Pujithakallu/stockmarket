#ifndef WORDDOCUMENT_HPP
#define WORDDOCUMENT_HPP

#include "Document.hpp"
#include <iostream>

class WordDocument : public Document {
public:
    void generate() override {
        std::cout << "Generating Word document" << std::endl;
    }

    void addWatermark(const std::string& watermark) override {
        std::cout << "Adding watermark to Word: " << watermark << std::endl;
    }

    void addMetadata(const std::map<std::string, std::string>& metadata) override {
        std::cout << "Adding metadata to Word: " << std::endl;
        for (const auto& pair : metadata) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    void addTable(const std::vector<std::vector<std::string>>& tableData) override {
        std::cout << "Adding table to Word:" << std::endl;
        for (const auto& row : tableData) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif 
