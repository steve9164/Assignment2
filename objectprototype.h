#ifndef SIMULATIONOBJECT_H
#define SIMULATIONOBJECT_H


#include <string>
#include <utility>
#include <memory>

#include "bodyiterator.h"

// gravitational constant
constexpr double G  = 6.67428e-11;

// astronomical unit
constexpr double AU = 1.4960000e+11;

// ObjectPrototype is implemented by:
// - Cluster
// - Body

class ObjectPrototype
{
public:
    ObjectPrototype() = default;
    virtual ~ObjectPrototype() = default;

    ObjectPrototype(const ObjectPrototype&) = delete;

    virtual bool isCluster() const = 0;

    virtual ObjectPrototype* clone() = 0;
    static std::unique_ptr<ObjectPrototype> getNewInstance();


    // get object name
    virtual std::string getName() const = 0;
    virtual void setName(std::string name) = 0;


protected:
    friend class BodyIterator;
    virtual BodyIterator::Info getIteratorInfo() = 0;
};

#endif // SIMULATIONOBJECT_H
