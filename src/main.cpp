#include "main.hpp"
#include "GlobalNamespace/PlayerHeightSettingsController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "../include/height-setting.hpp"

static ModInfo modInfo;

HeightSetting* heightSetting;

/* Temporary config while I'm working on the main
   features for the mod */
bool flickerE = false;
int meterPrecision = 2;
bool useImperial = false; 


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

// Gameplay hooks

/* Hooks up to Player Height UI refresh, and doesn't run original code
   Runs my version of code that has Imperial height, and more Precision */
MAKE_HOOK_OFFSETLESS(PlayerHeightSettingsController_RefreshUI, void, GlobalNamespace::PlayerHeightSettingsController *self)
{
    heightSetting = new HeightSetting();
    heightSetting->SetUseImperial(useImperial);
    heightSetting->SetMeterPrecision(meterPrecision);
    heightSetting->SetHeight(self->value);
    Il2CppString *heightText = il2cpp_utils::createcsstr(heightSetting->GetHeightText());
    self->text->SetText(heightText);
    delete heightSetting;
}

/* Hooks up to the OnEnable method for Flickering Neon Sign
   And disables it with preventing to call the Flickering Coroutine */
MAKE_HOOK_OFFSETLESS(FlickeringNeonSign_OnEnable, void, Il2CppObject* self)
{
    if(!flickerE) return;
    FlickeringNeonSign_OnEnable(self);
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
    INSTALL_HOOK_OFFSETLESS(getLogger(), FlickeringNeonSign_OnEnable, il2cpp_utils::FindMethodUnsafe("", "FlickeringNeonSign", "OnEnable", 0));
    getLogger().info("Installed all hooks!");
}