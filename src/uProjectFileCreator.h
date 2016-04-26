#ifndef UPROJECTFILECREATOR_H
#define UPROJECTFILECREATOR_H

#include "uProjectFile.h"
#include <string>

class uProjectFileCreator
{
public:
    uProjectFileCreator();
    void createFile(uClassDiagram const * const diagram, const std::string &name, const std::string &path);
    void setDevEnv(uProjectFile * devenv);
    std::string getDevEnvString() const;

private:
    uProjectFile * mDevenv;
    bool generateFile(std::string const& content, const std::string &name, const std::string &path);
};

#endif // UPROJECTFILECREATOR_H
