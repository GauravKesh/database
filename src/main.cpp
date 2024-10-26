#include "DocumentDB.h"

DocumentDB::DocumentDB() : head(nullptr) {}

DocumentDB::~DocumentDB() {
    while (head) {
        Document* temp = head;
        head = head->next;
        delete temp;
    }
}

void DocumentDB::insert(const std::string& id, const std::unordered_map<std::string, std::string>& fields) {
    Document* newDocument = new Document{id, fields, nullptr};
    if (!head) {
        head = newDocument;
    } else {
        Document* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newDocument;
    }
}

Document* DocumentDB::find(const std::string& id) {
    Document* current = head;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DocumentDB::update(const std::string& id, const std::unordered_map<std::string, std::string>& fields) {
    Document* document = find(id);
    if (document) {
        for (const auto& field : fields) {
            document->fields[field.first] = field.second;
        }
    } else {
        std::cerr << "Error: Document with ID " << id << " not found.\n";
    }
}

void DocumentDB::remove(const std::string& id) {
    if (!head) return;

    if (head->id == id) {
        Document* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Document* current = head;
    while (current->next) {
        if (current->next->id == id) {
            Document* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }

    std::cerr << "Error: Document with ID " << id << " not found.\n";
}

void DocumentDB::displayAll() const {
    Document* current = head;
    while (current) {
        current->display();
        std::cout << "------------------------\n";
        current = current->next;
    }
}

void DocumentDB::saveToFile() {
    std::ofstream file("data/database.json");
    file << "[\n";
    Document* current = head;
    while (current) {
        file << "  {\n    \"id\": \"" << current->id << "\",\n    \"fields\": {\n";
        for (const auto& field : current->fields) {
            file << "      \"" << field.first << "\": \"" << field.second << "\",\n";
        }
        // Remove the last comma
        file.seekp(-2, std::ios_base::cur); 
        file << "\n    }\n  }";
        if (current->next) {
            file << ",";
        }
        file << "\n";
        current = current->next;
    }
    file << "]\n";
    file.close();
}

void DocumentDB::loadFromFile() {
    std::ifstream file("data/database.json");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file.\n";
        return;
    }

    std::string line;
    std::unordered_map<std::string, std::string> fields;
    std::string id;
    while (std::getline(file, line)) {
        if (line.find("\"id\":") != std::string::npos) {
            id = line.substr(line.find(":") + 3);
            id.pop_back();
            fields.clear(); 
        } else if (line.find("\"fields\":") != std::string::npos) {
            continue;
        } else if (line.find(":") != std::string::npos) {
            size_t keyStart = line.find("\"") + 1;
            size_t keyEnd = line.find("\"", keyStart);
            size_t valueStart = line.find(":") + 3;
            size_t valueEnd = line.find("\"", valueStart);
            std::string key = line.substr(keyStart, keyEnd - keyStart);
            std::string value = line.substr(valueStart, valueEnd - valueStart);
            fields[key] = value;
        } else if (line.find("}") != std::string::npos) {
            insert(id, fields);
        }
    }
    file.close();
}

int main() {
    DocumentDB db;

    db.loadFromFile();  // Load existing data

    int choice;
    do {
        std::cout << "1. Insert Document\n";
        std::cout << "2. Find Document\n";
        std::cout << "3. Update Document\n";
        std::cout << "4. Remove Document\n";
        std::cout << "5. Display All Documents\n";
        std::cout << "6. Save to File\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string id;
                std::unordered_map<std::string, std::string> fields;
                std::string key, value;
                std::cout << "Enter Document ID: ";
                std::cin >> id;
                std::cout << "Enter fields (key:value) separated by spaces (enter 'done' to finish):\n";
                while (true) {
                    std::cin >> key;
                    if (key == "done") break;
                    std::getline(std::cin, value);
                    fields[key] = value.substr(1);  // Ignore the space before the value
                }
                db.insert(id, fields);
                break;
            }
            case 2: {
                std::string id;
                std::cout << "Enter Document ID: ";
                std::cin >> id;
                Document* doc = db.find(id);
                if (doc) {
                    doc->display();
                } else {
                    std::cout << "Document not found.\n";
                }
                break;
            }
            case 3: {
                std::string id;
                std::unordered_map<std::string, std::string> fields;
                std::string key, value;
                std::cout << "Enter Document ID: ";
                std::cin >> id;
                std::cout << "Enter fields to update (key:value) separated by spaces (enter 'done' to finish):\n";
                while (true) {
                    std::cin >> key;
                    if (key == "done") break;
                    std::getline(std::cin, value);
                    fields[key] = value.substr(1);
                }
                db.update(id, fields);
                break;
            }
            case 4: {
                std::string id;
                std::cout << "Enter Document ID: ";
                std::cin >> id;
                db.remove(id);
                break;
            }
            case 5: {
                db.displayAll();
                break;
            }
            case 6: {
                db.saveToFile();
                std::cout << "Data saved to file.\n";
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
