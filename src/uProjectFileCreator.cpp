#include "uProjectFileCreator.h"
#include "uDebugPrinter.h"
#include "uProjectFileQT.h"

#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;


uProjectFileCreator::uProjectFileCreator()
{
    mDevenv = new uProjectFileQT();
}

void uProjectFileCreator::createFile(uClassDiagram const * const diagram, const string &name, string const& path )
{
    if(mDevenv != NULL){
        string content = mDevenv->createFile(diagram);
        if(name == "")
            generateFile(content, "uCodeProjectFile", path);
        else
            generateFile(content, name, path);
    }
}

void uProjectFileCreator::setDevEnv(uProjectFile *devenv)
{
    mDevenv = devenv;
}

std::string uProjectFileCreator::getDevEnvString() const
{
    if (mDevenv == NULL) {
        uDebugPrinter::printText("NULL OBJECT");
        return "";
    }
    return mDevenv->getName();
}

bool uProjectFileCreator::generateFile(const string &content, const string &name, string const& path)
{
    string thisPath = path.substr(7, path.length());
#ifdef Q_OS_WIN
    thisPath = path.substr(8, path.length());
#endif
    ofstream myfile;
    myfile.open(thisPath+"/"+name.c_str()+".pro");
    if (!myfile.is_open())
        return false;

    myfile << content;
    myfile.close();
    return true;
}

