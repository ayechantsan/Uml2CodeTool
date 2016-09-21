
#include "uParameter.h"

using namespace std;

uParameter::uParameter()
{

}

uParameter::uParameter(uAccess access, std::string const&type, std::string const& name)
{
    mName = name;
    mType = type;
    mAccess = access;
}

string uParameter::getName() const
{
    return mName;
}

string uParameter::getType() const
{
    return mType;
}

uAccess uParameter::getAccess() const
{
    return mAccess;
}

void uParameter::setType(string newType)
{
    mType = newType;
}

bool uParameter::operator==(const uParameter &p2) const
{
    return mAccess==p2.getAccess() && mName==p2.getName() && mType==p2.getType();
}

bool uParameter::operator!=(const uParameter &p2) const
{
    return !operator==(p2);
}

static bool operator==(TParameters& param1, TParameters& param2){
    if(param1.size()!=param2.size())
        return false;

    TParametersIter iter2 = param2.begin();
    for (TParametersIter iter1 = param1.begin(); iter1 != param1.end(); iter1++, iter2++ ){
        if((*iter1)!=(*iter2))
            return false;
    }
    return true;
}

static bool operator!=(TParameters& param1, TParameters& param2){
    return !operator==(param1,param2);
}
