#include "../basicDLL/dll.hpp"

class DLL : public BasicDLL {
    public:
    DLL() = default;
    DLL(const std::initializer_list<int>& lst): BasicDLL(lst)
    {
    }

};