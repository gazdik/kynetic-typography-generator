#include "inputstring.h"

const std::regex InputString::sentenceRegex("^[^.!?]+[.!?]+");
const std::regex InputString::wordRegex("^[^ ]+");
const std::regex InputString::bigWordRegex("^[*]([^ *]+)[*]");
const std::regex InputString::bigWordReplaceRegex("[*]([^ *]+)[*]");
const std::regex InputString::characterRegex("^[^ ]");
const std::regex InputString::collapseSpacesRegex("[[:space:]]+");

InputString::InputString(std::string str) {
    this->str = trim(str);
    this->str = std::regex_replace(this->str, collapseSpacesRegex, " ");
}

std::string InputString::trim(const std::string &s)
{
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

bool InputString::startsWith(int count, StringObjectType type, StringObjectModifier modifiers) const
{
    std::string remaining = str;
    std::smatch match;

    for (int i = 0; i < count; ++i) {

        switch (type) {
        case SOT_CHARACTER:
            if (modifiers != 0 ||
                !std::regex_search(remaining, match, characterRegex)
            ) {
                return false;
            }
            break;

        case SOT_WORD: {
            if (!std::regex_search(remaining, match, wordRegex) ||
                (modifiers & SOM_BIG && !std::regex_search(remaining, match, bigWordRegex))
            ) {
                return false;
            }

            if (modifiers & (SOM_MEDIUM | SOM_LONG | SOM_SHORT)) {
                std::string::size_type s = read(1, type, false, remaining).size();
                if ((modifiers & SOM_SHORT && s > 2) ||
                    (modifiers & SOM_LONG && s < 8) ||
                    (modifiers & SOM_MEDIUM && (s <= 2 || s >= 8))
                ) {
                    return false;
                }
            }

            break;
        }

        case SOT_SENTENCE:
            if (modifiers != 0 ||
                !std::regex_search(remaining, match, sentenceRegex)
            ) {
                return false;
            }
            break;
        }

        remaining = match.suffix().str();
        remaining = trim(remaining);
    }

    return true;
}
std::string InputString::read(int count, StringObjectType type, bool pop)
{
    return read(count, type, pop, str);
}

std::string InputString::read(int count, StringObjectType type, bool pop, std::string &str)
{
    std::ostringstream outStr;
    std::string remaining = str;
    std::smatch match;
    std::string final;

    for (int i = 0; i < count; ++i) {

        switch (type) {
        case SOT_CHARACTER:
            if (!std::regex_search(remaining, match, characterRegex)) {
                return "";
            }
            break;

        case SOT_WORD: {
            if (!std::regex_search(remaining, match, wordRegex)) {
                return "";
            }
            break;
        }

        case SOT_SENTENCE:
            if (!std::regex_search(remaining, match, sentenceRegex)) {
                return "";
            }
            break;
        }

        outStr << match[0].str() << " ";
        remaining = match.suffix().str();
        remaining = trim(remaining);
    }

    if (pop) {
        str = remaining;
    }

    // Get final result from stream
    final = outStr.str();

    // Remove stars
    final = std::regex_replace(final, bigWordReplaceRegex, "$1");

    // Remove trailing space
    if (final.size() > 0) {
        final = final.substr(0, final.size() - 1);
    }

    return final;
}

std::string InputString::readAll(bool pop)
{
    std::string s = str;
    if (pop) {
        str = "";
    }
    return s;
}

bool InputString::isEmpty()
{
    return str.empty();
}

void InputString::test() {
    InputString str("  *Ahoj*, tohle je *moje* první věta. Tak uvidíme, co z *ní* vzejde!! \n pecka... ");
    assert(str.startsWith(1, SOT_WORD));
    assert(str.startsWith(13, SOT_WORD));
    assert(!str.startsWith(14, SOT_WORD));
    assert(str.startsWith(1, SOT_SENTENCE));
    assert(str.startsWith(3, SOT_SENTENCE));
    assert(!str.startsWith(4, SOT_SENTENCE));

    assert(str.read(1, SOT_WORD, false) == "Ahoj,");
    assert(str.startsWith(1, SOT_WORD, SOM_BIG));
    assert(!str.startsWith(1, SOT_WORD, SOM_SHORT));
    assert(!str.startsWith(1, SOT_WORD, SOM_LONG));
    assert(str.read(2, SOT_WORD, true) == "Ahoj, tohle");
    assert(!str.startsWith(1, SOT_WORD, SOM_BIG));
    assert(str.read(1, SOT_CHARACTER, true) == "j");
    assert(str.read(1, SOT_CHARACTER, true) == "e");
    assert(str.startsWith(1, SOT_WORD, SOM_BIG));
    assert(str.read(1, SOT_SENTENCE, true) == "moje první věta.");
    assert(str.read(3, SOT_SENTENCE, true) == "");
    assert(str.read(3, SOT_WORD, false) == "Tak uvidíme, co");
    assert(str.read(1, SOT_WORD, true) == "Tak");
    assert(str.read(1, SOT_SENTENCE, true) == "uvidíme, co z ní vzejde!!");
    assert(str.read(1, SOT_WORD, true) == "pecka...");
}
