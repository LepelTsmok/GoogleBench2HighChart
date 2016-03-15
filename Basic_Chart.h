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
#ifndef BASIC_CHART_H
#define BASIC_CHART_H

#include "HTML_Files.h"
#include "HTMLOutput.h"
#include <QtCore/qtextstream.h>
#include <QtCore/qstring.h>

using namespace std;

//! Der Basis-Chart
double itemsPerNanoSecond(double itemsPerSec) {
  double dItemsPerSec = itemsPerSec / 1000000000.0;

  return (1.0 / dItemsPerSec);
}

void writeHtmlBegin(QTextStream &stream, const QString &,
                    const vector<Benchmark_Values> &, const InputCommands &) {
  stream << defaultHTML_Begin;
}

void writeHtmlMiddle(QTextStream &stream, const QString &title,
                     const vector<Benchmark_Values> &values,
                     const InputCommands &commands) {
  int n, m;

  stream << "       <style type = \"text/css\">\n"
            "           #benchmark{\n"
            "                width: 100%;\n"
            "                height:400px;\n"
            "                     }\n"
            "       </style>\n";
  //          "       <script type = \"text/javascript\" src =
  //          \"./jquery-2.2.1.min.js\"></script>\n"
  //          "       <script type = \"text/javascript\" src =
  //          \"./highcharts.js\"></script>\n"
  handleInlineJS(stream, commands.useScrolling, commands.useInlineJS);

  stream << "       <script>\n"
            "            $(function () {\n"
            "                $('#benchmark').highcharts({\n"
            "                    chart: {\n"
            "                        type: 'line',\n"
            "                        zoomType: 'xy'\n"
            "                    },\n"
            "                    title: {\n"
            "                        text: '"
         << title
         << "'\n"
            "                    },\n"
            "                    legend: {\n"
            "                         align: 'right',\n"
            "                         verticalAlign: 'top',\n"
            "                         layout: 'vertical'\n"
            "                    },\n"
            "                    xAxis: {\n"
            "                        title: {\n"
            "                              text: 'Amount of calculated values',\n"
            "                              enabled: true\n"
            "                        },\n"
            "                        allowDecimals: false";

  if (commands.maxValueX < 0)
    stream << "\n";

  else
    stream << ",\n                        max: " << commands.maxValueX << "\n";

  stream << "                    },\n"
            "                    yAxis: {\n"
            "                        title: {\n"
            "                            text: 'time per item (ns)'\n"
            "                        },\n  "
            "                        allowDecimals: false";

  if (commands.maxValueY < 0)
    stream << "\n";

  else
    stream << ",\n                        max: " << commands.maxValueY << "\n";

  stream << "                    },\n"
            "                    tooltip: {\n"
            "                        headerFormat: "
            "'<b><center>{series.name}</center></b><br/>',\n"
            "                        pointFormat: 'Amount of calculated values: "
            "<b>{point.x}</b><br/>Time per item: <b>{point.y}ns</b>',\n"
            "                        borderWidth: 5\n"
            "                    },\n";

  if (commands.useScrolling) {
    stream << "                    scrollbar: {\n"
              "                        enabled: true\n"
              "                    },\n";
  }

  if (commands.useNavigator) {
    stream << "                    navigator: {\n"
              "                        enabled: true"
              "                    },\n";
  }

  stream << "                    plotOptions: {\n"
            "                        line: {\n"
            "                          marker: {\n"
            "                              enabled: true,\n"
            "                              radius: 3\n"
            "                          },\n"
            "                          lineWidth: 1\n"
            "                        }\n"
            "                    },\n";

  stream << "                    series: [{\n";

  n = 0;
  while (n < (signed int)values.size()) {
    stream << "name: '" << values[n].name << "',\ndata: [";
    m = 0;
    while (m < (signed int)values[n].iterations.size()) {
      stream << "[" << values[n].tails[m] << ","
             << itemsPerNanoSecond(values[n].itemsPerSec[m]) << "]";

      m++;
      if (m < (signed int)values[n].iterations.size())
        stream << ",";
    }

    switch (values[n].lineType) {
    case LongDash:
      stream << "],\ndashStyle: 'LongDash'\n}";
      break;

    case Dot:
      stream << "],\ndashStyle: 'LongDashDotDot'\n}";
      break;

    default:
      stream << "]\n}";
    }

    n++;
    if (n < (signed int)values.size())
      stream << ",{";

    else
      stream << "]";
  }

  stream << "                });\n"
            "            });\n"
            "       </script>\n";
}

void writeHtmlEnd(QTextStream &stream, const QString &, const vector<Benchmark_Values> &,
                  const InputCommands &) {
  stream << defaultHTML_End;
}

htmlFunctions basicChartfunctions = {writeHtmlBegin, writeHtmlMiddle, writeHtmlEnd};
int basicChartSize = 3;
#endif // BASIC_CHART_H
