#ifndef UINTERFACEBUTTON_H
#define UINTERFACEBUTTON_H

#include "uButton.h"

class uInterfaceButton: public uButton
{
public:
    static uInterfaceButton &getInstance();
    void update(const std::string &oldName, uAccess access, const std::string &newName, TParameters &attributes, TMethods &methods, TReferences &references, const std::string &base, bool isAbstract);
    void create(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, std::string const& base = "", bool isAbstract = false);
    void create(uAccess access, const std::string &name, TParameters & attributes, TMethods & methods, TReferences & references, double x, double y, const std::string &base = NULL, bool isAbstract = false);

protected:
    uInterfaceButton(){}
    uInterfaceButton(uInterfaceButton const&);
    void operator=(uInterfaceButton const&);
};

#endif // UINTERFACEBUTTON_H
