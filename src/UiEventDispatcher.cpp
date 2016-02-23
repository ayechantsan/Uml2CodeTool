#include "UiEventDispatcher.h"
#include "uDebugPrinter.h"
#include "uClassType.h"
#include "uClassButton.h"
#include "uInterfaceButton.h"
#include "uChildButton.h"
#include "uStringConverter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;


UiEventDispatcher::UiEventDispatcher(QObject *parent) : QObject(0)
{
    mCodeGenerator = &uCodeGenerationVisitor::getInstance();
    mClassDiagram = &uClassDiagram::getInstance();
    mClassButton = &uClassButton::getInstance();
}

void UiEventDispatcher::createClass(QString name, QString parent, QString methods, QString attributes)
{
    // convert method string to uMethod objects
    TMethods methodObjects = uStringConverter::parseMethods(methods.toStdString());

    // convert attribute string to uParameter objects
    TParameters attributeObjects = uStringConverter::parseAttributes(attributes.toStdString());

    // TODO
    TReferences referenceObjects;

    // find parent given name
    uInheritable * parentObj = mClassDiagram->find(parent);

    // call factory to create object
    mClassButton->create(uPublic, name.toStdString(), attributeObjects, methodObjects, referenceObjects, parentObj);
}

void UiEventDispatcher::updateClass(QString oldName, QString newName, QString parent, QString methods, QString attributes)
{
    // convert method string to uMethod objects
    TMethods methodObjects = uStringConverter::parseMethods(methods.toStdString());

    // convert attribute string to uParameter objects
    TParameters attributeObjects = uStringConverter::parseAttributes(attributes.toStdString());

    // TODO
    TReferences referenceObjects;

    // find parent given name
    uInheritable * parentObj = mClassDiagram->find(parent.toStdString());

    // call factory to create object
    mClassButton->update(oldName.toStdString(), uPublic, newName.toStdString(), attributeObjects, methodObjects, referenceObjects, parentObj);
}

void UiEventDispatcher::setClassState(int type)
{
    switch (type) {

        case 0:
            mClassButton = &uClassButton::getInstance();
            break;
        case 1:
            mClassButton = &uInterfaceButton::getInstance();
            break;
        case 2:
            mClassButton = &uChildButton::getInstance();
            break;
        default:
            break;
    }
}

void UiEventDispatcher::setLanguage(QString language)
{
    uDebugPrinter::printText("set language called " + language.toStdString());
    mCodeGenerator->setLanguage(uStringConverter::parseLanguage(language.toStdString()));
}

void UiEventDispatcher::setDevEnv(QString devenv)
{
    mProjectGenerator.setDevEnv(uStringConverter::parseDevEnv(devenv.toStdString()));
}

void UiEventDispatcher::generateCode()
{
    uDebugPrinter::printText("generating code");
    uDebugPrinter::printText("language: " + mCodeGenerator->getLanguage()->getName());

    // TODO
    mCodeGenerator->setFileAttributes("", "");

    mClassDiagram->applyVisitor(mCodeGenerator);
    uDebugPrinter::printText("done generating code");
}
//this is the function called by the eventDispatcher to call the mClassDiagram->applySaveVisitor to save the
//diagram to a text file in json format.
void UiEventDispatcher::saveDiagram()
{
    uDebugPrinter::printText("in the save function");
    mCodeGenerator->setFileAttributes("","");
    mClassDiagram->applySaveVisitor(mCodeGenerator);
}
//this method will load up one of our .uct files and use the uClassDiagram to add classes to the mClasses stack
void UiEventDispatcher::loadDiagram(QString url)
{
    uDebugPrinter::printText(" string loaded in:  " + url.toStdString());
    string fileLocation = url.toStdString();
    std::smatch match;
    std::regex reg ("\\b(file://)([^ ]*)");
    string location;
    int i = 0;
    //this is gross and needs to be fixed, but it does do what i need it to.
    if (std::regex_search(fileLocation, match, reg))
    {
        for (auto x:match)
        {
            uDebugPrinter::printText(x);
       // uDebugPrinter::printText("\n");
            if (i == 2)
            {
                location = x;
            }
            i++;
    }
           // location = match.str();
        fileLocation = match.suffix().str();

    }
    uDebugPrinter::printText("location: " + location);
     uDebugPrinter::printText("fileLocation: " + fileLocation);
    ifstream infile;
      infile.open(location);
      string line;
        if (infile.is_open())
        {
//TODO this needs to do more than print out but going to commit now.
            while ( getline (infile, line))
          {
            uDebugPrinter::printText( line +'\n');



          }
          infile.close();
        }
        else
       uDebugPrinter::printText("Unable to open file");



}

int UiEventDispatcher::getDiagramSize()
{
    return mClassDiagram->size();
}

uInheritable *UiEventDispatcher::getClass(int index)
{
    if (!(index < mClassDiagram->size())) return NULL;
    return mClassDiagram->get(index);
}

void UiEventDispatcher::removeClass(uInheritable *obj)
{
    if (obj == NULL) return;
    mClassDiagram->removeClass(obj);
}

void UiEventDispatcher::removeClass(QString name)
{
    uInheritable * obj = mClassDiagram->find(name);
    if (obj != NULL) {
        mClassDiagram->removeClass(obj);
    }
}

QString UiEventDispatcher::getClassName(int index)
{
    uInheritable * obj = getClass(index);
    if (obj == NULL) return "";

    return QString::fromStdString(obj->getName());
}

QString UiEventDispatcher::getClassMethods(int index)
{
    uInheritable * obj = getClass(index);
    if (obj == NULL) return "";

    return uStringConverter::qCreateMethodStringFromClass(obj);
}

QString UiEventDispatcher::getClassAttributes(int index)
{
    uInheritable * obj = getClass(index);
    if (obj == NULL) return "";

    return uStringConverter::qCreateAttributeStringFromClass(obj);
}

int UiEventDispatcher::getClassIndex(QString name)
{
    uInheritable * obj = mClassDiagram->find(name);
    if (obj == NULL) return -1;

    return mClassDiagram->getIndex(name);

}

QString UiEventDispatcher::getClassParent(int index)
{
    uInheritable * obj = getClass(index);
    if (obj == NULL || !obj->hasParent()) {
        return "";
    }
    uInheritable * parent = obj->getParent();
    if (parent == NULL) {
        return "";
    }

    return QString::fromStdString(parent->getName());
}

int UiEventDispatcher::getClassReferenceCount(QString name)
{
    uInheritable * obj = mClassDiagram->find(name);
    if (obj == NULL) return 0;
    return generateReferences(obj).size();
}

QString UiEventDispatcher::getClassReference(QString name, int index)
{
    uInheritable * obj = mClassDiagram->find(name);
    if (obj == NULL) return "";

    std::vector<QString> references = generateReferences(obj);
    if (index >= references.size()) return "";

    return references[index];
}

std::vector<QString> UiEventDispatcher::generateReferences(uInheritable * obj)
{
    std::vector<QString> references;
    TParameters attributes = obj->getAttributes();
    for (TParametersIter iter = attributes.begin(); iter != attributes.end(); ++iter) {
        if (mClassDiagram->contains((*iter)->getType())) {
            references.push_back(QString::fromStdString((*iter)->getType()));
        }
    }
    return references;
}


void UiEventDispatcher::generateProjectFile()
{
    mProjectGenerator.createFile(mClassDiagram);
}
