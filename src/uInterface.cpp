#include "uInterface.h"
#include "uVisitor.h"

uInterface::uInterface(std::string const& name) : uInheritable(name)
{
    mHasParent = false;
    mIsInterface = true;
    mIsAbstract = false;
}

uInterface::uInterface(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references) : uInheritable(access, name, attributes, methods, references, false)
{
    mHasParent = false;
    mIsInterface = true;
    mIsAbstract = false;
}

uInterface::uInterface(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, double x, double y) : uInheritable(access, name, attributes, methods, references, false)
{
    mHasParent = false;
    mIsInterface = true;
    mIsAbstract = false;
    locX = x;
    locY = y;
}


void uInterface::accept(uVisitor *visitor)
{
    visitor->visit(this);
}
void uInterface::acceptSave(uVisitor *visitor)
{
    visitor->visitSave(this, locX, locY);
}
