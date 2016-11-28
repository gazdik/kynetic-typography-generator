#ifndef FONTCACHE_H
#define FONTCACHE_H

#include <string>
#include <sstream>
#include <map>
#include <FTGL/ftgl.h>

class FontCache
{
public:
    static FontCache *getInstance();

    ~FontCache();
    FTFont *font(std::string const &name);

protected:
    FontCache();

private:
    std::map<std::string, FTFont*> fonts;
};

#endif // FONTCACHE_H
