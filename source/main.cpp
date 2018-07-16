#include "MainWindow.h"
#include "RefractionIDE.h"

int main(int argc, char *argv[])
{
    RefractionIDE app (argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
