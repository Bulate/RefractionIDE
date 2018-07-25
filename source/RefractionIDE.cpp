#include "RefractionIDE.h"
#include "LogManager.h"

RefractionIDE::RefractionIDE(int& argc, char* argv[])
    :QApplication(argc, argv)
{
//     Properties for the whole application
    setApplicationName("RefractionIDE");
    setOrganizationName("UCR");
    setApplicationDisplayName("RefractionIDE");
    setApplicationVersion("1.0.0");

    // Managers use the settings, create them after resetting the settings
    // Enable logging of messages to a file
    this->logManager = new LogManager(this);

}

RefractionIDE::~RefractionIDE()
{

}
