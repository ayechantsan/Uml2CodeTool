#include "uCodeGenerationVisitor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "uDebugPrinter.h"

using namespace std;

/**
 * @brief uCodeGenerationVisitor::uCodeGenerationVisitor, the constructor establishes the Author and the Date. This could be changed with
 * "setFileAttributes" but it is common for all the classes.
 */

uCodeGenerationVisitor::uCodeGenerationVisitor()
{
    mAuthor = "";
    mDate = "";
}

uCodeGenerationVisitor &uCodeGenerationVisitor::getInstance()
{
    static uCodeGenerationVisitor instance;
    return instance;
}

void uCodeGenerationVisitor::setLanguage(uLanguageStrategy * language)
{
    mLanguage = language;
}

uLanguageStrategy * uCodeGenerationVisitor::getLanguage() const
{
    return mLanguage;
}

void uCodeGenerationVisitor::setFileAttributes(const string &author, const string &date)
{
    mAuthor = author;
    mDate = date;
}

void uCodeGenerationVisitor::visit(uChildClass *childClass)
{
    if (mLanguage->hasSeparateFiles()) {
        createFile(childClass->getName() + mLanguage->getImplementationFileExtension(), mAuthor, mDate, mLanguage->createImplementationFileContent(childClass, childClass->getParent()->getName()), mLanguage->getLineComment());
        cout << "    " << childClass->getName() + mLanguage->getImplementationFileExtension() << endl;
    }
    createFile(childClass->getName() + mLanguage->getDeclarationFileExtension(), mAuthor, mDate, mLanguage->createDeclarationFileContent(childClass, childClass->getParent()->getName()), mLanguage->getLineComment());
    cout << "    " << childClass->getName() + mLanguage->getDeclarationFileExtension() << endl;
}

void uCodeGenerationVisitor::visit(uBaseClass *baseClass)
{
    if (mLanguage->hasSeparateFiles()) {
        createFile(baseClass->getName() + mLanguage->getImplementationFileExtension(), mAuthor, mDate, mLanguage->createImplementationFileContent(baseClass), mLanguage->getLineComment());
        cout << "    " << baseClass->getName() + mLanguage->getImplementationFileExtension() << endl;
    }
    createFile(baseClass->getName() + mLanguage->getDeclarationFileExtension(), mAuthor, mDate, mLanguage->createDeclarationFileContent(baseClass), mLanguage->getLineComment());
    cout << "    " << baseClass->getName() + mLanguage->getDeclarationFileExtension() << endl;
}

void uCodeGenerationVisitor::visit(uInterface *interfaceClass)
{
    if (mLanguage->hasSeparateFiles()) {
        createFile(interfaceClass->getName() + mLanguage->getImplementationFileExtension(), mAuthor, mDate, mLanguage->createImplementationFileContent(interfaceClass), mLanguage->getLineComment());
        cout << "    " << interfaceClass->getName() + mLanguage->getImplementationFileExtension() << endl;
    }
    createFile(interfaceClass->getName() + mLanguage->getDeclarationFileExtension(), mAuthor, mDate, mLanguage->createDeclarationFileContent(interfaceClass), mLanguage->getLineComment());
    cout << "    " << interfaceClass->getName() + mLanguage->getDeclarationFileExtension() << endl;
}
string uCodeGenerationVisitor::createAttributeString(uParameter * attribute)
{
    string attributeString = getAccessString(attribute->getAccess()) + " " + attribute->getType() + " " + attribute->getName() + ";";
    return attributeString;
}
std::string uCodeGenerationVisitor::createMethodString(uMethod * method)
{
    string methodStr = "{\"method\" : \"";
    TParameters params = method->getParameters();
    methodStr += getAccessString(method->getAccess()) + " " + method->getReturnType() + " " + method->getName() + "\"},\n";
    methodStr += "\t{\"parameters\" : \"";
    if (params.size() > 0) {
        for (TParametersIter iter = params.begin(); iter < params.end()-1; ++iter) {
            methodStr += (*iter)->getType() + " " + (*iter)->getName() + ", ";
        }
        methodStr += params[params.size()-1]->getType() + " " + params[params.size()-1]->getName();
    }
//    methodStr += ") \n\t{\n\t\t// TODO\n\t}\n\n";

    return methodStr + "}\n";
}
string uCodeGenerationVisitor::createContent(uInheritable * aClass, string const& base)
{

        stringstream fileContent;
//iterate through all the attributes associated with the current class and retrun the parameter and methods in a string
        TParameters attributes = aClass->getAttributes();
        fileContent << "\t{\"attributes\":[" << endl;
        for (TParametersIter iter = attributes.begin(); iter < attributes.end(); ++iter) {
            if (iter < attributes.end()-1)
            {
                fileContent << "\t\t{\"attribute\" : \"" << createAttributeString(*iter) << "\"}," << endl;
            }
            else
            {
                fileContent << "\t\t{\"attribute\" : \"" << createAttributeString(*iter) << "\"}" << endl;
            }
        }
        fileContent << "\t\t]},\n \t{\"methods\" : [" << endl;
        // methods
        TMethods methods = aClass->getMethods();
        for (TMethodsIter iter = methods.begin(); iter < methods.end(); ++iter) {
            if (iter < methods.end()-1)
            {
                fileContent << "\t\t" << createMethodString(*iter)  << endl;
            }
            else
            {
                fileContent << "\t\t" << createMethodString(*iter) << endl;
            }
            cout << *iter << " ";
        }
        fileContent << "\t]}";
        return fileContent.str();

}

//save visit functions one for each type of class that could be visited.
void uCodeGenerationVisitor::visitSave(uChildClass *childClass)
{

    saveDiagram(childClass->getName(), mAuthor, mDate, createContent(childClass, childClass->getParent()->getName()));
    cout << "    " << childClass->getName()  << endl;
}

void uCodeGenerationVisitor::visitSave(uBaseClass *baseClass)
{

    saveDiagram(baseClass->getName(), mAuthor, mDate, createContent(baseClass));
    cout << "    " << baseClass->getName()  << endl;
}

void uCodeGenerationVisitor::visitSave(uInterface *interfaceClass)
{

    saveDiagram(interfaceClass->getName(), mAuthor, mDate, createContent(interfaceClass));
    cout << "    " << interfaceClass->getName()  << endl;
}

bool uCodeGenerationVisitor::createFile(string const& name, string const& author, string const& date, string const& content, string const& lineComment, string const& path)
{
    ofstream myfile;
    myfile.open(path+name.c_str());
    if (!myfile.is_open())
        return false;

    myfile << getFileHeader(name, author, date, lineComment);
    myfile << content;
    myfile.close();
    //saveDiagram(name, author, date, content, lineComment, path);

    return true;
}
//method to save the diagram to a file using JSON objects to represent them
bool uCodeGenerationVisitor::saveDiagram(string const& name, string const& author, string const& date, string const& content, string const& path)
{
    ofstream myfile;
    const string & temp = "/tmp/";
//    myfile.open(temp+name.c_str() + ".uct", ios::app);
    myfile.open("/tmp/current.uct", ios::app);

    if (!myfile.is_open())
        return false;
//this will work but i need it do work a bit differently than this because i only want one file.
    myfile << "\{\"classes\" : [\n";
    myfile << "\t{\"name\":\"" +name + "\"},\n";
    myfile << "\t{\"author\":\"" + author + "\"},\n";
    myfile << "\t{\"date\":\"" + date + "\"},\n";
    myfile << "\t{\"content\": " + content + "}\n";
    myfile.close();
    return true;
}
string uCodeGenerationVisitor::getFileHeader(std::string const& fileName, std::string const& author, std::string const& date, std::string const& lineComment)
{
    string header = "";
    header += lineComment + " ------------------------------------------------------------------\n";
    header += lineComment + " File created with uCode - https://github.com/dstoeg/Uml2CodeTool\n";
    header += lineComment + " ------------------------------------------------------------------\n";
    header += lineComment + " file      : " + fileName + "\n";
    header += lineComment + " author    : " + author + "\n";
    header += lineComment + " created   : " + date   + "\n";
    header += lineComment + " ------------------------------------------------------------------\n\n";

    return header;
}
