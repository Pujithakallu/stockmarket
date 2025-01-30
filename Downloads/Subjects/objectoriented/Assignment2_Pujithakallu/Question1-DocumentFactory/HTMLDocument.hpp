#ifndef HTMLDOCUMENT_HPP
#define HTMLDOCUMENT_HPP

#include "Document.hpp"
#include <iostream>

class HTMLDocument : public Document {
public:
    void generate() override {
        std::cout << "Generating HTML document..." << std::endl;
    }

    void addMetadata(const std::map<std::string, std::string>& metadata) override {
        std::cout << "Adding metadata to HTML: " << std::endl;
        for (const auto& pair : metadata) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

#endif 
