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
    Node *prev{}; // Previous node!

    Node(int data) : data(data) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

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
    int length = 0;

    // let's maintain how many nodes

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

        if (node->prev == nullptr)
            cout << "X\t";
        else
            cout << node->prev->data << "\t";

        cout << " <= [" << node->data << "]\t => \t";

        if (node->next == nullptr)
            cout << "X\t";
        else
            cout << node->next->data << "\t";

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
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int)debug_data.size());

        len = 0;
        for (Node *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
        cout << "\n";
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

    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void insert_end(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(tail, item);
            tail = item;
        }
        debug_verify_data_integrity();
    }

    void insert_front(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        debug_verify_data_integrity();
    }

    void print_reversed()
    {
        for (Node *cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void delete_front()
    {
        if (!head)
            return;
        Node *cur = head->next;
        delete_node(head);
        head = cur;

        // Integrity change
        if (head)
            head->prev = nullptr;
        else if (!length)
            tail = nullptr;

        debug_verify_data_integrity();
    }

    void delete_end()
    {
        if (!head)
            return;
        Node *cur = tail->prev;
        delete_node(tail);
        tail = cur;

        // Integrity change
        if (tail)
            tail->next = nullptr;
        else if (!length)
            head = nullptr;

        debug_verify_data_integrity();
    }

    Node *delete_and_link(Node *cur)
    {
        // remove this node, but connect its neighbors
        Node *ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);

        return ret;
    }

    Node *delete_a_node(Node *cur)
    {
        if (head == cur)
            head = cur->next;

        if (cur == tail)
            tail = cur->prev;

        cur = delete_and_link(cur);
        debug_verify_data_integrity();
        return cur;
    }

    void delete_even_pos()
    {
        if (head == tail)
            return;

        for (Node *cur{head->next}; cur;)
        {
            cur = delete_a_node(cur);

            // move the cur
            cur = cur->next;
            if (cur)
                cur = cur->next;
        }
    }
};

int main()
{

    LinkedList ll{2, 9};
    ll.delete_even_pos();
    ll.print();
    return 0;
}
