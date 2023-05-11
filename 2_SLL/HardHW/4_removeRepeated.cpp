#include <iostream>
#include <cassert>
#include <climits>

#include <vector> // for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node
{
    int data{};
    Node *next{};
    Node(int data) : data(data) {}
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length = 0; // let's maintain how many nodes

    vector<Node *> debug_data; // add/remove nodes you use

    void debug_add_node(Node *node)
    {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node *node)
    {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:
    // Below 2 deletes prevent copy and assign to avoid this mistake
    LinkedList()
    {
    }

    LinkedList(const initializer_list<int> &lst)
    {
        for (auto &value : lst)
            insert_end(value);
    }

    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

    ~LinkedList()
    {
        Node *nextNode{nullptr};
        while (head)
        {
            nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }

    void debug_print_address()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }

    void debug_print_node(Node *node, bool is_seperate = false)
    {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr)
        {
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "")
    {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int)debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n"
             << flush;
    }

    string debug_to_string()
    {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node *cur = head; cur; cur = cur->next)
        {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
            assert(len < 10000); // Consider infinite cycle?
        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    ////////////////////////////////////////////////////////////

    void print()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    // These 2 simple functions just to not forget changing the vector and length
    void delete_node(Node *node)
    {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node *node)
    {
        debug_add_node(node);
        ++length;
    }

    void insert_end(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }

    ////////////////////////////////////////////////////////////
    void delete_a_node(Node *prv)
    {

        if (!prv && head == tail)
        {
            delete_node(head);
            head = tail = nullptr;
            return;
        }

        if (!prv && head != tail)
        {
            Node *to_delete = head;
            head = head->next;
            delete_node(to_delete);
            return;
        }

        Node *to_delete = prv->next;
        prv->next = prv->next->next;
        if (to_delete == tail)
            tail = prv;
        delete_node(to_delete);
        return;
    }

    void delete_key_recursive(vector<int> keys)
    {
        for (int key : keys)
        {
            for (Node *cur{head}, *prv{nullptr}; cur;)
            {
                if (cur->data == key)
                {
                    cur = cur->next;
                    delete_a_node(prv);
                }
                else
                {
                    prv = cur;
                    cur = cur->next;
                }
            }
        }
    }

    void remove_repeated()
    {
        vector<int> keys;

        for (Node *cur{head}, *prv{nullptr}; cur; prv = cur, cur = cur->next)
            if (prv)
                if (prv->data == cur->data)
                    if (keys.empty() || keys.back() != cur->data)
                        keys.push_back(cur->data);

        delete_key_recursive(keys);
        debug_verify_data_integrity();
    }
};

int main()
{
    LinkedList l1{1, 1, 2, 2, 2, 3, 5};
    LinkedList l2{1, 1};
    LinkedList l3{1, 1, 2, 2, 2};
    LinkedList l4{1, 1, 2, 2, 2, 5};
    LinkedList l5{1, 2, 2, 2, 3};

    l1.debug_print_address();
    l1.remove_repeated();
    l2.remove_repeated();
    l3.remove_repeated();
    l4.remove_repeated();
    l5.remove_repeated();

    l1.print();
    l2.print();
    l3.print();
    l4.print();
    l5.print();

    return 0;
}