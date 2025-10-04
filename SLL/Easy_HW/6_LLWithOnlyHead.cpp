#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* next {nullptr};
    Node(int data): data(data) {}
    ~Node() {
        cout << "Destroy value: " << data <<" at address "<< this<< "\n";
    }
};

class LinkedList {
    private:
        Node * head;

    public:
        LinkedList() : head{nullptr} {
	    }
	    LinkedList(const LinkedList&) = delete;
	    LinkedList &operator=(const LinkedList &another) = delete;

        ~LinkedList() {
        Node* nextNode {nullptr};
        while (head) {
            nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }

        void add_element(int value) { // Time and memory O(1)
            Node * node = new Node{value};
        
            node->next = head;
            head = node;
            return ;
        }

        void print() { // Time is O(n) - Memory is O(1)
            for (Node* curr = head; curr; curr = curr->next)
                cout << curr->data << " ";
            cout << "\n";
            return ;
        }

        Node* get_tail() { // Time is O(n) - Memory is O(1)
            for (Node* curr = head; curr; curr = curr->next)
                if (!curr->next)
                    return curr;
            
            return nullptr;
        }

        
};

int main() {

    LinkedList ll;
    ll.add_element(6);
    ll.add_element(10);
    ll.add_element(8);
    ll.add_element(15);

    ll.print();
    cout << ll.get_tail()->data << "\n";

    return 0;

}