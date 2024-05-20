#include "../basicDLL/dll.hpp"

class DLL : public BasicDLL {
    public:
    DLL() = default;
    DLL(const std::initializer_list<int>& lst): BasicDLL(lst)
    {
    }

    void merge_2_sorted_lists(DLL &other){
        if(tail->data < other.head->data){
            Node* other_cur = other.head.get();
            while(other_cur){
                insert_end(other_cur->data);
                other_cur = other_cur->next.get();
            }
            return;
        }

        if(other.tail->data < head->data){
            Node* other_cur = other.tail;
            while(other_cur){
                insert_front(other_cur->data);
                other_cur = other_cur->prev;
            }
            return;
        }

        Node* cur = head.get();
        Node* other_cur = other.head.get();

        while(cur && other_cur){
            if (other_cur->data < cur->data){
                embed_before(cur, other_cur->data);
                other_cur = other_cur->next.get();
                cur = cur->prev;
            }
            cur = cur->next.get();
        }

        while(other_cur){
            insert_end(other_cur->data);
            other_cur = other_cur->next.get();
        }

        debug_verify_data_integrity();
        return;
    }

};

void test_2nd_dll_is_smaller(void);
void test_2nd_dll_is_bigger(void);
void test_2nd_dll_with_elem_after_before_1st(void);
void test_2nd_dll_shorter_than_1st(void);
void test_1st_dll_shorter_than_2nd(void);
void test_course_example(void);

int main() {
    test_2nd_dll_is_smaller();
    test_2nd_dll_is_bigger();
    test_2nd_dll_with_elem_after_before_1st();
    test_2nd_dll_shorter_than_1st();
    test_1st_dll_shorter_than_2nd();
    test_course_example();

    return 0;
}

void test_2nd_dll_is_smaller(void){
    std::cout << "=================Merge 2nd DLL is small==================\n";
    DLL dll1 {6, 7, 8, 9, 10};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2  {1, 2,3, 4,5};
    std::cout << "Second dll : " << dll2 << "\n";

    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";
   
    return;
}

void test_2nd_dll_is_bigger(void){
    std::cout << "=================Merge 2nd DLL is Big==================\n";
    DLL dll1 {1, 2,3, 4,5};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2 {6, 7, 8, 9, 10};
    std::cout << "Second dll : " << dll2 << "\n";
    
    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";
    
    return;
}

void test_2nd_dll_with_elem_after_before_1st(void){

    std::cout << "=================Test 2nd DLL With Elements After and Before 1st==================\n";
    DLL dll1 {6, 7, 8, 9, 10};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2  {2, 3,4, 12,14, 15};
    std::cout << "Second dll : " << dll2 << "\n";

    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";

    return;
}

void test_2nd_dll_shorter_than_1st(void){
    std::cout << "=================Test 2nd DLL Shorter than 1st=================\n";
    DLL dll1 {6, 7, 8, 9, 10};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2  {2, 3,4};
    std::cout << "Second dll : " << dll2 << "\n";

    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";

    return;
}

void test_1st_dll_shorter_than_2nd(void){
    std::cout << "=================Test 1st dll shorter than 2nd================\n";
    DLL dll1 {6, 7};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2  {2, 3, 4, 9, 11, 13};
    std::cout << "Second dll : " << dll2 << "\n";

    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";

    return;
}

void test_course_example(void){
    std::cout << "=================Course Test Example===============\n";
    DLL dll1 {10, 20, 30, 40, 50};
    std::cout << "First dll : " << dll1 << "\n";

    DLL dll2  {15, 17, 22, 24, 35};
    std::cout << "Second dll : " << dll2 << "\n";

    dll1.merge_2_sorted_lists(dll2);
    std::cout << dll1 << "\n";

    return;
}