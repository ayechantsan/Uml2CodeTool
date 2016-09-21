#include "uClassDiagram.h"
#include <algorithm>
#include "uDebugPrinter.h"
#include "uBaseClass.h"
#include "uClassFactory.h"
#include "uClassButton.h"

using namespace std;

uClassDiagram::uClassDiagram()
{

}

uClassDiagram &uClassDiagram::getInstance()
{
    static uClassDiagram mInstance;
    return mInstance;
}

void uClassDiagram::addClass(uInheritable *uClass)
{
    if (uClass == NULL)
        uDebugPrinter::printText("error: null pointer");
    mClasses.push_back(uClass);
}
//overloaded method that accepts x and y cordinations.
void uClassDiagram::addClass(uInheritable *uClass, double x, double y)
{
    if (uClass == NULL)
        uDebugPrinter::printText("error: null pointer");
    uClass->setLocX(x);
    uClass->setLocY(y);
    mClasses.push_back(uClass);
}
void uClassDiagram::removeClass(uInheritable *uClass)
{
    if (uClass == NULL)
        uDebugPrinter::printText("error: null pointer");

    //remove parent from classes inheriting from it
    for(TClassesConstIter iter = mClasses.begin(); iter < mClasses.end(); iter++){
        if ((*iter)->hasParent() && (*iter)->getParent() == uClass->getName()){
            TParameters attributeObjects = (*iter)->getAttributes();
            TMethods methodObjects = (*iter)->getMethods();
            TReferences references = (*iter)->getReferences();
            std::string const& father = "";
            uClassButton::getInstance().update((*iter)->getName(), (*iter)->getAccess(), (*iter)->getName(), attributeObjects, methodObjects, references, father, (*iter)->isAbstract());
            removeClass(uClass);
            return;
        }
    }

    removeClass(QString::fromStdString(uClass->getName()));
}



bool uClassDiagram::removeClass(QString const &name)
{
    for(TClassesConstIter iter = mClasses.begin(); iter < mClasses.end(); iter++){
        if ((*iter)->getName() == name.toStdString()){
            mClasses.erase(std::remove(mClasses.begin(), mClasses.end(), (*iter)), mClasses.end());
            return true;
        }
    }
    return false;
}

bool uClassDiagram::contains(uInheritable *uClass) const
{
    if (uClass == NULL)
        uDebugPrinter::printText("error: null pointer");
    return std::find(mClasses.begin(), mClasses.end(), uClass) != mClasses.end();
}

bool uClassDiagram::contains(const string &name) const
{
    for(TClassesConstIter iter = mClasses.begin(); iter < mClasses.end(); iter++){
        if ((*iter)->getName() == name) return true;
    }
    return false;
}

uInheritable *uClassDiagram::find(QString const &name) const
{
    if (name == "") return NULL;

    for(TClassesConstIter iter = mClasses.begin(); iter < mClasses.end(); iter++){

        if ((*iter)->getName() == name.toStdString())
            return (*iter);

    }
    return NULL;
}

uInheritable *uClassDiagram::find(std::string const &name) const
{
    if (name == "") return NULL;

    for(TClassesConstIter iter = mClasses.begin(); iter < mClasses.end(); iter++){
        if ((*iter)->getName() == name)
            return (*iter);
    }
    return NULL;
}

void uClassDiagram::applyVisitor(uVisitor *visitor)
{
    if (visitor == NULL)
        uDebugPrinter::printText("NULL POINTER");

    for(TClassesIter iter = mClasses.begin(); iter < mClasses.end(); iter++){
        uDebugPrinter::printClass(*iter);
        (*iter)->accept(visitor);
    }
}
void uClassDiagram::applySaveVisitor(uVisitor *visitor)
{
    if (visitor == NULL)
        uDebugPrinter::printText("NUll POINTER");

    //size_t listSize = x.size();
    int i = 0;
    for(TClassesIter iter = mClasses.begin(); iter < mClasses.end(); iter++, i++){
        (*iter)->acceptSave(visitor);
    }
}

uInheritable *uClassDiagram::get(int index) const
{
    if (index >= mClasses.size()) return NULL;
    return mClasses[index];
}

int uClassDiagram::size() const
{
    return mClasses.size();
}

int uClassDiagram::getIndex(const QString &name) const
{
    for (size_t i=0; i<mClasses.size(); i++) {
        if (mClasses[i]->qGetName() == name) return i;
    }
    return -1;
}

bool uClassDiagram::changeReferenceName(string className, string oldName, string newName)
{
    bool referenceFound = false;
    for(TClassesConstIter iter = mClasses.begin(); iter != mClasses.end(); iter++)
    {
        if((*iter)->getName() == className)
        {
            (*iter)->changeParameterType(oldName, newName);
            referenceFound = true;
        }
    }

    return referenceFound;
}

void uClassDiagram::clearAll()
{
    mClasses.clear();
}
