#include <iostream>
#include <cassert>
#include <climits>

#include <vector> // for debug
#include <set>
#include <algorithm>
#include <sstream>
using namespace std;

struct Node
{
    int data{};
    Node *next{nullptr};
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

    void insert_front(int value)
    {
        Node *node = new Node{value};
        add_node(node);
        if (!head)
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
    }

    int delete_front()
    {
        Node *new_head = head->next;
        int value = head->data;

        delete_node(head);
        head = new_head;

        if (!head)
        {
            tail = nullptr;
        }
        return value;
    }

    Node *get_nth_back(int n)
    {
        int count{length};

        for (Node *curr = head; curr && count >= n; curr = curr->next, --count)
            if (count == n)
                return curr;

        return nullptr;
    }

    bool is_same(const LinkedList &ll)
    { // Time is O(n) - Memory is O(1)
        for (Node *og = head, *cp = ll.head; og || cp; og = og->next, cp = cp->next)
        {
            if (!og || !cp)
                return false;

            if (og->data != cp->data)
                return false;
        }

        return true;
    }

    void delete_node_with_key(int value)
    {
        if (head->data == value)
        {
            delete_front();
            return;
        }

        for (Node *cur = head; cur->next; cur = cur->next)
        {
            if (cur->next->data == value)
            {
                Node *temp = cur->next;
                bool is_tail = temp == tail;
                cur->next = cur->next->next;
                delete_node(temp);
                if (is_tail)
                    tail = cur;
                return;
            }

            cout << "This value doesn't exist\n";
            return;
        }
    }

    void swap_pairs()
    {
        for (Node *cur = head; cur && cur->next; cur = cur->next->next)
            swap(cur->data, cur->next->data);

        return;
    }

    void reverse()
    {
        for (Node *cur = head, *prv = nullptr; cur;)
        {
            Node *temp = cur->next;
            cur->next = prv;
            prv = cur;
            cur = temp;
        }

        swap(head, tail);
    }

    void delete_even_positions()
    {
        int idx{1};
        for (Node *cur = head, *prv = nullptr; cur; cur = cur->next, idx++)
        {
            if (idx % 2 == 0)
            {
                Node *temp = cur;

                if (tail == cur)
                    tail = prv;

                prv->next = cur->next;
                cur = prv;
                delete_node(temp);
            }
            prv = cur;
        }

        debug_verify_data_integrity();
    }

    void insert_sorted(int value)
    {
        Node *node = new Node{value};
        add_node(node);

        if (!head)
        {
            head = tail = node;
            debug_verify_data_integrity();

            return;
        }

        for (Node *cur = head, *prv = nullptr; cur; cur = cur->next)
        {
            if (node->data < cur->data)
            {
                node->next = cur;

                if (prv)
                    prv->next = node;

                if (!prv)
                    head = node;

                debug_verify_data_integrity();

                return;
            }
            prv = cur;
        }

        tail->next = node;
        tail = node;
        debug_verify_data_integrity();

        return;
    }

    void swap_head_tail_nodes()
    {
        if (!head || head == tail)
        {
            return;
        }
        else if (head->next == tail)
        {
            tail->next = head;
            head->next = nullptr;
        }
        else
        {
            Node *before_tail{nullptr};

            for (Node *cur{head}; cur; cur = cur->next)
                if (cur->next == tail)
                    before_tail = cur;

            tail->next = head->next;
            head->next = nullptr;
            before_tail->next = head;
        }

        swap(head, tail);
        debug_verify_data_integrity();
        return;
    }

    void left_rotate(int k)
    {
        k = k % length;

        for (int i{0}; i < k; i++)
        {
            Node *new_tail = head;
            head = head->next;
            tail->next = new_tail;
            new_tail->next = nullptr;
            tail = new_tail;
        }
        debug_verify_data_integrity();
        return;
    }

    void remove_duplicates()
    {
        set<int> s;
        for (Node *cur{head}, *prv{nullptr}; cur; cur = cur->next)
        {
            if (s.find(cur->data) != s.end())
            {
                prv->next = cur->next;
                if (cur == tail)
                    tail = prv;
                delete_node(cur);
                cur = prv;
            }
            else
            {
                s.insert(cur->data);
            }
            prv = cur;
        }
        debug_verify_data_integrity();
        return;
    }
};

int main()
{
    LinkedList ll;

    ll.insert_end(1);
    ll.insert_end(2);
    ll.insert_end(1);
    ll.insert_end(3);
    ll.insert_end(2);
    ll.insert_end(4);
    ll.insert_end(3);
    ll.insert_end(5);
    ll.insert_end(2);

    ll.print();
    ll.remove_duplicates();
    ll.print();

    LinkedList l2;
    l2.insert_end(1);
    l2.insert_end(2);
    l2.insert_end(3);
    l2.insert_end(4);
    l2.insert_end(5);

    l2.print();
    l2.remove_duplicates();
    l2.print();

    LinkedList l3;
    l3.insert_end(1);
    l3.insert_end(1);
    l3.insert_end(1);

    l3.print();
    l3.remove_duplicates();
    l3.print();

    return 0;
}