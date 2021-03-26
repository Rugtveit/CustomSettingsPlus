#pragma once

#include "modloader/shared/modloader.hpp"

#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "GlobalNamespace/PlayerHeightSettingsController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/BasicUIAudioManager.hpp"
#include "GlobalNamespace/RandomObjectPicker_1.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/SongPreviewPlayer_AudioSourceVolumeController.hpp"
#include "GlobalNamespace/NoteCutSoundEffect.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"
#include "GlobalNamespace/StretchableObstacle.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "../include/height-setting.hpp"
#include "../include/obstacle-settings.hpp"

Configuration& getConfig();
Logger& getLogger();