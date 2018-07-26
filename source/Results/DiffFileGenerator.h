#ifndef DIFFFILEGENERATOR_H
#define DIFFFILEGENERATOR_H

#include <QFileInfoList>
#include <QDir>

class DiffFileGenerator : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiffFileGenerator)
protected:
    const QFileInfoList &outputInfoList;
    const QFileInfoList &programOutputInfoList;
    const QDir workingDirectory;
    int index;
    QString outputFileHtmlPath;

public:
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
