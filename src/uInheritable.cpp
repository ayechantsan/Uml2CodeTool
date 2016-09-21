#include "uInheritable.h"

#include "uDebugPrinter.h"



uInheritable::uInheritable()
{

}

uInheritable::uInheritable(const std::string &name)
{
    mName = name;
    mBaseClass = "";
}

uInheritable::uInheritable(uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, bool isAbstract)
{
    mAccess = access;
    mName = name;
    mAttributes = attributes;
    mMethods = methods;
    mReferences = references;
    mHasParent = false;
    mBaseClass = "";
    mIsAbstract = isAbstract;
}

uInheritable::~uInheritable()
{
    //uDebugPrinter::printText("uInheritable: DTor called");
}

void uInheritable::accept(uVisitor *visitor)
{

}

void uInheritable::acceptSave(uVisitor *visitor)
{

}
std::vector<uMethod*> uInheritable::getMethods() const
{
    return mMethods;
}

std::vector<uParameter*> uInheritable::getAttributes() const
{
    return mAttributes;
}

std::vector<uReference *> uInheritable::getReferences() const
{
    return mReferences;
}

uAccess uInheritable::getAccess() const
{
    return mAccess;
}

void uInheritable::setAccess(uAccess access)
{
    mAccess = access;
}

std::string uInheritable::getName() const
{
    return mName;
}

std::string uInheritable::getParent() const
{
    return mBaseClass;
}

double uInheritable::getLocX() const
{
    return this->locX;
}

double uInheritable::getLocY() const
{
    return this->locY;
}

QString uInheritable::qGetName() const
{
    return QString::fromStdString(mName);
}

bool uInheritable::hasParent() const
{
    return mHasParent;
}

bool uInheritable::isInterface() const
{
    return mIsInterface;
}

bool uInheritable::isAbstract() const
{
    return mIsAbstract;
}

bool uInheritable::operator==(const uInheritable &class1) const
{
    return mName==class1.getName() && mAccess==class1.getAccess() && mAttributes==class1.getAttributes() &&
            mReferences==class1.getReferences() && mMethods==class1.getMethods();
}

bool uInheritable::operator!=(const uInheritable &class1) const
{
    return !operator==(class1);
}

void uInheritable::addMethod(uMethod *method)
{
    mMethods.push_back(method);
}

void uInheritable::addAttribute(uParameter *attribute)
{
    mAttributes.push_back(attribute);
}

void uInheritable::addReference(uReference * reference)
{
    mReferences.push_back(reference);
}

void uInheritable::setLocX(double locx)
{
    this->locX = locx;
}

void uInheritable::setLocY(double locy)
{
    this->locY = locy;
}

void uInheritable::setLoc(double locx, double locy)
{
    this->locX = locx;
    this->locY = locy;
}

void uInheritable::setParent(std::string parent)
{
    mBaseClass = parent;
}

void uInheritable::changeParameterType(std::string oldName, std::string newName)
{
    for(TParametersConstIter iter = mAttributes.begin(); iter != mAttributes.end(); iter++)
    {
        if((*iter)->getType() == oldName)
            (*iter)->setType(newName);
    }
}

static bool operator==(TClasses& classes1, TClasses& classes2){
    if(classes1.size()!=classes2.size())
        return false;

    TClassesIter iter2 = classes2.begin();
    for (TClassesIter iter1 = classes1.begin(); iter1 != classes1.end(); iter1++, iter2++ ){
        if((*iter1)!=(*iter2))
            return false;
    }
    return true;
}

static bool operator!=(TClasses& classes1, TClasses& classes2){
    return !operator==(classes1,classes2);
}
