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
    virtual ~uBaseClass();
    virtual void accept(uVisitor * visitor);

protected:

};

#endif // UBASECLASS_H
