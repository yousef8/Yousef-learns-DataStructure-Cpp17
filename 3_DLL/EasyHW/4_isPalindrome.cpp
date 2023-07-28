#include "../basicDLL/dll.hpp"
#include <initializer_list>

class DLL : public BasicDLL {
public:
  DLL() = default;

  DLL(const std::initializer_list<int> &lst) : BasicDLL(lst) {}

  DLL(const DLL &another) = delete;
  DLL &operator=(const DLL &another) = delete;

  bool is_palindrome() {

    for (Node *lcur{head.get()}, *rcur{tail}; lcur->next.get() != rcur->prev;
         lcur = lcur->next.get(), rcur = rcur->prev)
      if (lcur->data != rcur->data)
        return false;
    return true;
  }
};

void test1() {
  std::cout << "\n\ntest 1\n";

  DLL ll{1, 2, 2, 1};
  std::cout << ll << "\n";

  std::cout << "Is Palindrome : ";

  bool result = ll.is_palindrome();
  std::cout << result << "\n";

  bool expected = true;
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult : " << result
              << "\n";
    assert(false);
  }
  ll.debug_print_list("******************");
}

void test2() {
  std::cout << "\n\ntest 2\n";

  DLL ll{1, 2, 3, 2, 1};
  std::cout << ll << "\n";

  bool result = ll.is_palindrome();
  std::cout << "Is Palindrome : " << result << "\n";

  bool expected = true;
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult : " << result
              << "\n";
    assert(false);
  }
  ll.debug_print_list("******************");
}
void test3() {
  std::cout << "\n\ntest 3\n";

  DLL ll{1, 2, 3, 4, 2, 1};
  std::cout << ll << "\n";

  bool result = ll.is_palindrome();
  std::cout << "Is Palindrome : " << result << "\n";

  bool expected = false;
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult : " << result
              << "\n";
    assert(false);
  }
  ll.debug_print_list("******************");
}

int main() {
  test1();
  test2();
  test3();
  std::cout << "\n\n NO RTE\n";
  return 0;
}
