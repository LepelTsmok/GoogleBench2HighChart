#include "JSONConvert.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
 QApplication   app(argc, argv);
 //!Verarbeitet die Eingaben
 QCommandLineParser cmdParser;
 //!Die Eingaben vom User
 InputCommands  commands;

    //!Eingaben verarbeiten
    createInputCommands(cmdParser);
    cmdParser.process(app);
    fillInputCommands(cmdParser, commands);
    if(checkInputCommands(commands))
    {
        processJSON(commands);
    }

    else
    {
        cout << "No input!\n";
        return 1;
    }

 return 0;
}


