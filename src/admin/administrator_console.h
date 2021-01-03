#ifndef COURSEWORK_ADMINISTRATOR_CONSOLE_H
#define COURSEWORK_ADMINISTRATOR_CONSOLE_H

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "sha256/sha256.h"
#include "../common/dbs.h"
#include "../common/input.h"

struct AdministratorConsole
{
    std::string password;
    std::string real_password;

    const char BACKSPACE=127;
    const char RETURN=10;

    DataBases *dbs{};

    AdministratorConsole() = default;
    explicit AdministratorConsole(DataBases *data_bases);
    int Run();

    // Password
    void _loadRealPassword();
    void _uploadPassword() const;
    static int _getch();
    void _inputPassword(const std::string &prompt, bool show_asterisk=true);
    [[nodiscard]] bool _verifyPassword() const;

    //Menu
    [[nodiscard]] int _mainMenu();
    void _truckMenu() const;
    void _driverMenu() const;
    void _routeMenu() const;
    void _changePassword();
};

#endif //COURSEWORK_ADMINISTRATOR_CONSOLE_H
