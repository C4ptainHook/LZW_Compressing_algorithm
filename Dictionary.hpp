#include <iostream>
#include <cassert>
using namespace std;

constexpr int Nil            = -1;
constexpr int MaxDictBits    = 16;
constexpr int StartBits      = 9;
constexpr int FirstCode      = (1 << (StartBits - 1));
constexpr int MaxDictEntries = (1 << MaxDictBits);

class Dictionary final
{
public:

    struct Entry
    {
        int code;
        int value;
    };

    int size;
    Entry entries[MaxDictEntries];

    Dictionary();
    int findIndex(int code, int value) const;
    bool add(int code, int value);
    bool flush(int & codeBitsWidth);
};