#ifndef HTMLOUTPUT_H
#define HTMLOUTPUT_H
#include <QtCore/qstring.h>
#include "JSONConvert.h"

typedef void (*htmlFunctions[])(QTextStream&, const QString&, const std::vector<Benchmark_Values>&, const InputCommands&);

//!Speichert das HTML-Dokument
extern bool writeHTML(htmlFunctions, int, const QString &path, const QString&, const std::vector<Benchmark_Values>&, const InputCommands&);
#endif
