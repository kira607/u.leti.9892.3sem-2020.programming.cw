#include "libs.h"

int main(int argc, char *argv[])
{
    DataBases dbs{};

    if (argc == 1)
    {
        AdministratorConsole ac{&dbs};
        return ac.Run();
    }
    else if (argc == 2)
    {
        RequestHandler rh{argv[1], &dbs};
        return rh.Run();
    }

    std::cerr << "Unexpected arguments count\n";
    return 255;
}