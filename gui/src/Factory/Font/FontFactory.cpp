#include "Factory/Font/FontFactory.h"

#include <filesystem>
#include <utility>

#include "imgui_internal.h"
#include "TextDefines.h"
#include "Factory/ImGuiFactory.h"
#include "Factory/Font/FontFamilyTypes.h"

std::unique_ptr<FontFactory> FontFactory::_fontFamilyInstance = nullptr;

FontFactory::FontFactory()
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    auto path {resourceDir / "fonts/Roboto-Medium.ttf"};

    _fontFamilies.emplace(FontFamilyTypes::ROBOTO_REGULAR, ImGuiFactory::CreateFont(path.c_str()));

    _fontBackedFamilies.emplace(FontFamilyTypes::ROBOTO_REGULAR, _fontFamilies.at(FontFamilyTypes::ROBOTO_REGULAR)->GetFontBaked(BASE_FONT_SIZE));

    _fontsSizes.emplace(FontFamilyTypes::ROBOTO_REGULAR, [&](uint32_t codePoint)
    {
        if (!_robotoSizes.contains(codePoint))
        {
            _robotoSizes.emplace(codePoint, _fontBackedFamilies.at(FontFamilyTypes::ROBOTO_REGULAR)->FindGlyph(static_cast<ImWchar>(codePoint))->AdvanceX);
        }

        return _robotoSizes.at(codePoint);
    });
}

FontFactory& FontFactory::GetInstance()
{
    if (_fontFamilyInstance == nullptr)
    {
        _fontFamilyInstance.reset(new FontFactory());
    }

    return *_fontFamilyInstance;
}

ImFont* FontFactory::GetFontFamily(FontFamilyTypes fontFamilyType) const
{
    return _fontFamilies.at(fontFamilyType);
}

float FontFactory::GetTextReferenceWidth(const FontFamilyTypes& fontFamily, std::string text) const
{
    float totalWidth {0};

    const char* characters {text.c_str()};

    while (*characters)
    {
        uint32_t codepoint;

        characters += ImTextCharFromUtf8(&codepoint, characters, nullptr);

        totalWidth += _fontsSizes.at(fontFamily)(codepoint);
    }

    return totalWidth;
}
