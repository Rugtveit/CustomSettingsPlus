#include "GlobalNamespace/StretchableObstacle.hpp"
#include "GlobalNamespace/ParametricBoxFakeGlowController.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

class ObstacleSetting
{
    public: 
        static void SetActiveObstacleCore(GlobalNamespace::StretchableObstacle* stretchableObstacle, bool value);
        static void SetActiveObstacleGlowFrame(GlobalNamespace::ParametricBoxFakeGlowController* fakeGlowController, bool value); 
};