#pragma once
#include <QtCore/qcommandlineparser.h>
#include <QtWidgets/qapplication.h>

//!Die Typen, wie der Output aussehen könnte
enum struct OutputMode : unsigned char
{
    HTML_Basic //!Die Basis-Variante
};
typedef std::pair<QString, OutputMode> outModePair;

//!Merkt sich welche Commands über die Konsole gesetzt wurden
struct InputCommands
{
    OutputMode htmlOutputMode; //!< Die Art des Ouputs
    QString    outputName;     //!< Der Outputname
    QString    inputName;      //!< Der Eingabename
    QString    chartTitle;     //!< Der Title für den Chart
    int        maxValueX;      //!< Setzt die Größe der Tabelle in X-Richtung
    int        maxValueY;      //!< Setzt die Größe der Tabelle in Y-Richtung
    bool       useLabel;       //!< Gibt an, ob als Bezeichnung die Labels verwendet werden sollen, oder nicht
    bool       useScrolling;   //!< Verwendet Scrollbars
    bool       useInlineJS;    //!< Gibt an, ob die JavaScript-Datein in die Datei kopiert werden sollen
    bool       useNavigator;   //!< Gibt sn, ob wir einen Navigator nutzen wollen

    InputCommands()
    : htmlOutputMode(OutputMode::HTML_Basic),
      outputName("./output.html"),
      inputName(""),
      chartTitle("Benchmarks"),
      maxValueX(-1),
      maxValueY(-1),
      useLabel(false),
      useScrolling(false),
      useInlineJS(false),
      useNavigator(false)
    {}
};

//!Bereitet die Eingabeparameter vor
extern void createInputCommands(QCommandLineParser &cmdParser);
//!Verarbeitet die Eingaben
extern void fillInputCommands(const QCommandLineParser &cmdParser, InputCommands &inputCommands);
//!Prüft die Eingaben auf Korrektheit
extern bool checkInputCommands(const InputCommands &inputCommands);
