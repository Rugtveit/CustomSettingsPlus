#include "main.hpp"
#include "GlobalNamespace/PlayerHeightSettingsController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/BasicUIAudioManager.hpp"
#include "GlobalNamespace/RandomObjectPicker_1.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/SongPreviewPlayer_AudioSourceVolumeController.hpp"
#include "GlobalNamespace/NoteCutSoundEffect.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "../include/height-setting.hpp"

static ModInfo modInfo;

HeightSetting *heightSetting;

/* Temporary config while I'm working on the main
   features for the mod */
bool flickerE = false;
int meterPrecision = 2;
bool useImperial = false;
float clickAudioVolume = 1.0f;
float previewAudioVolume = 0.05f;
float goodCutVolume = 0.0f;
float badCutVolume = 1.0f;

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

// Menu hooks

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
MAKE_HOOK_OFFSETLESS(FlickeringNeonSign_OnEnable, void, Il2CppObject *self)
{
    if (!flickerE) return;
    FlickeringNeonSign_OnEnable(self);
}

/* Hooks up to the Audio Manager that handles button click sounds and
   I rewrite the code as audio level is hardcoded. */
MAKE_HOOK_OFFSETLESS(BasicUIAudioManager_HandleButtonClickEvent, void, GlobalNamespace::BasicUIAudioManager *self)
{
    UnityEngine::AudioClip *audioClip = self->randomSoundPicker->PickRandomObject();
    if (!audioClip) return;
    self->audioSource->set_pitch(1.0f); // Supposed to be random but min and max pitch is 1 so it's not necessary but could be changed in the future.
    self->audioSource->PlayOneShot(audioClip, clickAudioVolume);
}

MAKE_HOOK_OFFSETLESS(SongPreviewPlayer_Start, void, GlobalNamespace::SongPreviewPlayer* self)
{
    self->volume = previewAudioVolume;
    SongPreviewPlayer_Start(self);
}

MAKE_HOOK_OFFSETLESS(NoteCutSoundEffect_Start, void, GlobalNamespace::NoteCutSoundEffect* self)
{
    self->badCutVolume = badCutVolume; 
    self->goodCutVolume = goodCutVolume;
    NoteCutSoundEffect_Start(self);
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
    getLogger().info("Finding methods...");
    auto PlayerHeightSC_RefreshUI = il2cpp_utils::FindMethodUnsafe("", "PlayerHeightSettingsController", "RefreshUI", 0);
    auto FlickeringSign_OnEnable = il2cpp_utils::FindMethodUnsafe("", "FlickeringNeonSign", "OnEnable", 0);
    auto UIAudioManager_ButtonClick = il2cpp_utils::FindMethodUnsafe("", "BasicUIAudioManager", "HandleButtonClickEvent", 0);
    auto SongPreview_Start = il2cpp_utils::FindMethodUnsafe("", "SongPreviewPlayer", "Start", 0);
    auto CutSoundEffect_Start = il2cpp_utils::FindMethodUnsafe("", "NoteCutSoundEffect", "Start", 0);
    getLogger().info("Found all methods!");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(getLogger(), PlayerHeightSettingsController_RefreshUI, PlayerHeightSC_RefreshUI);
    INSTALL_HOOK_OFFSETLESS(getLogger(), FlickeringNeonSign_OnEnable, FlickeringSign_OnEnable);
    INSTALL_HOOK_OFFSETLESS(getLogger(), BasicUIAudioManager_HandleButtonClickEvent, UIAudioManager_ButtonClick);
    INSTALL_HOOK_OFFSETLESS(getLogger(), SongPreviewPlayer_Start, SongPreview_Start);
    INSTALL_HOOK_OFFSETLESS(getLogger(), NoteCutSoundEffect_Start, CutSoundEffect_Start);
    getLogger().info("Installed all hooks!");
}
