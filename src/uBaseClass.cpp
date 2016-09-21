#include "uBaseClass.h"
#include "uVisitor.h"

#include "uDebugPrinter.h"

/**
 * @brief uBaseClass::uBaseClass basic constructor that relies on the uInheritable constructor with the same param
 * @param name
 */


uBaseClass::uBaseClass(std::string const& name) : uInheritable(name)
{
    mHasParent = false;
    mIsInterface = false;
}

/**
 * @brief uBaseClass::uBaseClass basic constructor that relies on the uInheritable constructor with the same params
 * @param name
 */

uBaseClass::uBaseClass(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, bool isAbstract) : uInheritable(access, name, attributes, methods, references, isAbstract)
{
    mHasParent = false;
    mIsInterface = false;
}


uBaseClass::uBaseClass(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, bool isAbstract, double x, double y) : uInheritable(access, name, attributes, methods, references, isAbstract)
{
    mHasParent = false;
    mIsInterface = false;
    uBaseClass::locX = x;
    uBaseClass::locY = y;
}

uBaseClass::~uBaseClass()
{
    uDebugPrinter::printText("uBaseClass DTor called: " + mName);
}

void uBaseClass::accept(uVisitor *visitor)
{
    visitor->visit(this);
}
void uBaseClass::acceptSave(uVisitor *visitor)
{
    visitor->visitSave(this, locX, locY);
}


