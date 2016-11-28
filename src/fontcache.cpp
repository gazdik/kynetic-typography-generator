#include "fontcache.h"

FontCache *FontCache::getInstance()
{
    static FontCache instance;
    return &instance;
}

FTFont *FontCache::font(std::string const &name)
{
    if (!fonts.count(name)) {

        FTFont *font = new FTExtrudeFont(
            (std::string("fonts/") + name + ".ttf").c_str());

        if(font->Error())
        {
            std::ostringstream ss;
            ss << "Could not load font '" << name << "'" << std::endl;
            throw std::runtime_error(ss.str());
        }

        //font->ShaderLocations(_aPosition, _aNormal, _uPen);
        font->FaceSize(70);
        font->Depth(3);
        font->CharMap(ft_encoding_unicode);

        fonts[name] = font;
    }

    return fonts[name];
}

FontCache::~FontCache()
{
    for (auto const &iter : fonts) {
        delete(iter.second);
    }
}

FontCache::FontCache()
{
}
