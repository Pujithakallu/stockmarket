#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP
#include <iostream>
#include <string>
#include <map>
#include <vector>

class Document {
public:
    virtual ~Document() {}

    virtual void generate() = 0; 

    virtual void addWatermark(const std::string& watermark) {
        
        std::cout << "No watermark for this document type." << std::endl;
    }

    virtual void addMetadata(const std::map<std::string, std::string>& metadata) {
        
        std::cout << "No metadata for this document type." << std::endl;
    }

    virtual void addTable(const std::vector<std::vector<std::string>>& tableData) {
        
        std::cout << "No table for this document type." << std::endl;
    }
};

#endif 
