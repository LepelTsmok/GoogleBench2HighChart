#pragma once
#include "Commandline.h"
#include <vector>

enum Line_Type
{
    Normal,
    LongDash,
    Dot
};

//!Speichert Werte aus dem Becnhmark-Test
struct Benchmark_Values
{
 QString name;
 Line_Type lineType;
 std::vector<QString> tails;
 std::vector<double> iterations;
 std::vector<double> realTime;
 std::vector<double> cpuTime;
 std::vector<double> itemsPerSec;
};

//!Verarbeitet die übergebenen Befehle
extern void processJSON(const InputCommands&);
