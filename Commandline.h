/*
Copyright © 2016 Björn Gaier
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <QtCore/qcommandlineparser.h>
#include <QtWidgets/qapplication.h>

//! Die Typen, wie der Output aussehen könnte
enum struct OutputMode : unsigned char {
  HTML_Basic //! Die Basis-Variante
};
typedef std::pair<QString, OutputMode> outModePair;

//! Merkt sich welche Commands über die Konsole gesetzt wurden
struct InputCommands {
  OutputMode htmlOutputMode; //!< Die Art des Ouputs
  QString outputName;        //!< Der Outputname
  QString inputName;         //!< Der Eingabename
  QString chartTitle;        //!< Der Title für den Chart
  int maxValueX;             //!< Setzt die Größe der Tabelle in X-Richtung
  int maxValueY;             //!< Setzt die Größe der Tabelle in Y-Richtung
  bool useLabel; //!< Gibt an, ob als Bezeichnung die Labels verwendet werden sollen, oder
                 //!nicht
  bool useScrolling; //!< Verwendet Scrollbars
  bool useInlineJS;  //!< Gibt an, ob die JavaScript-Datein in die Datei kopiert werden
                     //!sollen
  bool useNavigator; //!< Gibt sn, ob wir einen Navigator nutzen wollen

  InputCommands()
      : htmlOutputMode(OutputMode::HTML_Basic), outputName("./output.html"),
        inputName(""), chartTitle("Benchmarks"), maxValueX(-1), maxValueY(-1),
        useLabel(false), useScrolling(false), useInlineJS(false), useNavigator(false) {}
};

//! Bereitet die Eingabeparameter vor
extern void createInputCommands(QCommandLineParser &cmdParser);
//! Verarbeitet die Eingaben
extern void fillInputCommands(const QCommandLineParser &cmdParser,
                              InputCommands &inputCommands);
//! Prüft die Eingaben auf Korrektheit
extern bool checkInputCommands(const InputCommands &inputCommands);
#endif // COMMANDLINE_H
