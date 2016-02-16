#ifndef UVISITOR
#define UVISITOR

#include "uChildClass.h"
#include "uBaseClass.h"
#include "uInterface.h"

class uVisitor {

public:
    virtual void visit(uChildClass * childClass) {}
    virtual void visit(uBaseClass * baseClass) {}
    virtual void visit(uInterface * interfaceClass) {}
    virtual void visitSave(uChildClass * childClass) {}
    virtual void visitSave(uBaseClass * baseClass) {}
    virtual void visitSave(uInterface * interfaceClass) {}
};

#endif // UVISITOR

