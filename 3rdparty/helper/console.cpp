#include <zpl.h>
#include <console.h>

#if defined(ZPL_SYSTEM_WINDOWS)
#   include <windows.h>
#   include <cstdlib>
#endif

void open_console()
{
#if defined(ZPL_SYSTEM_WINDOWS)
    // Attempt to attach to parent process's console
    if (!AttachConsole(ATTACH_PARENT_PROCESS))
        return;
    
    FILE* fp = 0;

    // Redirect STDIN if the console has an input handle
    if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONIN$", "r", stdin) == 0)
            setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT if the console has an output handle
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stdout) == 0)
            setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR if the console has an error handle
    if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stderr) == 0)
            setvbuf(stderr, NULL, _IONBF, 0);

    // Make C++ standard streams point to console as well.
    std::ios::sync_with_stdio(true);

    // Clear the error state for each of the C++ standard streams.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
#endif // defined(ZPL_SYSTEM_WINDOWS)
}

void close_console()
{
#if defined(OS_WIN)
    FILE* fp = 0;

    // Redirect STDIN to NUL
    if (freopen_s(&fp, "NUL:", "r", stdin) == 0)
        setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT to NUL
    if (freopen_s(&fp, "NUL:", "w", stdout) == 0)
        setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR to NUL
    if (freopen_s(&fp, "NUL:", "w", stderr) == 0)
        setvbuf(stderr, NULL, _IONBF, 0);

    // Detach from console
    FreeConsole();
#endif // defined(ZPL_SYSTEM_WINDOWS)
}