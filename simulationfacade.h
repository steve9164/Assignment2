#ifndef SIMULATIONFACADE_H
#define SIMULATIONFACADE_H

#include <memory>

#include "bodyiterator.h"
#include "cluster.h"
#include "config.h"

class SimulationFacade
{
public:
    SimulationFacade();
//    ZodiacIterator zodiacBegin() const;
//    ZodiacIterator zodiacEnd() const;
    BodyIterator bodyBegin() const;
    BodyIterator bodyEnd() const;
    void updateSimulation(double timestep);

private:
    std::unique_ptr<Cluster> m_universe;
    std::unique_ptr<Config> m_config;
};

#endif // SIMULATIONFACADE_H
