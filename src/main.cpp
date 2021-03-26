#include "main.hpp"
#include "GlobalNamespace/PlayerHeightSettingsController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "../include/height-setting.hpp"

static ModInfo modInfo;

HeightSetting* heightSetting;

Configuration &getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

Logger &getLogger()
{
    LoggerOptions log = LoggerOptions(false, false);
    static Logger *logger = new Logger(modInfo, log);
    return *logger;
}

/* Hooks up to Player Height UI refresh, and doesn't run original code
   Runs my version of code that has Imperial height, and more Precision */
MAKE_HOOK_OFFSETLESS(PlayerHeightSettingsController_RefreshUI, void, GlobalNamespace::PlayerHeightSettingsController *self)
{
    heightSetting = new HeightSetting();
    heightSetting->SetUseImperial(false);
    heightSetting->SetMeterPrecision(2);
    heightSetting->SetHeight(self->value);
    Il2CppString *heightText = il2cpp_utils::createcsstr(heightSetting->GetHeightText());
    self->text->SetText(heightText);
    delete heightSetting;
}

extern "C" void setup(ModInfo &info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getConfig().Load();
    getLogger().info("Completed setup!");
}

extern "C" void load()
{
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(getLogger(), PlayerHeightSettingsController_RefreshUI, il2cpp_utils::FindMethodUnsafe("", "PlayerHeightSettingsController", "RefreshUI", 0));
    getLogger().info("Installed all hooks!");
}