#ifndef INPUTSTRING_H
#define INPUTSTRING_H

#include <string>

enum StringObjectType {
    WORD,
    SENTENCE,
    CHARACTER
};

enum StringObjectModifier {
    BIG = 0x1,
    SHORT = 0x2,
    LONG = 0x4
};

class InputString
{
public:
    InputString(std::string str) : str(str) {}
    bool startsWith(int count, StringObjectType type, StringObjectModifier modifiers);
    std::string read(int count, StringObjectType type);
private:
    std::string str;
};

#endif // INPUTSTRING_H
