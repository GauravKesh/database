#ifndef DOCUMENTDB_H
#define DOCUMENTDB_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

struct Document {
    std::string id;
    std::unordered_map<std::string, std::string> fields;
    Document* next;

    //  function to display the document
    void display() const {
        std::cout << "Document ID: " << id << "\nFields:\n";
        for (const auto& field : fields) {
            std::cout << "  " << field.first << ": " << field.second << '\n';
        }
    }
};

class DocumentDB {
public:
    DocumentDB();
    ~DocumentDB();

    void insert(const std::string& id, const std::unordered_map<std::string, std::string>& fields);
    Document* find(const std::string& id);
    void update(const std::string& id, const std::unordered_map<std::string, std::string>& fields);
    void remove(const std::string& id);
    void displayAll() const;
    void saveToFile();
    void loadFromFile();

private:
    Document* head;
};

#endif
