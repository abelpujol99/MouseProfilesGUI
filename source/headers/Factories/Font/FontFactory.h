#pragma once
#include <memory>
#include <unordered_map>

#include "FontFamilyTypes.h"

struct ImFont;

class FontFactory
{
public:

    static FontFactory& GetInstance();

    ImFont* GetFontFamily(FontFamilyTypes fontFamilyType) const;

private:

    FontFactory();

    static std::unique_ptr<FontFactory> _fontFamilyInstance;

    std::unordered_map<FontFamilyTypes, std::unique_ptr<ImFont>> _fontFamilies;

};
