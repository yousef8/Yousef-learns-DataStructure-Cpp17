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
    Node *move(Node *cur, int k)
    {
        for (int i{1}; (i <= k) && cur; i++)
            cur = cur->next;
        return cur;
    }

    pair<Node *, Node *> make_chain(Node *cur, int k)
    {
        Node *chain_tail = cur;
        Node *chain_head = move(chain_tail, k - 1);
        if (!chain_head)
            chain_head = chain_tail;
        Node *prv{nullptr};

        for (int i{0}; cur && i < k; i++)
        {
            Node *temp = cur->next;
            cur->next = prv;
            prv = cur;
            cur = temp;
        }

        if (chain_tail == head)
            head = chain_head;

        if (chain_head == tail)
            tail = chain_tail;

        return {chain_head, chain_tail};
    }

    void reverse_chains(int k)
    {
        pair<Node *, Node *> prv_chain{nullptr, nullptr};

        for (Node *cur{head}; cur;)
        {
            Node *chain_begin = cur;
            cur = move(cur, k);
            pair<Node *, Node *> cur_chain = make_chain(chain_begin, k);

            if (prv_chain.first)
            {
                prv_chain.second->next = cur_chain.first;
                prv_chain = cur_chain;
            }
            else
            {
                prv_chain = cur_chain;
            }
        }

        debug_verify_data_integrity();
    }
};

int main()
{
    LinkedList l1{1, 2, 3, 4, 5, 6};
    LinkedList l2{1, 2, 3, 4, 5, 6};
    LinkedList l3{1, 2, 3, 4, 5, 6, 7};

    l1.print();
    l1.reverse_chains(6);
    l1.print();

    cout << "\n";
    l2.print();
    l2.reverse_chains(3);
    l2.print();

    cout << "\n";
    l3.print();
    l3.reverse_chains(2);
    l3.print();

    return 0;
}
