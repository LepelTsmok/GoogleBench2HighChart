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
#include "Commandline.h"
#include <utility>

using namespace std;

//! Bereitet die Eingabeparameter vor
void createInputCommands(QCommandLineParser &cmdParser) {
  //! Befehle
  QCommandLineOption inputPath("i", "Path for input", "...");
  QCommandLineOption outputPath("o", "Path for output", "...");
  QCommandLineOption generateType("g", "Generating type", "[htmlbasic]");
  QCommandLineOption chartTitle("t", "Title for the chart", "...");
  QCommandLineOption minValueX("x", "Maximumvalue for the chart on the X-Axis", "...");
  QCommandLineOption minValueY("y", "Maximumvalue for the chart on the Y-Axis", "...");

  cmdParser.setApplicationDescription("Description");
  cmdParser.addHelpOption();
  cmdParser.addPositionalArgument("useLabel",
                                  "Use the label form json as label for the graph");
  cmdParser.addPositionalArgument("useScrolling", "Uses Scrolling with Highstock");
  cmdParser.addPositionalArgument("useInlineJS",
                                  "Uses JQuery and HighChart without seperate File");
  cmdParser.addPositionalArgument("useNavigator", "Adds a navigator to the chart");

  //! Optionen hinzufügen
  cmdParser.addOption(inputPath);
  cmdParser.addOption(outputPath);
  cmdParser.addOption(generateType);
  cmdParser.addOption(chartTitle);
  cmdParser.addOption(minValueX);
  cmdParser.addOption(minValueY);
}

//! Verarbeitet die Eingaben
void fillInputCommands(
    const QCommandLineParser &cmdParser,
    InputCommands &inputCommands) { // outputModeMap({outModePair(QString("htmlwithjs"),
                                    // OutputMode::HTMLwithJS),
                                    // outModePair(QString("htmlandjs"),
                                    // OutputMode::HTMLandJS),
                                    // outModePair(QString("html"), OutputMode::HTML)});
  const QMap<QString, OutputMode> outputModeMap(
      {outModePair(QString("htmlbasic"), OutputMode::HTML_Basic)});
  const QStringList positional = cmdParser.positionalArguments();
  QString fileName;
  bool convertedOK;

  //! Die jeweiligen Werte und Pfade speichern
  inputCommands.htmlOutputMode =
      outputModeMap.value(cmdParser.value("g"), OutputMode::HTML_Basic);

  inputCommands.inputName = cmdParser.value("i");

  if (cmdParser.value("o") != QString(""))
    inputCommands.outputName = cmdParser.value("o");

  else {
    if (inputCommands.inputName != QString("")) {
      fileName = inputCommands.inputName;
      inputCommands.outputName = fileName.replace(QString(".json"), QString(".hmtl"));
    }

    else
      inputCommands.outputName = "Result.html";
  }

  if (cmdParser.value("t") != QString(""))
    inputCommands.chartTitle = cmdParser.value("t");

  inputCommands.maxValueX = cmdParser.value("x").toInt(&convertedOK);
  if (!convertedOK)
    inputCommands.maxValueX = -1;

  inputCommands.maxValueY = cmdParser.value("y").toInt(&convertedOK);
  if (!convertedOK)
    inputCommands.maxValueY = -1;

  inputCommands.useLabel = positional.contains("useLabel");
  inputCommands.useInlineJS = positional.contains("useInlineJS");
  inputCommands.useScrolling = positional.contains("useScrolling");
  inputCommands.useNavigator = positional.contains("useNavigator");
}

//! Prüft die Eingaben auf Korrektheit
bool checkInputCommands(const InputCommands &inputCommands) {
  return (inputCommands.inputName != QString(""));
}
