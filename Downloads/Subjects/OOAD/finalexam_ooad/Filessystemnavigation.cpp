// 3.) Composite Pattern for Filesystem Navigation Design a Filesystem Navigation System using
// the Composite pattern in C++.
// • Implement components like File and Directory, where Directory can contain File objects or
// other Directory objects.
// • Write methods to calculate the total size of a directory and list all files recursively.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>


class FSComponent {
protected:
    std::string name;
    int size;

public:
    FSComponent(const std::string& n, int s) : name(n), size(s) {}
    virtual ~FSComponent() {}  

    std::string getName() const { return name; }
    virtual int getSize() const { return size; }
    
    
    virtual void list(int indent = 0) const = 0;
    virtual bool isDirectory() const = 0;
};


class File : public FSComponent {
public:
    File(const std::string& name, int size) : FSComponent(name, size) {}

    virtual void list(int indent = 0) const {  
        std::string indentation(indent, ' ');
        std::cout << indentation << "File: " << name << " (" << size << " bytes)" << std::endl;
    }

    virtual bool isDirectory() const { return false; }  
};

class MatchName {
    std::string componentName;
public:
    MatchName(const std::string& name) : componentName(name) {}
    bool operator()(const std::shared_ptr<FSComponent>& component) const {
        return component->getName() == componentName;
    }
};


class Directory : public FSComponent {
private:
    std::vector<std::shared_ptr<FSComponent> > children;  

public:
    Directory(const std::string& name) : FSComponent(name, 0) {}

    void add(std::shared_ptr<FSComponent> component) {
        children.push_back(component);
    }

    void remove(const std::string& componentName) {
        children.erase(
            std::remove_if(children.begin(), children.end(), MatchName(componentName)),
            children.end()
        );
    }

    virtual int getSize() const {  
        int totalSize = 0;
        for (std::vector<std::shared_ptr<FSComponent> >::const_iterator it = children.begin();
             it != children.end(); ++it) {
            totalSize += (*it)->getSize();
        }
        return totalSize;
    }

    virtual void list(int indent = 0) const {  
        std::string indentation(indent, ' ');
        std::cout << indentation << "Directory: " << name << " (total: " << getSize() << " bytes)" << std::endl;
        
        for (std::vector<std::shared_ptr<FSComponent> >::const_iterator it = children.begin();
             it != children.end(); ++it) {
            (*it)->list(indent + 2);
        }
    }

    virtual bool isDirectory() const { return true; } 

    
    std::shared_ptr<FSComponent> find(const std::string& componentName) const {
        for (std::vector<std::shared_ptr<FSComponent> >::const_iterator it = children.begin();
             it != children.end(); ++it) {
            if ((*it)->getName() == componentName) {
                return *it;
            }
            if ((*it)->isDirectory()) {
                std::shared_ptr<Directory> dir = std::dynamic_pointer_cast<Directory>(*it);
                std::shared_ptr<FSComponent> result = dir->find(componentName);
                if (result) {
                    return result;
                }
            }
        }
        return std::shared_ptr<FSComponent>(); 
    }
};

int main() {
    
    std::shared_ptr<Directory> root(new Directory("/"));
    
   
    std::shared_ptr<Directory> documents(new Directory("Documents"));
    std::shared_ptr<Directory> pictures(new Directory("Pictures"));
    
   
    std::shared_ptr<File> doc1(new File("report.doc", 1000));
    std::shared_ptr<File> doc2(new File("letter.txt", 500));
    std::shared_ptr<File> pic1(new File("vacation.jpg", 2000));
    std::shared_ptr<File> pic2(new File("family.jpg", 1500));
    
    
    documents->add(doc1);
    documents->add(doc2);
    pictures->add(pic1);
    pictures->add(pic2);
    
    root->add(documents);
    root->add(pictures);
    
   
    std::cout << "Directory Structure:" << std::endl;
    root->list();
    
  
    std::cout << "\nTotal size: " << root->getSize() << " bytes" << std::endl;
    
    
    std::shared_ptr<FSComponent> found = root->find("vacation.jpg");
    if (found) {
        std::cout << "\nFound file: " << found->getName() << 
                    " (Size: " << found->getSize() << " bytes)" << std::endl;
    }
    
    return 0;
}