#ifndef UIEVENTDISPATCHER_H
#define UIEVENTDISPATCHER_H

#include <QObject>
#include <QString>
#include <QList>
#include <string>
#include <vector>
#include "uStringConverter.h"
#include "uClassType.h"
#include "uLanguageStrategy.h"
#include "uCodeGenerationVisitor.h"
#include "uClassDiagram.h"
#include "uCodeGenerationVisitor.h"
#include "uClassFactory.h"
#include "uButton.h"
#include "uInheritable.h"
#include "uProjectFileCreator.h"


class UiEventDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit UiEventDispatcher(QObject *parent = 0);


    Q_INVOKABLE void createClass(QString name, QString parent, QString methods, QString attributes, bool isAbstract);
    Q_INVOKABLE void createClass(QString name, QString parent, QString methods, QString attributes, bool isAbstract, double x, double y);

    Q_INVOKABLE int getClassX(QString name);
    Q_INVOKABLE int getClassY(QString name);
    Q_INVOKABLE void updateClass(QString oldName, QString newName, QString parent, QString methods, QString attributes, bool isAbstract);

    Q_INVOKABLE void setClassState(int type);

    Q_INVOKABLE void setLanguage(QString language);

    Q_INVOKABLE void setDevEnv(QString devenv);
    Q_INVOKABLE void generateCode();
    Q_INVOKABLE void generateProjectFile(QString name);
    Q_INVOKABLE void saveDiagram(QString url, QList<QString> names, QList<double> xLoc, QList<double> yLoc);
    Q_INVOKABLE void saveArrows(QString arrows);
    Q_INVOKABLE QString loadDiagram(QString url);
    Q_INVOKABLE QString loadArrows(QString url);

    Q_INVOKABLE int getDiagramSize();
    Q_INVOKABLE uInheritable * getClass(int index);
    Q_INVOKABLE void removeClass(uInheritable * obj);
    Q_INVOKABLE void removeClass(QString name);

    Q_INVOKABLE QString getClassName(int index);
    Q_INVOKABLE QString getClassMethods(int index, bool accessSymbol);
    Q_INVOKABLE QString getClassAttributes(int index, bool accessSymbol);
    Q_INVOKABLE int getClassIndex(QString name);
    Q_INVOKABLE QString getClassParent(int index);
    Q_INVOKABLE bool getClassIsInterface(int index);
    Q_INVOKABLE bool getClassIsAbstract(int index);
    Q_INVOKABLE int getClassReferenceCount(QString name);
    Q_INVOKABLE QString getClassReference(QString name, int index);

    Q_INVOKABLE void setUrl(QString string);
    Q_INVOKABLE QString getUrl();

    Q_INVOKABLE void clearAll();

signals:

public slots:

private:
    //enums to let words represtent indecies in an array
    enum loadAttribute {
        name,
        methods,
        attributes,
        parent,
        interface,
        abstract,
        xLoc,
        yLoc
    };
    QString url;
    // link application logic with GUI
    bool mCreateDoxyGenComments;
    std::string folderName;
    std::string projectFile;
    uButton * mClassButton;
    uClassDiagram * mClassDiagram;
    uCodeGenerationVisitor * mCodeGenerator;
    uProjectFileCreator mProjectGenerator;
    std::vector<QString> generateReferences(uInheritable * obj);

};

#endif // UIEVENTDISPATCHER_H
