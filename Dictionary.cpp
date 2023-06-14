#include "Dictionary.hpp"

Dictionary::Dictionary()
{
    size = FirstCode;
    for (int i = 0; i < size; ++i)
    {
        entries[i].code  = Nil;
        entries[i].value = i;
    }
}

int Dictionary::findIndex(const int code, const int value) const
{
    if (code == Nil)
    {
        return value;
    }

    for (int i = 0; i < size; ++i)
    {
        if (entries[i].code == code && entries[i].value == value)
        {
            return i;
        }
    }

    return Nil;
}

bool Dictionary::add(const int code, const int value)
{
    if (size == MaxDictEntries)
    {
        cout<<"Dictionary overflowed!"<<endl;
        return false;
    }

    entries[size].code  = code;
    entries[size].value = value;
    ++size;
    return true;
}

bool Dictionary::flush(int & codeBitsWidth)
{
    if (size == (1 << codeBitsWidth))
    {
        ++codeBitsWidth;
        if (codeBitsWidth > MaxDictBits)
        {
            codeBitsWidth = StartBits;
            size = FirstCode;
            return true;
        }
    }
    return false;
}