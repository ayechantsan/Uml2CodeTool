#ifndef UPARAMETER
#define UPARAMETER

#include "uAccess.h"
#include <vector>
#include <iterator>



class uParameter {

public:
    explicit uParameter();
    uParameter(uAccess access, std::string const&type, std::string const& name);
    std::string getName() const;
    std::string getType() const;
    uAccess getAccess() const;
    inline bool operator==(const uParameter& p2) const;
    inline bool operator!=(const uParameter& p2) const;

private:
    std::string mName;
    std::string mType;
    uAccess mAccess;
};

typedef std::vector<uParameter*> TParameters;
typedef std::vector<uParameter*>::iterator TParametersIter;
typedef std::vector<uParameter*>::const_iterator TParametersConstIter;

#endif // UPARAMETER

