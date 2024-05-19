#include "../basicDLL/dll.hpp"

class DLL : public BasicDLL {
    public:
    DLL() = default;
    DLL(const std::initializer_list<int>& lst): BasicDLL(lst)
    {
    }

    void reverse(){
        Node* current = head.get();
        Node* prev = nullptr;
        Node* next = nullptr;
        if(current){
            prev = current->prev;
            next = current->next.get();
        }

        while(current){
            current->next.release();
            current->next.reset(prev);
            current->prev = next;

            current = current->prev;
            if(current){
                prev = current->prev;
                next = current->next.get();
            }

        }

        Node* temp = head.release();
        head.reset(tail);
        tail = temp;

        debug_verify_data_integrity();
    }
};

void test_empty_dll(void);
void test_1_dll(void);
void test_odd_dll(void);
void test_even_dll(void);

int main() {
    test_empty_dll();
    test_1_dll();
    test_odd_dll();
    test_even_dll();

    return 0;
}

void test_empty_dll(){

    std::cout << "=================Empty DLL Begin==================\n";

    DLL dll {};
    std::cout << "Current DLL : " << dll << "\n";
    dll.reverse();
    std::cout << "Reversed DLL : " << dll << "\n";

    std::cout << "=================Empty DLL Test End==================\n";
}

void test_1_dll(){

    std::cout << "================= DLL with 1 element Begin==================\n";

    DLL dll {1};
    std::cout << "Current DLL : " << dll << "\n";
    dll.reverse();
    std::cout << "Reversed DLL : " << dll << "\n";
    std::cout << "================= DLL with 1 element End==================\n";
}

void test_odd_dll(){

    std::cout << "================= DLL with odd element Begin==================\n";

    DLL dll {1,2,3};

    std::cout << "Current DLL : " << dll << "\n";
    dll.reverse();
    std::cout << "Reversed DLL : " << dll << "\n";

    std::cout << "================= DLL with odd element End==================\n";
}


void test_even_dll(){

    std::cout << "================= DLL with even element Begin==================\n";

    DLL dll {6, 10, 8, 15};

    std::cout << "Current DLL : " << dll << "\n";
    dll.reverse();
    std::cout << "Reversed DLL : " << dll << "\n";

    std::cout << "================= DLL with even element End==================\n";
}
