#pragma once

namespace Squareball
{
    using UpdateCallback = void(*)(float);
    using RenderCallback = void(*)();

    void SetGameUpdateCallback(UpdateCallback cb);
    void SetGameRenderCallback(RenderCallback cb);

    void GameMain();
}
