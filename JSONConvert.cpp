#include "JSONConvert.h"
#include "HTMLOutput.h"
#include "Basic_Chart.h"
#include <QtCore/qfile.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <iostream>

using namespace std;

void fillBenchmark(vector<Benchmark_Values> &benchmarkVec, const QJsonObject &jsonObject, bool useLabel)
{
 QString jsonAccess = (useLabel) ? "label" : "name";
 const QJsonArray  array = jsonObject["benchmarks"].toArray();
 QString   benchmarkName;
 QString   benchmarkTail;
 Line_Type lineType;
 int index;
 int n, m;

    for(n = 0; n < array.size(); n++)
    {
        //!Den aktuellen Namen holen und bearbeiten
        benchmarkName = array[n].toObject()[jsonAccess].toString();
        index = benchmarkName.indexOf('/');

        if(index > -1)
        {
            benchmarkTail = benchmarkName.right((benchmarkName.length() - index - 1));
            benchmarkName.remove(index, benchmarkName.size());
        }

        //!Prüfen ob der Name bold sein will
        switch(benchmarkName[0].toLatin1())
        {
            case '-':
                benchmarkName.remove(0, 1);
                lineType = LongDash;
            break;

            case '.':
                benchmarkName.remove(0, 1);
                lineType = Dot;
            break;

            default:
                lineType = Normal;
        }

        for(m = 0; m < (signed int)benchmarkVec.size(); m++)
            if(benchmarkVec[m].name == benchmarkName)
            {
                benchmarkVec[m].tails.push_back(benchmarkTail);
                benchmarkVec[m].iterations.push_back(array[n].toObject()["iterations"].toDouble());
                benchmarkVec[m].realTime.push_back(array[n].toObject()["real_time"].toDouble());
                benchmarkVec[m].cpuTime.push_back(array[n].toObject()["cpu_time"].toDouble());
                benchmarkVec[m].itemsPerSec.push_back(array[n].toObject()["items_per_second"].toDouble());
                break;
            }

        if(m == (signed int)benchmarkVec.size())
        {
            benchmarkVec.push_back(Benchmark_Values());

            benchmarkVec[m].name = benchmarkName;
            benchmarkVec[m].lineType = lineType;

            benchmarkVec[m].tails.push_back(benchmarkTail);
            benchmarkVec[m].iterations.push_back(array[n].toObject()["iterations"].toDouble());
            benchmarkVec[m].realTime.push_back(array[n].toObject()["real_time"].toDouble());
            benchmarkVec[m].cpuTime.push_back(array[n].toObject()["cpu_time"].toDouble());
            benchmarkVec[m].itemsPerSec.push_back(array[n].toObject()["items_per_second"].toDouble());
        }
    }
}

//!Verarbeitet die übergebenen Befehle
void processJSON(const InputCommands &inputCommands)
{
 //!Die konvertierte Datei
 QJsonDocument jsonDocument;
 //!Speichert sich Fehler
 QJsonParseError jsonError;
 //!Die Datei, die die JSON enthält
 QFile   jsonFile(inputCommands.inputName);
 //!Buffert die ganze Datei
 QString jsonBuffer;
 //!Speichert alle gelesenen Werte
 vector<Benchmark_Values> benchmark;

    if(!jsonFile.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        cout << "Failed to open input\n";
        return;
    }

    //!Alle Elemente einlesen
    jsonBuffer = jsonFile.readAll();
    jsonFile.close();

    jsonDocument = QJsonDocument::fromJson(jsonBuffer.toUtf8(), &jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        cout << "JSON Error: " << jsonError.errorString().toStdString() << "\n";
        return;
    }

    fillBenchmark(benchmark, jsonDocument.object(), inputCommands.useLabel);

    switch(inputCommands.htmlOutputMode)
    {
        case OutputMode::HTML_Basic:
            writeHTML(basicChartfunctions, basicChartSize, inputCommands.outputName, inputCommands.chartTitle, benchmark, inputCommands);
        break;
    }
}
