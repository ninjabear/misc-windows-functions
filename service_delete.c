#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, GENERIC_ALL);
    SC_HANDLE hService = OpenService(hSCM,
            argv[1],
            SERVICE_ALL_ACCESS);
    if (hService == NULL) {
        printf("OpenService Failure! %d\n", GetLastError());
    }
    if (DeleteService(hService) == 0) {
        printf("DeleteService Failure! %d\n", GetLastError());
    }
    return 0;
}
