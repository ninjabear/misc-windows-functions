
// kill -p <pid>
// kill -n <name>
// rectifies incapacity to remove "system critical" processes in taskman

BOOL FindAndKillProcess(const char* pszProcName) {
    HANDLE hProcSnap;
    PROCESSENTRY32 pe32;
    int nKillCount = 0;
    // this is my critical processes list
    char *critical[] = {"svchost.exe", "alg.exe", "explorer.exe", "lsass.exe", "winlogon.exe", "csrss.exe",
        "smss.exe", "services.exe", "System", "[System Process]", NULL};
    // cmd because thats what we might look like
    // handle NON_CRITICAL     
    if (strcmp(pszProcName, "NON_CRITICAL") == 0) {
        hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcSnap != INVALID_HANDLE_VALUE) {
            Process32First(hProcSnap, &pe32);
            do {
                int i = 0;
                BOOL bCritical = FALSE;
                if (pe32.th32ProcessID == GetCurrentProcessId())
                    continue;
                while (critical[i] != NULL) {
                    if (strcmp(pe32.szExeFile, critical[i]) == 0) {
                        bCritical = TRUE;
                        break;
                    }
                    ++i;
                }
                if (bCritical == FALSE) {
                    KillProcess(pe32.th32ProcessID);
                }
            } while (Process32Next(hProcSnap, &pe32));
            return SUCCESS;
        }
        return FAILURE;
    }
    // assume its the name of a process
    hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcSnap != INVALID_HANDLE_VALUE) {
        //printf("killing all instances of %s... \n", pszProcName);
        Process32First(hProcSnap, &pe32);
        do {
            if (strcmp(pe32.szExeFile, pszProcName) == 0) {
                if (KillProcess(pe32.th32ProcessID) == SUCCESS) {
                    nKillCount++;
                }
            }
        } while (Process32Next(hProcSnap, &pe32));
        CloseHandle(hProcSnap);
        //printf("killed %d processes", nKillCount);
        return SUCCESS;
    } else {
        //printf("couldn't create process snapshot\n");
        return FAILURE;
    }
}

BOOL KillProcess(int nPid) {
    HANDLE hProc;
    //printf ("attempting to kill pid %d... ", nPid);
    hProc = OpenProcess(PROCESS_TERMINATE,
            0,
            nPid);
    if (TerminateProcess(hProc, -1)) {
        //printf("success!\n");
        return SUCCESS;
    } else {
        //printf("failure! (%d)\n", GetLastError());
        return FAILURE;
    }
}
