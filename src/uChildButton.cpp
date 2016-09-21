#include "uChildButton.h"
#include "uClassFactory.h"
#include "uDebugPrinter.h"
#include "uClassDiagram.h"


uChildButton &uChildButton::getInstance()
{
    static uChildButton mInstance;
    return mInstance;
}

void uChildButton::update(const std::string &oldName, uAccess access, const std::string &newName, TParameters &attributes, TMethods &methods, TReferences &references, std::string const& base, bool isAbstract)
{
    if (uClassDiagram::getInstance().find(QString::fromStdString(oldName)) != 0){
        uClassDiagram::getInstance().removeClass(QString::fromStdString(oldName));
        uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eChildClass ,access, newName, attributes, methods, references, base, isAbstract));
    }else
        uDebugPrinter::printText("updating ERROR: Class "+ oldName + " not found");
}

void uChildButton::create(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, const std::string &base, bool isAbstract)
{
    uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eChildClass ,access, name, attributes, methods, references, base, isAbstract));
}
//overloaded create that takes a x and y location.
void uChildButton::create(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, double x, double y,  std::string const& base, bool isAbstract)
{
      uDebugPrinter::printText("create() in child button");
    uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eChildClass ,access, name, attributes, methods, references, base, isAbstract, x, y));
}
