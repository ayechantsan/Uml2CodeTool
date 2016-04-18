#ifndef UBASECLASS_H
#define UBASECLASS_H

#include "uInheritable.h"

/**
 * @brief The uBaseClass class is an uInheritable which represents classes with no parent class
 */

class uBaseClass : public uInheritable
{
public:
    uBaseClass(std::string const& name);
    uBaseClass(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, bool isAbstract);
    uBaseClass(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, bool isAbstract, double x, double y);

    virtual ~uBaseClass();
    virtual void accept(uVisitor * visitor);
    virtual void acceptSave(uVisitor *visitor, double x, double y);
protected:

};

#endif // UBASECLASS_H
