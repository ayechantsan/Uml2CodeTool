#include "uClassFactory.h"
#include "uDebugPrinter.h"
uClassFactory::uClassFactory()
{

}

uClassFactory &uClassFactory::getInstance()
{
    static uClassFactory instance;
    return instance;
}

uInheritable * uClassFactory::createClass(uClassType type, std::string const& name)
{
    switch (type) {

        case eBaseClass:
            return new uBaseClass(name);
            break;
        case eInterface:
            return new uInterface(name);

            break;
        case eChildClass:
            return new uChildClass(name);

            break;
        default:
            return NULL;
            break;
    }
}

uInheritable * uClassFactory::createClass(uClassType type, uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, const std::string &base, bool isAbstract)
{
    switch (type) {

        case eBaseClass:
            return new uBaseClass(access, name, attributes, methods, references,isAbstract);
            break;

        case eInterface:
            return new uInterface(access, name, attributes, methods, references);
            break;

        case eChildClass:
            return new uChildClass(access, name, attributes, methods, references, base, isAbstract);
            break;

        default:
            return NULL;
            break;
    }

}
//overloaded to provide the x and y
uInheritable * uClassFactory::createClass(uClassType type, uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, std::string const& base, bool isAbstract, double x, double y)
{
    switch (type) {

        case eBaseClass:
            uDebugPrinter::printText("base factory with x");
            return new uBaseClass(access, name, attributes, methods, references,isAbstract, x, y);
            break;

        case eInterface:
            uDebugPrinter::printText("interface factory with x");
            return new uInterface(access, name, attributes, methods, references, x ,y );
            break;

        case eChildClass:
            uDebugPrinter::printText("child factory with x");
            return new uChildClass(access, name, attributes, methods, references, base, isAbstract, x , y);
            break;

        default:
            return NULL;
            break;
    }

}

