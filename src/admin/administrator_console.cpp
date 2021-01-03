#include "administrator_console.h"

AdministratorConsole::AdministratorConsole(DataBases *data_bases)
{
    dbs = data_bases;
}

int AdministratorConsole::Run()
{
    _loadRealPassword();
    _inputPassword("Password: ");
    if(!_verifyPassword())
    {
        std::cout << "Incorrect password!\n";
        return 1;
    }

    return _mainMenu();
}

void AdministratorConsole::_loadRealPassword()
{
    std::ifstream fin("../.pass");

    if(!fin)
    {
        std::cerr << ".pass does not exist!\n";
    }
    fin >> real_password;
}

void AdministratorConsole::_uploadPassword() const
{
    std::ofstream fout("../.pass", std::ios_base::trunc);

    if(!fout)
    {
        std::cerr << ".pass does not exist!\n";
    }
    fout << real_password;
}

int AdministratorConsole::_getch()
{
    int ch;
    struct termios t_old{}, t_new{};

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

    return ch;
}

void AdministratorConsole::_inputPassword(const std::string &prompt, bool show_asterisk)
{
    if(!password.empty()) password.clear();
    std::cout << prompt;

    unsigned char ch=0;
    while((ch = _getch()) != RETURN)
    {
        if(ch == BACKSPACE)
        {
            if(password.length()!=0)
            {
                if(show_asterisk)
                    std::cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            if(show_asterisk)
                std::cout <<'*';
        }
    }
    std::cout << "\n";
}

bool AdministratorConsole::_verifyPassword() const
{
    std::string hashed_password = sha256(password);
    return hashed_password == real_password;
}

int AdministratorConsole::_mainMenu()
{
    while(true)
    {
        std::cout << "\nChoose Data Base" << "\n";
        std::cout << "1 Choose Truck Data Base" << "\n";
        std::cout << "2 Choose Driver Data Base" << "\n";
        std::cout << "3 Choose Route Data Base" << "\n";
        std::cout << "4 Change password\n";
        std::cout << "0 Exit" << "\n";

        int option = InputInt("Input: ");
        switch (option)
        {
            case 1: _truckMenu(); break;
            case 2: _driverMenu(); break;
            case 3: _routeMenu(); break;
            case 4: _changePassword(); break;
            case 0: dbs->CloseAll(); return 0;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void AdministratorConsole::_truckMenu() const
{
    while(true)
    {
        std::cout << "\nTruck Data Base" << "\n";
        std::cout << "1 Print all" << "\n";
        std::cout << "2 Edit" << "\n";
        std::cout << "3 Add" << "\n";
        std::cout << "4 Delete" << "\n";
        std::cout << "0 Exit" << "\n";

        int option = InputInt("Input: ");
        switch (option)
        {
            case 1: dbs->truck_db.PrintAll(); break;
            case 2:
            {
                int index = InputInt("Choose item by index: ", 0, dbs->truck_db.list.size-1);
                dbs->truck_db.Edit(index);
                break;
            }
            case 3: dbs->truck_db.Add(); break;
            case 4: dbs->truck_db.Delete(InputInt("Index: ")); break;
            case 0: return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void AdministratorConsole::_driverMenu() const
{
    while(true)
    {
        std::cout << "\nDriver Data Base" << "\n";
        std::cout << "1 Print all" << "\n";
        std::cout << "2 Edit" << "\n";
        std::cout << "3 Add" << "\n";
        std::cout << "4 Delete" << "\n";
        std::cout << "0 Exit" << "\n";

        int option = InputInt("Input: ");
        switch (option)
        {
            case 1: dbs->driver_db.PrintAll(); break;
            case 2:
            {
                int index = InputInt("Choose item by index: ", 0, dbs->driver_db.list.size-1);
                dbs->driver_db.Edit(index);
                break;
            }
            case 3: dbs->driver_db.Add(); break;
            case 4: dbs->driver_db.Delete(InputInt("Index: ")); break;
            case 0: return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void AdministratorConsole::_routeMenu() const
{
    while(true)
    {
        std::cout << "\nRoute Data Base" << "\n";
        std::cout << "1 Print all" << "\n";
        std::cout << "2 Edit" << "\n";
        std::cout << "3 Add" << "\n";
        std::cout << "4 Delete" << "\n";
        std::cout << "0 Exit" << "\n";

        int option = InputInt("Input: ");
        switch (option)
        {
            case 1: dbs->route_db.PrintAll(); break;
            case 2:
            {
                int index = InputInt("Choose item by index: ", 0, dbs->route_db.list.size-1);
                dbs->route_db.Edit(index);
                break;
            }
            case 3: dbs->route_db.Add(); break;
            case 4: dbs->route_db.Delete(InputInt("Index: ")); break;
            case 0: return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void AdministratorConsole::_changePassword()
{
    _inputPassword("Old password: ");
    if(!_verifyPassword())
    {
        std::cerr << "Invalid password!\n";
        return;
    }
    _inputPassword("New Password: ");
    std::string hashed_password = sha256(password);
    real_password = hashed_password;
    _uploadPassword();
    std::cout << "Password changed\n";
}
