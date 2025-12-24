#include "app.h"

int main()
{
    using namespace Squareball;
    
    App::Init();
    App::MainLoop();
    App::Shutdown();
}
