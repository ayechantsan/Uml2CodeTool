#ifndef UCLASSBUTTON_H
#define UCLASSBUTTON_H

#include "uButton.h"

/**
 * @brief The uClassButton class manages the creation and updating of every class with no parents (base class)
 */

class uClassButton : public uButton
{
public:
    static uClassButton &getInstance();
    void update(const std::string &oldName, uAccess access, const std::string &newName, TParameters &attributes, TMethods &methods, TReferences &references, std::string const& base, bool isAbstract);
    void create(uAccess access, std::string const& name, TParameters & attributes, TMethods & methods, TReferences & references, std::string const& base = "", bool isAbstract = false);
    void create(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, double x, double y, const std::string &base = NULL, bool isAbstract = false);
protected:
    uClassButton(){}
    uClassButton(uClassButton const&);
    void operator = (uClassButton const&);
};

#endif // UCLASSBUTTON_H
