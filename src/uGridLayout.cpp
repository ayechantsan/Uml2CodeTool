#include "uGridLayout.h"
#include "uDebugPrinter.h"
#include "uGridObjectFactory.h"
#include <QVector>
#include <QString>
#include <string>

using namespace std;

uGridLayout::uGridLayout(QObject *parent) : QObject(0)
{

}

uGridLayout::uGridLayout(int width, int height) : QObject(0)
{
    mWidth = width;
    mHeight = height;
}


QString uGridLayout::getAllNames()
{
    QString thisString;
//    if (mTable.size() > 0)
//        thisString += (*mTable.begin())->getName();
//    else
//        return thisString;

    for(TGridClassConstIter iter= mTable.begin(); iter != mTable.end(); iter++) {

            thisString += (*iter)->getName() + " ";
    }
    return thisString;
}


bool uGridLayout::addClass(int i, int j, int i_to, int j_to, const QString &name)

{
    uDebugPrinter::printText("adding class: " + name.toStdString() + " index i: " + to_string(i) + " index j: " + to_string(j));

    mTable.push_back(uGridObjectFactory::createClass(i ,j ,i_to ,j_to ,name));

    return true;
}

void uGridLayout::addArrowFromString(QString arrowString)
{
    uGridArrow * arrow = new uGridArrow(arrowString.toStdString());
    if(!checkReferences(arrow))
        uDebugPrinter::printText("ERROR: Arrow-> " + arrowString.toStdString() + " found no reference");

    mArrows.push_back(arrow);
}

void uGridLayout::checkArrowSides()
{
    for(TGridClassConstIter iter = mTable.begin(); iter != mTable.end(); iter++)
        (*iter)->checkArrowConnections();
}

bool uGridLayout::checkReferences(uGridArrow * arrow)
{
    bool reference_found = false;
    for(TGridClassConstIter iter = mTable.begin(); iter != mTable.end(); iter++)
        if((*iter)->getName().toStdString() == arrow->getOrigin().toStdString()
                || (*iter)->getName().toStdString() == arrow->getDestination().toStdString())
        {
            reference_found = true;
            (*iter)->addReference(arrow);
        }

     return reference_found;
}


bool uGridLayout::removeObject(const QString &name)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            mTable.erase(iter);
            return true;
        }
    }
    return false;
}

bool uGridLayout::removeObject(int x, int y)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x,y)) {
            mTable.erase(iter);
            return true;
        }
    }
    return false;
}

bool uGridLayout::changeObjectName(const QString &name, const QString &newName)
{
    bool found = false;
    TGridClassConstIter foundPosition;

    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++)
    {
        if ((*iter)->getName() == name)
        {
            foundPosition = iter;
            found = true;
        }

        if ((*iter)->getName() == newName)
            return false;
    }

    if (found)
    {
        (*foundPosition)->setName(newName);
        for(TGridArrowConstIter iter = mArrows.begin(); iter != mArrows.end(); iter++)
            (*iter)->notifyNameChange(name, newName);

        return true;
    }
    return false;
}

bool uGridLayout::moveObject(const QString &name, int movX, int movY)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            //if(checkBounds((*iter)->getX() + movX, (*iter)->getY() + movY, (*iter)->getWidth(), (*iter)->getHeight())){
                (*iter)->setY((*iter)->getY() + movY);
                (*iter)->setX((*iter)->getX() + movX);
                (*iter)->setY_to((*iter)->getY_to() + movY);
                (*iter)->setX_to((*iter)->getX_to() + movX);
                (*iter)->notifyMovement(movX, movY); //notifies the arrows that it is moving
                return true;
            //}
        }
    }

    return false;
}

bool uGridLayout::createAggregation(const QString &aggregationName, const QString &name)
{
    bool aggregationNotFound = true;
    bool nameNotFound = true;

    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name)
            nameNotFound = false;
        if((*iter)->getName() == aggregationName)
            aggregationNotFound = false;
    }

    if (aggregationNotFound || nameNotFound)
        return false;

    //First If it is created already. If it is, I check it as created
    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++)
    {
        if((*iter)->equals(aggregationName, name, uAggregation)){
            (*iter)->setDeleted(false);
            return false;
        }
    }

    uGridArrow * arrow = new uGridArrow(aggregationName, name, uAggregation);
    mArrows.push_back(arrow);

    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name || (*iter)->getName() == aggregationName) {
            (*iter)->addReference(arrow);
        }
    }

    return true;
}

bool uGridLayout::createInheritance(const QString &name, const QString &parent)
{
    bool fatherNotFound = true;
    bool nameNotFound = true;

    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name)
            nameNotFound = false;
        if((*iter)->getName() == parent)
            fatherNotFound = false;
    }

    if (fatherNotFound || nameNotFound)
        return false;

    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++)
    {
        if((*iter)->equals(name, parent, uInheritance)){
            (*iter)->setDeleted(false);
            return false;
        }
    }

    uGridArrow * arrow = new uGridArrow(name, parent, uInheritance);
    mArrows.push_back(arrow);

    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name || (*iter)->getName() == parent) {
            (*iter)->addReference(arrow);
        }
    }

    return true;
}

int uGridLayout::getAggregationIndex(const QString &name, const QString &reference) const
{
    for(unsigned int i = 0; i < mArrows.size(); i++)
    {
        if(mArrows[i]->equals(name, reference, uAggregation))
            return i;
    }

    return -1;
}

int uGridLayout::getInheritanceIndex(const QString &name, const QString &reference) const
{
    for(unsigned int i = 0; i < mArrows.size(); i++)
    {
        if(mArrows[i]->equals(name, reference, uInheritance))
            return i;
    }

    return -1;
}

void uGridLayout::addSegmentToArrow(int arrowIndex, int mX, int mY, int mWidth, int mHeight) const
{
    mArrows[arrowIndex]->addSegment(uGridObjectFactory::createSegment(mX, mY, mX + mWidth, mY + mHeight));
    uDebugPrinter::printText("added segment ("+to_string(mX)+","+ to_string(mY) +"), size("+ to_string(mWidth) +","+ to_string(mHeight) +") "
                              "to arrow: " + to_string(arrowIndex));
}

//Deletes arrows with flag mDeleted as true
void uGridLayout::deleteNonExistentArrows()
{
    for(TGridArrowConstIter iter = mArrows.begin(); iter != mArrows.end(); iter++)
        if((*iter)->getDeleted()){
            //Check classes making reference to it to delete those references too
            for(TGridClassConstIter iter2 = mTable.begin(); iter2 != mTable.end(); iter2++)
                (*iter2)->deleteArrow(*iter);

            mArrows.erase(iter);

            deleteNonExistentArrows();
            return;
        }
}

void uGridLayout::setArrowsDeleted()
{
    for(TGridArrowConstIter iter = mArrows.begin(); iter != mArrows.end(); iter++)
        (*iter)->setDeleted(true);
}

QString uGridLayout::getString(int x, int y) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x, y)) {
            return (*iter)->getName();
        }
    }
    return "";
}

int uGridLayout::getArrowSelected(int x, int y) const
{
    for(int i = 0; i < mArrows.size(); i++)
    {
        if(mArrows[i]->selected(x,y) >= 0)
            return i;
    }
    return -1;
}

void uGridLayout::modifyArrow(int index, int oldX, int oldY, int newX, int newY)
{
    mArrows[index]->moveSegments(oldX, oldY, newX, newY);
}

void uGridLayout::mergeSegments(int arrowIndex)
{
    mArrows[arrowIndex]->mergeSegments();
}

int uGridLayout::getWidth() const
{
    return mWidth;
}

int uGridLayout::getHeight() const
{
    return mHeight;
}

int uGridLayout::getArrowsSize() const
{
    return mArrows.size();
}

int uGridLayout::getArrowSize(int index) const
{
    return mArrows[index]->getSize();
}

int uGridLayout::getArrowType(int index) const
{
    return mArrows[index]->getType();
}

QString uGridLayout::getArrowsString() const
{
    QString arrowString = QString::fromStdString("{\"Arrows\" :\n");
    for(TGridArrowConstIter iter = mArrows.begin(); iter != mArrows.end(); iter++)
        arrowString += QString::fromStdString("\"Arrow\":\"" + (*iter)->toString() + "\"\n");

    arrowString += QString::fromStdString("}");
    return arrowString;
}

bool uGridLayout::setWidth(int width)
{
    if (width < 0) return false;

    double ratio = (double)width/(double)mWidth;

    mWidth = width;

    //resize elements in grid
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++)
        (*iter)->resizeX(ratio);

    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++){
        int destX = getClassX((*iter)->getDestination());
        int destWidth = getClassWidth((*iter)->getDestination());
        (*iter)->resizeX(ratio, destX, destWidth);
    }

    //uDebugPrinter::printText("Set grid width: " + to_string(width));
    return true;
}

bool uGridLayout::setHeight(int height)
{
    if (height < 0) return false;

    double ratio = (double)height/(double)mHeight;

    mHeight = height;

    //resize elements in grid
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++)
        (*iter)->resizeY(ratio);

    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++){
        int destY = getClassY((*iter)->getDestination());
        int destHeight = getClassHeight((*iter)->getDestination());
        (*iter)->resizeY(ratio, destY, destHeight);
    }

    //uDebugPrinter::printText("Set grid height: " + to_string(height));
    return true;
}

int uGridLayout::getClassWidth(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getWidth();
        }
    }
    return -1;
}

int uGridLayout::getClassHeight(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getHeight();
        }
    }
    return -1;
}

int uGridLayout::getClassX(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getX();
        }
    }
    return -1;
}

int uGridLayout::getClassY(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getY();
        }
    }
    return -1;
}

int uGridLayout::getClassX_to(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getX_to();
        }
    }
    return -1;
}

int uGridLayout::getClassY_to(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getY_to();
        }
    }
    return -1;
}

int uGridLayout::getSegmentX(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getX();
}

int uGridLayout::getSegmentY(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getY();
}

//int uGridLayout::getClasses() const
//{
//    return 56;
//}

int uGridLayout::getSegmentX_to(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getX_to();
}

int uGridLayout::getSegmentY_to(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getY_to();
}

int uGridLayout::getSegmentWidth(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getWidth();
}

int uGridLayout::getSegmentHeight(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getHeight();
}

int uGridLayout::getSegmentLength(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getLength();
}

bool uGridLayout::isEmpty(int x, int y) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x, y)) {
            return false;
        }
    }
    return true;
}

bool uGridLayout::contains(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return true;
        }
    }
    return false;
}

void uGridLayout::cleanAll()
{
    mTable.clear();
    mArrows.clear();
}

void uGridLayout::moveAll(int movX, int movY)
{
    //move all classes
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++)
    {
            //if(checkBounds((*iter)->getX() + movX, (*iter)->getY() + movY, (*iter)->getWidth(), (*iter)->getHeight())){
            (*iter)->setY((*iter)->getY() + movY);
            (*iter)->setX((*iter)->getX() + movX);
            (*iter)->setY_to((*iter)->getY_to() + movY);
            (*iter)->setX_to((*iter)->getX_to() + movX);
                //(*iter)->notifyMovement(movX, movY); //notifies the arrows that it is moving
            //}
    }

    //move all arrows
    for(TGridArrowConstIter iter=mArrows.begin(); iter!= mArrows.end(); iter++)
    {
        (*iter)->moveAllSegments(movX, movY);
    }


}

bool uGridLayout::checkBounds(int i, int j, int width, int height) const
{
    return (i + width <mWidth && j + height <mHeight && i>=0 && j >= 0);
}

bool uGridLayout::checkBounds(int i, int j) const
{
    return (i <mWidth && j <mHeight && i>=0 && j >= 0);
}


