#include "uChildClass.h"
#include "uVisitor.h"
#include "uDebugPrinter.h"


uChildClass::uChildClass(std::string const& name) : uInheritable(name)
{
    mHasParent = true;
    mBaseClass = "";
    mIsInterface = false;
}

uChildClass::uChildClass(std::string const& name, std::string const& base) : uInheritable(name)
{
    mHasParent = true;
    mBaseClass = base;
    mIsInterface = false;
}

uChildClass::uChildClass(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, std::string const& base, bool isAbstract) : uInheritable(access, name, attributes, methods, references, isAbstract)
{
    mHasParent = true;
    mBaseClass = base;
    mIsInterface = false;
}

uChildClass::uChildClass(uAccess access, const std::string & name, TParameters & attributes, TMethods & methods, TReferences & references, const std::string &base, bool isAbstract, double x, double y) : uInheritable(access, name, attributes, methods, references, isAbstract)
{

    mHasParent = true;
    mBaseClass = base;
    mIsInterface = false;
    locX = x;
    locY = y;

}
uChildClass::~uChildClass()
{
    uDebugPrinter::printText("UChildClass DTor called");
}

void uChildClass::accept(uVisitor *visitor)
{
    visitor->visit(this);
}
void uChildClass::acceptSave(uVisitor *visitor, double x, double y)
{
    visitor->visitSave(this, x, y);
}
