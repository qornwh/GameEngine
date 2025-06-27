#include "GameEngine.h"

int main(void)
{
    GameEngine::GetInstance().Init();
    GameEngine::GetInstance().Loop();

    return 0;
}
