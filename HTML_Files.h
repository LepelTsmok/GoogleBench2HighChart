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
#ifndef HTML_FILES_H
#define HTML_FILES_H
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

const char *defaultHTML_Begin = "<!DOCTYPE html>\n"
                                "<html>\n"
                                "   <head>\n"
                                "       <meta charset = \"UTF-8\"/>\n";

const char *defaultHTML_End = "\t</head>\n"
                              "\t<body>\n"
                              "\t\t<div id = 'benchmark'></div>"
                              "\t</body>\n"
                              "</html>";

void handleInlineJS(QTextStream &stream, bool useHighChart, bool useInlineJS) {
  const char *pathChart = (useHighChart) ? "./highstock.js" : "./highcharts.js";
  const char *pathJQuery = "./jquery-2.2.1.min.js";

  QFile fileHighChart(pathChart);
  QFile fileJQuery(pathJQuery);
  QTextStream highChartReader;
  QTextStream jQueryReader;
  QString data;

  if (useInlineJS) {
    if (fileHighChart.open(QIODevice::ReadOnly | QIODevice::Text) &&
        fileJQuery.open(QIODevice::ReadOnly | QIODevice::Text)) {
      highChartReader.setDevice(&fileHighChart);
      jQueryReader.setDevice(&fileJQuery);

      stream << "       <script type = \"text/javascript\">\n";
      do {
        stream << data;
        data = jQueryReader.readLine();
      } while (!data.isNull());

      stream << "\n       </script>\n       <script type = \"text/javascript\">\n";
      do {
        stream << data;
        data = highChartReader.readLine();
      } while (!data.isNull());

      stream << "\n       </script>\n";

      fileHighChart.close();
      fileJQuery.close();

      return;
    }
  }

  //! Wird geschrieben, falls wir es wünschen oder die Datein nicht existieren
  stream << "       <script type = \"text/javascript\" src = \"" << pathJQuery
         << "\"></script>\n"
            "       <script type = \"text/javascript\" src = \""
         << pathChart << "\"></script>\n";
}
#endif // HTML_FILES_H
