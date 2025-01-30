#ifndef DOCUMENTFACTORY_HPP
#define DOCUMENTFACTORY_HPP

#include "Document.hpp"
#include "PDFDocument.hpp"
#include "WordDocument.hpp"
#include "HTMLDocument.hpp"
#include <string>
#include <map>

class DocumentFactory {
public:
    static Document* createDocument(const std::string& docType) {
        if (docType == "PDF") {
            return new PDFDocument();
        } else if (docType == "Word") {
            return new WordDocument();
        } else if (docType == "HTML") {
            return new HTMLDocument();
        } else {
            std::cout << "Unknown document type!" << std::endl;
            return nullptr;
        }
    }
};

#endif 
