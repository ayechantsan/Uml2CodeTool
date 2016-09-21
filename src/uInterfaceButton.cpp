#include "uInterfaceButton.h"
#include "uClassFactory.h"
#include "uDebugPrinter.h"
#include "uClassDiagram.h"

uInterfaceButton &uInterfaceButton::getInstance()
{
    static uInterfaceButton mInstance;
    return mInstance;
}

void uInterfaceButton::update(const std::string &oldName, uAccess access, const std::string &newName, TParameters &attributes, TMethods &methods, TReferences &references, std::string const& base, bool isAbstract)
{
    uDebugPrinter::printText("updating uInterface");
    if (uClassDiagram::getInstance().find(QString::fromStdString(oldName)) != 0){
        uClassDiagram::getInstance().removeClass(QString::fromStdString(oldName));
        uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eInterface ,access, newName, attributes, methods, references, base, isAbstract));
    }else
        uDebugPrinter::printText("updating ERROR: Class "+ oldName + " not found");
}


//Constructor should be changed when the boxes are implemented with the GUI
void uInterfaceButton::create(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, const std::string &base, bool isAbstract)
{
    uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eInterface,access, name, attributes, methods, references, base, isAbstract));
}
//overloaded create that takes a  x and y location
void uInterfaceButton::create(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, double x, double y,std::string const& base, bool isAbstract)
{
    uClassDiagram::getInstance().addClass(uClassFactory::getInstance().createClass(uClassType::eInterface,access, name, attributes, methods, references, base, isAbstract, x, y));
}
