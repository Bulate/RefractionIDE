#ifndef DIFFFILEGENERATOR_H
#define DIFFFILEGENERATOR_H

#include <QFileInfoList>
#include <QDir>

class DiffFileGenerator : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiffFileGenerator)
protected:
    /// Saves the information of the expected output files
    const QFileInfoList &outputInfoList;
    /// Saves the information of the program output files
    const QFileInfoList &programOutputInfoList;
    /// The directory where the program files can be located
    const QDir workingDirectory;
    /// The test case number to be analyzed
    int index;
    /// The path for the html file to be used as output
    QString outputFileHtmlPath;

public:
    /// Constructor. Recieves all of the files that
    DiffFileGenerator(QObject *parent, const QFileInfoList &outputInfoList
                      , const QFileInfoList &programOutputInfoList
                      , const QDir workingDirectory
                      , int index);

    void generateDiffFile( );
signals:
    void htmlFileGenerated(int index, QString outputFileHtmlPath);
public slots:
    void callDiff2Html();
    void diff2HtmlFinished();
};

#endif // DIFFFILEGENERATOR_H
