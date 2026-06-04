#pragma once
#include <memory>
#include <unordered_map>
#include "imgui.h"

enum class FontFamilyTypes;

class FontFactory
{
public:
    
    FontFactory(const FontFactory& other) = delete;
    FontFactory& operator=(const FontFactory& other) = delete;
    FontFactory(FontFactory&& other) = delete;
    FontFactory&& operator=(FontFactory&& other) = delete;

    static FontFactory& GetInstance();

    ImFont* GetFontFamily(FontFamilyTypes fontFamilyType) const;

private:

    FontFactory();

    static std::unique_ptr<FontFactory> _fontFamilyInstance;

    std::unordered_map<FontFamilyTypes, ImFont*> _fontFamilies;

};