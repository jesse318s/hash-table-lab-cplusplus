#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Customer {
public:
    std::string lastname;
    std::string firstname;
    std::string id;

    Customer(std::string lastname, std::string firstname, std::string id)
        : lastname(lastname), firstname(firstname), id(id) {}
};

class Node {
public:
    Customer data;
    Node* prev;
    Node* next;

    Node(Customer data) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtHead(Customer data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
};

class HashTable {
private:
    int BUCKET_COUNT;
    std::vector<DoublyLinkedList> table;

    int hashFunction(std::string key) {
        unsigned long long hash = 14695981039346656037ULL;

        for (char c : key) {
            hash ^= c;
            hash *= 1099511628211ULL;
        }

        return hash % BUCKET_COUNT;
    }

public:
    HashTable(int bucketCount) : BUCKET_COUNT(bucketCount), table(bucketCount) {}

    void insert(Customer customer) {
        int index = hashFunction(customer.id);

        table[index].insertAtHead(customer);
    }

    void display() {
        for (int i = 0; i < BUCKET_COUNT; ++i) {
            Node* temp = table[i].head;
            std::cout << "Bucket " << i << ": ";

            while (temp != nullptr) {
                std::cout << temp->data.lastname << " " << temp->data.firstname << " (" << temp->data.id << ") -> ";
                temp = temp->next;
            }

            std::cout << "NULL\n";
        }
    }
};

int main() {
    HashTable ht(400);

    std::ifstream file("Customer.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string lastname, firstname, id;
        std::getline(ss, lastname, ',');
        std::getline(ss, firstname, ',');
        std::getline(ss, id);
        ht.insert(Customer(lastname, firstname, id));
    }

    file.close();
    ht.display();

    return 0;
}
