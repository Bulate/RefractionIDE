#ifndef REFRACTIONIDE_H
#define REFRACTIONIDE_H

#include <QApplication>

class LogManager;
/**
 * @brief The RefractionIDE class hosts the main processes of the aplication.
 *
 */
class RefractionIDE : public QApplication
{
    //Q_OBJECT
    //Q_DISABLE_COPY(RefractionIDE)
 public:
    /// Sets the program information and the icon for windows or mac
    RefractionIDE(int& argc , char* argv[]);
    virtual ~RefractionIDE();
 protected:

    /// Saves log events to a file and upload them to a network server
    LogManager* logManager;

};

#endif // REFRACTIONIDE_H
