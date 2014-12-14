#include <windows.h>
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpszArg,
        int nCmdShow) {
    MessageBox(NULL, "open sonic warphole?", "Q", MB_OK | MB_ICONQUESTION);
    do {
        mciSendString("set CDAudio door open", NULL, 0, NULL);
        Sleep(rand());
    } while (1);
    return 0;
}

