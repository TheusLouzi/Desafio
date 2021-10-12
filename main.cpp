#include <iostream>
using namespace std;

class Node {
    friend class List;
    private:
        int value;
        Node *next;
        Node *prior;
    public:
        Node(int v);
};

Node::Node(int v) {
    value = v;
    next = nullptr;
    prior = nullptr;
}

class List {
    private:
        Node *first;
        Node *last;
    public:
        List();
        void insert(int v);
        void print(int v);
        void print();
        int remove(int v);
        void removeSequence();
};

List::List() {
    first = nullptr;
    last = nullptr;
}

void List::insert(int v) {
    Node *newNode = new Node(v);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    }
    else {
        newNode->prior = last;
        last->next = newNode;
        last = newNode;
    }
}

void List::print(int v) {
    cout << v << " removed!\n";
}

void List::print() {
    Node *auxNode = new Node(0);
    auxNode = first;
    if (first != nullptr) {
        cout << "List: ";
        while (auxNode->next != nullptr) {
            cout << auxNode->value << " ";
            auxNode = auxNode->next;
        }
        cout << auxNode->value << endl;
    }
    else {
        cerr << "Cannot print! List is empty!\n";
    }
}

int List::remove(int v) {
    Node *auxNode = new Node(0);
    auxNode = first;
    if (first == nullptr) {
        cerr << "Error. List is empty!\n";
        return 0;
    }
    if (auxNode->value == v) {
        if (auxNode->next == nullptr) {
            first = nullptr;
            last = nullptr;
        }
        else {
            first = auxNode->next;
            first->prior = nullptr;
        }
        print(v);
        return auxNode->value;
    }
    else {
        while (auxNode->value != v && auxNode->next != nullptr) {
            auxNode = auxNode->next;
        }
        if (auxNode->value == v) {
            if (auxNode->next == nullptr) {
                last = last->prior;
                last->next = nullptr;
            }
            else {
                auxNode->prior->next = auxNode->next;
                auxNode->next->prior= auxNode->prior;
            }
            print(v);
            return auxNode->value;
        }
        else cerr << "Value not found and could no be deleted!\n";
    }
}

void List::removeSequence() {
    Node *auxNode = new Node(0);
    auxNode = first;
    bool sentry = 0;
    while (auxNode->next != nullptr && sentry == 0) {

        if (auxNode->value == -1) {
            Node *findseqNode = auxNode->next;
            if (findseqNode->value == 0) {
                findseqNode = findseqNode->next;
                if (findseqNode->value == 2) {
                    findseqNode = findseqNode->next;
                    if (findseqNode->value == 5) {
                        sentry = 1;
                    }
                }
            }
        }
        

        if (sentry == 1) {
            remove(-1);
            remove(0);
            remove(2);
            remove(5);
        }
        else {
            remove(auxNode->value);
            auxNode = auxNode->next;
            if (auxNode->next == nullptr) {
                remove(auxNode->value);
                cerr << "Sequence not found!\n";
            } 
        }
    }    
}

int main() {
    int value;
    char comando;
    int removed;
    List aList;
    cout << "Type i to insert, r to an element, p to print or t remove until the sequence (-1, 0, 2, 5) is printed.\nType s to stop.\n";
    do {
        cin >> comando;
        switch (comando) {
        case 'i':
            cin >> value;
            aList.insert(value);
            break;

        case 'r':
            cin >> value;
            removed = aList.remove(value);
            break;

        case 't':
            aList.removeSequence();
            break;

        case 'p':
            aList.print();
            break;

        case 's':
            break;

        default:
            cerr << "Invalid command.\n";
            break;
        }
    } while (comando != 'f');

    return 0;
}