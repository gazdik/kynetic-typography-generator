#ifndef INPUTSTRING_H
#define INPUTSTRING_H

#include <string>
#include <regex>
#include <cctype>
#include <algorithm>
#include <cassert>

enum StringObjectType {
    SOT_WORD,
    SOT_SENTENCE,
    SOT_CHARACTER
};

enum StringObjectModifier {
    SOM_BIG = 0x1,
    SOM_SHORT = 0x2,
    SOM_MEDIUM = 0x4,
    SOM_LONG = 0x8,
};

class InputString
{
public:
    InputString(std::string str);

    bool startsWith(int count, StringObjectType type, int modifiers = 0) const;

    std::string read(int count, StringObjectType type, bool pop = true);
    std::string readAll(bool pop = true);
    static std::string read(int count, StringObjectType type, bool pop, std::string &str);

    bool isEmpty();

    static std::string trim(const std::string &s);

    static void test();
private:

    std::string str;
    static const std::regex sentenceRegex;
    static const std::regex wordRegex;
    static const std::regex characterRegex;
    static const std::regex bigWordRegex;
    static const std::regex bigWordReplaceRegex;
    static const std::regex collapseSpacesRegex;
};

#endif // INPUTSTRING_H
