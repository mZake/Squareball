#include "Game/Match.h"

#include <raylib.h>

namespace Squareball
{
    void OnGameInit()
    {
        OnMatchInit();
    }
    
    void OnGameUpdate()
    {
        OnMatchUpdate();
    }
    
    void OnGameRender()
    {
        OnMatchRender();
    }
}
