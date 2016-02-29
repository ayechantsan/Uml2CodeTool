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
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

UiEventDispatcher::UiEventDispatcher(QObject *parent) : QObject(0)
{
    mCodeGenerator = &uCodeGenerationVisitor::getInstance();
    mClassDiagram = &uClassDiagram::getInstance();
    mClassButton = &uClassButton::getInstance();
}

void UiEventDispatcher::createClass(QString name, QString parent, QString methods, QString attributes)
{
//    uDebugPrinter::printText("------input text--------");
//    uDebugPrinter::printText(name.toStdString());
//    uDebugPrinter::printText(parent.toStdString());
//    uDebugPrinter::printText(methods.toStdString());
//    uDebugPrinter::printText(attributes.toStdString());

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
//this method will load up one of our .uct files and use the uEventDispatcher::creatClass() to add classes to the mClasses stack
QString UiEventDispatcher::loadDiagram(QString url)
{


    uDebugPrinter::printText(" string loaded in:  " + url.toStdString());
    string fileLocation = url.toStdString();
    string fileContent;
    std::smatch match;
    std::regex reg ("\\b(file://)([^ ]*)");
    string location;
    //this searches for file:/ and returns what follows it which is the path to the file selected.
    if (std::regex_search(fileLocation, match, reg))
    {
        //this gives me the string after what i was looking for which was "file:/".
        location = match[2];
    }
    //regular exprestion to search for things in the file taht wa
    regex anyReg("\"(.*?)\"");

    ifstream infile;
      infile.open(location);
      string line;
      int i = 0;
      int j = 0;
        if (infile.is_open())
        {
           //while there is file to read we are going to add to file Content to then parse and get classes
            while ( getline (infile, line))
          {
                    fileContent += line + "\n";
          }
          infile.close();
        }
        else uDebugPrinter::printText("Unable to open file");

        int classCount = 0;

        auto words_begain = sregex_iterator(fileContent.begin(), fileContent.end(), anyReg);
        auto words_end = sregex_iterator();
        int leng = distance(words_begain, words_end);
        //array to keep all the strings found between ""s
        string *foundArray = new string[leng];
        int myi = 0;
        //this iterator finds all the matches to the regex, addes them to foundArray and counts how many name tags are found.
        for (sregex_iterator i = words_begain; i != words_end; ++i)
        {
            smatch match = *i;
            string match_str = match.str();
            uDebugPrinter::printText(match_str);
            foundArray[myi] = match.str();
            myi++;
            if (match.str() == "\"name\"")
            {
                classCount++;
            }
        }
        //this array represents a class
        //{name, methodsString, attributesString, parent, interface, abstract}
        string **classArray = new string*[classCount];
        for (int i = 0; i < classCount; i ++)
        {
            classArray[i] = new string[6];
        }
        //
        classCount = 0;
        //for each item that was found we want to check what the value is and then grab the string after it in the array
        for (int u = 0; u < leng-1; u++ )
        {
            string word = foundArray[u];
            if (word =="\"name\"")
            {
                classCount++;
                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][0] = subString;
                uDebugPrinter::printText("name if: " + classArray[classCount-1][0]);

            }
            else if (word ==  "\"method\"")
            {
                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][1] += " " + subString;
                uDebugPrinter::printText("method if: " + classArray[classCount-1][1]);
            }
            else if (word == "\"attribute\"")
            {
                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][2] += " " + subString;
                uDebugPrinter::printText("attribute if: " + classArray[classCount-1][2]);
            }
            else if (word =="\"parent\"")
            {

                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][3] += " " + subString;
                uDebugPrinter::printText("parent if: " + classArray[classCount-1][3]);
            }
            else if (word =="\"interface\"")
            {
                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][4] += " " + subString;
                uDebugPrinter::printText("interface if: " + classArray[classCount-1][4]);
            }
            else if (word =="\"abstract\"")
            {
                string foundString = foundArray[u+1];
                const auto lastOfNot = foundString.find_last_not_of(" ");
                string subString = foundString.substr(1, lastOfNot-1);
                classArray[classCount-1][5] += " " + subString;
                uDebugPrinter::printText("abstract if: " + classArray[classCount-1][5]);
            }
        }
        //loop to add each of the classes collected to the class array
        string classNamesString ="";
        for (int i = 0; i < classCount; i++)
        {
            UiEventDispatcher::createClass(
                        QString::fromStdString(classArray[i][0]),
                        QString::fromStdString(classArray[i][3]),
                        QString::fromStdString(classArray[i][1]),
                        QString::fromStdString(classArray[i][2]));
            classNamesString += " " + classArray[i][0];
            uDebugPrinter::printText(classNamesString);
        }
        //clean up things i've added to the heap.
        for(int i = 0; i < classCount; ++i) {
            delete [] classArray[i];
        }
        delete [] foundArray;
        delete [] classArray;
        //final conversion from std::string to QString for the QML javascript function to consume.
        QString returnWords = QString::fromStdString(classNamesString);
        return returnWords;
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

bool UiEventDispatcher::getClassIsInterface(int index)
{
    uInheritable *obj = getClass(index);
    return obj->isInterface();
}

bool UiEventDispatcher::getClassIsAbstract(int index)
{
    uInheritable *obj = getClass(index);
    return obj->isAbstract();
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
