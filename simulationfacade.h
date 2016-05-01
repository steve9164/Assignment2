#ifndef SIMULATIONFACADE_H
#define SIMULATIONFACADE_H

#include <memory>

#include "bodyiterator.h"
#include "cluster.h"
#include "config.h"

class SimulationFacade
{
public:
    SimulationFacade(SimulationFacade&) = delete;
    static SimulationFacade* getInstance();
//    ZodiacIterator zodiacBegin() const;
//    ZodiacIterator zodiacEnd() const;
    BodyIterator bodyBegin() const;
    BodyIterator bodyEnd() const;
    void updateSimulation(double timestep);

private:
    SimulationFacade();
    static SimulationFacade* singletonInstance;
    std::unique_ptr<Cluster> m_universe;

    friend class ListObjects; // Lists objects in the heirarchy
};

#endif // SIMULATIONFACADE_H
