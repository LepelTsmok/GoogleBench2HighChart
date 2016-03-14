#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

const char *defaultHTML_Begin =
"<!DOCTYPE html>\n"
"<html>\n"
"   <head>\n"
"       <meta charset = \"UTF-8\"/>\n";

const char *defaultHTML_End =
    "\t</head>\n"
    "\t<body>\n"
        "\t\t<div id = 'benchmark'></div>"
    "\t</body>\n"
"</html>";

void handleInlineJS(QTextStream &stream, bool useHighChart, bool useInlineJS)
{
 const char *pathChart  = (useHighChart) ? "./highstock.js" : "./highcharts.js";
 const char *pathJQuery = "./jquery-2.2.1.min.js";

 QFile fileHighChart(pathChart);
 QFile fileJQuery(pathJQuery);
 QTextStream highChartReader;
 QTextStream jQueryReader;
 QString     data;

    if(useInlineJS)
    {
        if(fileHighChart.open(QIODevice::ReadOnly | QIODevice::Text) && fileJQuery.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            highChartReader.setDevice(&fileHighChart);
            jQueryReader.setDevice(&fileJQuery);

            stream << "       <script type = \"text/javascript\">\n";
            do
            {
                stream << data;
                data = jQueryReader.readLine();
            } while(!data.isNull());

            stream << "\n       </script>\n       <script type = \"text/javascript\">\n";
            do
            {
                stream << data;
                data = highChartReader.readLine();
            } while(!data.isNull());

            stream << "\n       </script>\n";

            fileHighChart.close();
            fileJQuery.close();

         return;
        }
    }

    //!Wird geschrieben, falls wir es wünschen oder die Datein nicht existieren
    stream << "       <script type = \"text/javascript\" src = \"" << pathJQuery << "\"></script>\n"
              "       <script type = \"text/javascript\" src = \"" << pathChart  << "\"></script>\n";

}
