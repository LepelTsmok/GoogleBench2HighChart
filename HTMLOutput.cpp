#include "HTMLOutput.h"
#include <QtCore/qfile.h>
#include <QtCore/QTextStream>

using namespace std;

//!Speichert das HTML-Dokument
bool writeHTML(htmlFunctions function, int functionSize, const QString &path, const QString &title, const vector<Benchmark_Values> &values, const InputCommands &commands)
{
 //!Öffnet die Datei
 QFile       file(path);
 //!Schreibt die Datei
 QTextStream writer;
 int n;

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    writer.setDevice(&file);

        for(n = 0; n < functionSize; n++)
            function[n](writer, title, values, commands);

    file.close();

 return true;
}
