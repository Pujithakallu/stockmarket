#include "DocumentFactory.hpp"
#include <iostream>

int main() {
    
    Document* pdfDoc = DocumentFactory::createDocument("PDF");
    if (pdfDoc) { 
        pdfDoc->generate();  
        pdfDoc->addWatermark("Classified");
        pdfDoc->addMetadata({{"Creator", "Alex Taylor"}, {"Title", "Sample PDF Document"}});
        pdfDoc->addTable({{"Name", "Age"}, {"Pujitha", "29"}, {"kallu", "34"}});
        delete pdfDoc;  
    }

    std::cout << std::endl;

    
    Document* wordDoc = DocumentFactory::createDocument("Word");
    if (wordDoc) {
        wordDoc->generate();
        wordDoc->addWatermark("Preliminary");
        wordDoc->addMetadata({{"Creator", "Morgan Lee"}, {"Title", "Word Document Example"}});
        delete wordDoc;
    }

    std::cout << std::endl;

    
    Document* htmlDoc = DocumentFactory::createDocument("HTML");
    if (htmlDoc) {
        htmlDoc->generate();
        htmlDoc->addMetadata({{"Creator", "Jordan Smith"}, {"Description", "HTML Document Sample"}});
        delete htmlDoc;
    }

    return 0;
}
