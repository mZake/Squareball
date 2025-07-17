#include "State.h"

#include "States/Match.h"

namespace Squareball
{
    GameState RunState(GameState state)
    {
        if (state == GameState::Match)
            return RunMatch();
        
        return GameState::None;
    }
}
