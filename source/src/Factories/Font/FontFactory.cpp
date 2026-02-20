#include "Factory/Font/FontFactory.h"

#include <filesystem>

#include "imgui.h"

std::unique_ptr<FontFactory> FontFactory::_fontFamilyInstance = nullptr;

FontFactory::FontFactory()
{
    std::filesystem::path resourceDir = RESOURCE_DIR;

    auto path {resourceDir / "fonts/faith.ttf"};

    ImGuiIO& io {ImGui::GetIO()};

    _fontFamilies.emplace(ROBOTO_REGULAR, io.Fonts->AddFontFromFileTTF(path.c_str()));
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
    return _fontFamilies.at(fontFamilyType).get();
}