// ##############################################
//             Platform-Independed
// ##############################################

// ##############################################
//              Windows Platform
// ##############################################
#if _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

int WINAPI WinMain(
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR     lpCmdLine,
   int       nCmdShow
){
    return 0;
}

#endif
