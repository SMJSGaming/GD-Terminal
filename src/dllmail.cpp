#include <MinHook.h>

#include "includes.hpp"
#include "registers/StaticIncludes.hpp"

DWORD WINAPI thread_func(void* hModule) {
    uintptr_t cocosBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("libcocos2d.dll"));

    MH_Initialize();

    for (const hook_t& hook : gd::m_hooks) {
        MH_CreateHook(
            reinterpret_cast<LPVOID>((std::get<0>(hook) ? cocosBase : gd::base) + std::get<1>(hook)), 
            std::get<2>(hook), 
            std::get<3>(hook)
        );
    }

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    #ifdef SHOW_CONSOLE
        if (AllocConsole()) {
            freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
            freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
        }
    #endif
    
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0x100, thread_func, handle, 0, 0);
    }

    return TRUE;
}