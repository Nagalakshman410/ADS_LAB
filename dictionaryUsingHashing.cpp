#include <iostream>
#include <vector>
using namespace std;

// Define the structure for dictionary entry
struct KeyValuePair {
    int key;
    string value;
    KeyValuePair(int k, const string& v) : key(k), value(v) {}
};

// Define the Dictionary class
class Dictionary {
private:
    vector<KeyValuePair*> table;
    int capacity;

    // Hash function to calculate index
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    // Constructor
    Dictionary(int cap) : capacity(cap) {
        table.resize(capacity, nullptr);
    }

    // Destructor
    ~Dictionary() {
        for (auto entry : table) {
            delete entry;
        }
    }

    // Function to insert a key-value pair into the dictionary
    void insert(int key, const string& value) {
        int index = hashFunction(key);
        KeyValuePair* newEntry = new KeyValuePair(key, value);
        if (table[index] == nullptr) {
            table[index] = newEntry;
        } else {
            // Collision handling (Linear Probing)
            int newIndex = (index + 1) % capacity;
            while (table[newIndex] != nullptr && newIndex != index) {
                newIndex = (newIndex + 1) % capacity;
            }
            if (table[newIndex] == nullptr) {
                table[newIndex] = newEntry;
            } else {
                cout << "Dictionary is full, unable to insert." << endl;
                delete newEntry;
            }
        }
    }

    // Function to retrieve the value associated with a given key
    string get(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                return table[index]->value;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break; // Key not found
            }
        }
        return "Key not found";
    }

    // Function to delete a key-value pair from the dictionary
    void remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                delete table[index];
                table[index] = nullptr;
                cout << "Key-value pair deleted." << endl;
                return;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break; // Key not found
            }
        }
        cout << "Key not found, unable to delete." << endl;
    }
};

// Main function
int main() {
    int capacity;
    cout << "Enter the capacity of the dictionary: ";
    cin >> capacity;

    // Create a dictionary with user-defined capacity
    Dictionary dict(capacity);

    // Insert key-value pairs
    int key;
    string value;
    char choice;
    do {
        cout << "Enter key: ";
        cin >> key;
        cout << "Enter value: ";
        cin >> value;
        dict.insert(key, value);
        cout << "Do you want to insert another key-value pair? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Retrieve values for keys
    cout << "Enter a key to retrieve its value: ";
    cin >> key;
    cout << "Value for key " << key << ": " << dict.get(key) << endl;

    // Remove a key-value pair
    cout << "Enter a key to remove its value: ";
    cin >> key;
    dict.remove(key);

    return 0;
}
