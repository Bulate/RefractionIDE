#include "DiffFileGenerator.h"
#include <QString>
#include <QFile>
#include <QProcess>
#include <QDir>

DiffFileGenerator::DiffFileGenerator( QObject* parent
                                     , const QFileInfoList &outputInfoList
                                     , const QFileInfoList &programOutputInfoList
                                     , const QDir workingDirectory
                                     , int index )
    : QObject(parent)
    , outputInfoList(outputInfoList)
    , programOutputInfoList(programOutputInfoList)
    , workingDirectory(workingDirectory)
    , index(index)
{

}
void DiffFileGenerator::generateDiffFile( )
{
     QString diffCall = "diff";
     QStringList arguments;
     QProcess* diffProcess = new QProcess(this);
     diffProcess->setProgram("diff");

     QString outputFileDiffPath;

     outputFileDiffPath.sprintf("%s%c%s%03d%s", workingDirectory.absolutePath().toStdString().c_str()
                                , QDir::separator().toLatin1() , "p_output" , index+1 , ".diff");

     diffProcess->setReadChannelMode(QProcess::SeparateChannels);
     diffProcess->setStandardOutputFile( outputFileDiffPath );
     arguments <<  "-w" <<  "-U 1000" << outputInfoList.at(index).absoluteFilePath()
               << programOutputInfoList.at(index).absoluteFilePath();
     diffProcess->setArguments(arguments);
     //connect(diffProcess, &QProcess::finished, this, &ResultsDockWidget::callDiff2Html);
     connect(diffProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(callDiff2Html()));
     diffProcess->start(diffCall, arguments);

}

void DiffFileGenerator::callDiff2Html()
{
    //std::cerr << "ENTRE" << this->workingDirectoryPath.toStdString();
    QString outputFileDiffPathT;

    outputFileDiffPathT.sprintf("%s%c%s%03d%s", this->workingDirectory.absolutePath().toStdString().c_str()
                               , QDir::separator().toLatin1() , "p_output" , index+1 , ".diff");

    this->outputFileHtmlPath.sprintf("%s%c%s%03d%s", this->workingDirectory.absolutePath().toStdString().c_str()
                               , QDir::separator().toLatin1() , "p_output" , index+1 , ".html");

    QString diff2HtmlCall = "diff2html";
    QStringList arguments;
    QProcess* diff2HtmlProcess = new QProcess(this);


    diff2HtmlProcess->setReadChannelMode(QProcess::SeparateChannels);

    arguments << "--su" << "hidden" << "-i" <<  "file" << "-F" << outputFileHtmlPath <<"--" << outputFileDiffPathT;
    connect(diff2HtmlProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(diff2HtmlFinished()) );
    diff2HtmlProcess->start(diff2HtmlCall, arguments);
}

void DiffFileGenerator::diff2HtmlFinished()
{
    emit htmlFileGenerated(index, outputFileHtmlPath);
}
