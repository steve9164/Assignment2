#include "simulationfacade.h"

#include <map>

#include "debug.h"
#include "clusterbuilder.h"
#include "planetary_bodybuilder.h"



SimulationFacade::SimulationFacade()
    : m_universe(Cluster::getNewInstance())
{
    std::unique_ptr<Config> config;
    try
    {
        config.reset(new Config("config.ini"));
    }
    catch (const std::invalid_argument&)
    {
        std::cerr << "No simulation config! Exiting..." << std::endl;
        exit(1);
    }

    std::map<std::string, std::unique_ptr<ObjectPrototype>> freeObjects;

    // Build the bodies
    for (ConfigSection* cs : config->getSections())
    {
        std::list<ConfigKeyValue*> pairs = cs->getPairs();
        if (std::any_of(pairs.begin(), pairs.end(), [](ConfigKeyValue* kv){ return kv->getKey() == CONF_CLUSTER; }))
        {
            // ConfigSection refers to cluster
            ClusterBuilder builder(freeObjects);
            builder.buildBody(cs);
            std::unique_ptr<Cluster> cluster = builder.getCluster();
            freeObjects[cluster->getName()] = std::move(cluster);
        }
        else
        {
            PlanetaryBodyBuilder builder;
            builder.buildBody(cs);
            std::unique_ptr<Body> body = builder.getBody();
            freeObjects[body->getName()] = std::move(body);
        }

    }

    if (!freeObjects.empty())
    {
        for (auto it = freeObjects.begin(); it != freeObjects.end(); ++it)
        {
            m_universe->addSimulationObject(std::move(it->second));
        }
    }

}

SimulationFacade* SimulationFacade::singletonInstance = nullptr;

SimulationFacade *SimulationFacade::getInstance()
{
    if (!singletonInstance)
        singletonInstance = new SimulationFacade;
    return singletonInstance;
}

BodyIterator SimulationFacade::bodyBegin() const
{
    return BodyIterator(m_universe.get());
}

BodyIterator SimulationFacade::bodyEnd() const
{
    return BodyIterator(nullptr);
}

void SimulationFacade::updateSimulation(double timestep)
{
    for (auto it = bodyBegin(); it != bodyEnd(); ++it)
    {
        // Initial zero force vector for body it
        double xForce = 0.0,
               yForce = 0.0;

        for (auto it2 = bodyBegin(); it2 != bodyEnd(); ++it2)
        {
            if (it == it2)
                continue;

            // Add attraction between it and every other body
            it->addAttraction(*it2, xForce, yForce);
        }
        // Update it with the new force vector for the current timestep
        it->update(xForce, yForce, timestep);
    }
}
