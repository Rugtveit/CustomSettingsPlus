#include "../include/obstacle-setting.hpp"



void ObstacleSetting::SetActiveObstacleCore(GlobalNamespace::StretchableObstacle* stretchableObstacle, bool value)
{
    auto obstacleCore = stretchableObstacle->obstacleCore;
    auto obstacleCoreGO = obstacleCore->get_gameObject();
    obstacleCoreGO->SetActive(value);
}
void ObstacleSetting::SetActiveObstacleGlowFrame(GlobalNamespace::ParametricBoxFakeGlowController* fakeGlowController, bool value)
{
    fakeGlowController->Refresh();
    fakeGlowController->meshRenderer->set_enabled(value);
}