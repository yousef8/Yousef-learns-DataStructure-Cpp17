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
    const Node *get_head() const
    {
        return head;
    }

    void add_num(const LinkedList &another)
    {
        Node *cur{head};
        int carry{0};
        for (const Node *cur_another{another.get_head()}; cur_another; cur_another = cur_another->next)
        {
            if (cur)
            {
                int sum = cur->data + cur_another->data + carry;
                cur->data = sum % 10;
                carry = sum / 10;
                cur = cur->next;
            }
            else
            {
                insert_end(cur_another->data + carry);
                carry = 0;
            }
        }

        if (carry)
            insert_end(carry);

        debug_verify_data_integrity();
    }

    void print_num()
    {
        print_num(head);
        cout << "\n";
    }

    void print_num(const Node *cur)
    {
        if (!cur)
            return;

        print_num(cur->next);
        cout << cur->data;
    }
};

int main()
{
    LinkedList l1{1, 2, 3};
    LinkedList l2{9, 6, 5};

    cout << "321 + 354 = ";
    l1.add_num({4, 5, 3});
    l1.print_num();

    cout << "569 + 98754678 = ";
    l2.add_num({8, 7, 6, 4, 5, 7, 8, 9});
    l2.print_num();

    return 0;
}
