#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <map>
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

    [[nodiscard]] ImFont* GetFontFamily(FontFamilyTypes fontFamilyType) const;

    [[nodiscard]] float GetTextReferenceWidth(const FontFamilyTypes& fontFamily, std::string text) const;

private:

    FontFactory();

    static std::unique_ptr<FontFactory> _fontFamilyInstance;

    std::map<FontFamilyTypes, ImFont*> _fontFamilies;

    std::map<FontFamilyTypes, ImFontBaked*> _fontBackedFamilies;

    std::map<FontFamilyTypes, std::function<float(uint32_t)>> _fontsSizes;

    std::map<uint32_t, float> _robotoSizes;

};