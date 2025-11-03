#include "ConsoleInitializer.h"

#ifdef _WIN32

namespace Console
{
    void enableVirtualTerminalProcessing(const HANDLE hConsole)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hConsole, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(hConsole, dwMode))
            {
                LOG_WARNING("Could not set console mode (SetConsoleMode) for ANSI enabling.");
            }
        }
        else
        {
            LOG_WARNING("Could not get console mode (GetConsoleMode) for ANSI enabling.");
        }
    }

    bool setConsoleSize(const HANDLE hConsole)
    {
        if (constexpr COORD bufferSize = {static_cast<short>(WIDTH), static_cast<short>(HEIGHT)}; !SetConsoleScreenBufferSize(hConsole, bufferSize))
        {
            LOG_ERROR("Error: Unable to set console buffer size.");
            return false;
        }

        constexpr SMALL_RECT rect = {0, 0, static_cast<short>(WIDTH - 1), static_cast<short>(HEIGHT - 1)};
        if (!SetConsoleWindowInfo(hConsole, TRUE, &rect))
        {
            std::cerr << RED_NORMAL_TEXT << "Error: Unable to set console window size\n" << RESET_TEXT;
            LOG_ERROR("Error: Unable to set console window size");
            return false;
        }

        return true;
    }

    void lockConsoleSize()
    {
        const HWND consoleWindow = GetConsoleWindow();
        if (consoleWindow == nullptr)
        {
            LOG_WARNING("Warning: Unable to get console window handle for size lock.");
            return;
        }

        if (const long style = GetWindowLong(consoleWindow, GWL_STYLE); !SetWindowLong(consoleWindow, GWL_STYLE, style & ~WS_THICKFRAME))
        {
            LOG_WARNING("Could not remove WS_THICKFRAME to lock size.");
        }

        if (!SetWindowPos(consoleWindow, nullptr, 0, 0, 0, 0,
                          SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED))
        {
            LOG_WARNING("Could not call SetWindowPos to apply locked size.");
        }
    }

    void disableMouseInput(const HANDLE hConsole)
    {
        DWORD prevMode;
        if (GetConsoleMode(hConsole, &prevMode))
        {
            if (const DWORD newMode = prevMode & ~ENABLE_MOUSE_INPUT; !SetConsoleMode(hConsole, newMode))
            {
                LOG_ERROR("Error: Unable to disable mouse input.");
            }
        }
        else
        {
            LOG_ERROR("Error: Unable to get console mode for mouse input check.");
        }
    }

    bool initialize()
    {
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE)
        {
            std::cerr << RED_NORMAL_TEXT << "Error: Unable to get console handle\n" << RESET_TEXT;
            LOG_ERROR("Error: Unable to get console handle");
            return false;
        }

        enableVirtualTerminalProcessing(hConsole);

        if (!setConsoleSize(hConsole))
        {
            return false;
        }

        lockConsoleSize();
        disableMouseInput(hConsole);

        return true;
    }
}

#endif // _WIN32
