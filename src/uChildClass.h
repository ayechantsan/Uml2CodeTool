#ifndef UCHILDCLASS_H
#define UCHILDCLASS_H

#include "uInheritable.h"

/**
 * @brief The uChildClass class it is a uInheritable which represents classes that inherits from another
 */

class uChildClass : public uInheritable
{
public:
    uChildClass(std::string const& name);
    uChildClass(std::string const& name, const std::string &base);
    uChildClass(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, std::string const& base, bool isAbstract);
    uChildClass(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, std::string const& base, bool isAbstract, double x, double y);

    virtual ~uChildClass();
    virtual void accept(uVisitor * visitor);
    virtual void acceptSave(uVisitor * visitor);
};

#endif // UCHILDCLASS_H
