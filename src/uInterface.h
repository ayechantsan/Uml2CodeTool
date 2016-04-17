#ifndef UINTERFACE_H
#define UINTERFACE_H

#include "uInheritable.h"

class uInterface : public uInheritable
{
public:
    uInterface(std::string const& name);
    uInterface(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references);
    uInterface(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, double x, double y);

    virtual void accept(uVisitor * visitor);
    virtual void acceptSave(uVisitor * visitor, double x, double y);

private:

};

#endif // UINTERFACE_H
