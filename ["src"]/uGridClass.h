#ifndef UGRIDCLASS_H
#define UGRIDCLASS_H

#include "uGridObject.h"
#include "uGridArrow.h"
#include <QString>

class uGridClass: public uGridObject
{
public:
    uGridClass(int mX, int mY, int mX_to, int mY_to, QString mName);
    virtual ~uGridClass(){}

    virtual bool selected(int x, int y) const;

    bool notifyMovement(int movX, int movY);

    bool setName(const QString &newName);

    QString getName() const;

    bool addReference(uGridArrow * arrow);

private:
    QString mName;
    TGridArrow mArrows;
};

typedef std::vector<uGridClass*> TGridClass;
typedef std::vector<uGridClass*>::iterator TGridClassIter;
typedef std::vector<uGridClass*>::const_iterator TGridClassConstIter;

#endif // UGRIDCLASS_H
