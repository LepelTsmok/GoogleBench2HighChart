#include "Commandline.h"
#include <utility>

using namespace std;

//!Bereitet die Eingabeparameter vor
void createInputCommands(QCommandLineParser &cmdParser)
{
 //!Befehle
 QCommandLineOption inputPath("i", "Path for input", "...");
 QCommandLineOption outputPath("o", "Path for output", "...");
 QCommandLineOption generateType("g", "Generating type", "[htmlbasic]");
 QCommandLineOption chartTitle("t", "Title for the chart", "...");
 QCommandLineOption minValueX("x", "Maximumvalue for the chart on the X-Axis", "...");
 QCommandLineOption minValueY("y", "Maximumvalue for the chart on the Y-Axis", "...");

    cmdParser.setApplicationDescription("Description");
    cmdParser.addHelpOption();
    cmdParser.addPositionalArgument("useLabel", "Use the label form json as label for the graph");
    cmdParser.addPositionalArgument("useScrolling", "Uses Scrolling with Highstock");
    cmdParser.addPositionalArgument("useInlineJS", "Uses JQuery and HighChart without seperate File");
    cmdParser.addPositionalArgument("useNavigator", "Adds a navigator to the chart");

    //!Optionen hinzufügen
    cmdParser.addOption(inputPath);
    cmdParser.addOption(outputPath);
    cmdParser.addOption(generateType);
    cmdParser.addOption(chartTitle);
    cmdParser.addOption(minValueX);
    cmdParser.addOption(minValueY);
}

//!Verarbeitet die Eingaben
void fillInputCommands(const QCommandLineParser &cmdParser, InputCommands &inputCommands)
{//outputModeMap({outModePair(QString("htmlwithjs"), OutputMode::HTMLwithJS), outModePair(QString("htmlandjs"), OutputMode::HTMLandJS), outModePair(QString("html"), OutputMode::HTML)});
 const QMap<QString, OutputMode> outputModeMap({outModePair(QString("htmlbasic"), OutputMode::HTML_Basic)});
 const QStringList positional = cmdParser.positionalArguments();
 QString fileName;
 bool convertedOK;

    //!Die jeweiligen Werte und Pfade speichern
    inputCommands.htmlOutputMode = outputModeMap.value(cmdParser.value("g"), OutputMode::HTML_Basic);

    inputCommands.inputName      = cmdParser.value("i");

    if(cmdParser.value("o") != QString(""))
        inputCommands.outputName = cmdParser.value("o");

    else
    {
        if(inputCommands.inputName != QString(""))
        {
            fileName = inputCommands.inputName;
            inputCommands.outputName = fileName.replace(QString(".json"), QString(".hmtl"));
        }

        else
            inputCommands.outputName = "Result.html";
    }

    if(cmdParser.value("t") != QString(""))
        inputCommands.chartTitle = cmdParser.value("t");

    inputCommands.maxValueX = cmdParser.value("x").toInt(&convertedOK);
    if(!convertedOK)
        inputCommands.maxValueX = -1;

    inputCommands.maxValueY = cmdParser.value("y").toInt(&convertedOK);
    if(!convertedOK)
        inputCommands.maxValueY = -1;

    inputCommands.useLabel       = positional.contains("useLabel");
    inputCommands.useInlineJS    = positional.contains("useInlineJS");
    inputCommands.useScrolling   = positional.contains("useScrolling");
    inputCommands.useNavigator   = positional.contains("useNavigator");
}

//!Prüft die Eingaben auf Korrektheit
bool checkInputCommands(const InputCommands &inputCommands)
{
 return (inputCommands.inputName != QString(""));
}
