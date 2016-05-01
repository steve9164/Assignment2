#include "simulationfacade.h"

#include <map>

#include "debug.h"
#include "clusterbuilder.h"
#include "planetary_bodybuilder.h"



SimulationFacade::SimulationFacade()
    : m_universe(Cluster::getNewInstance())
{
    m_universe->setName("Universe");

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

BodyIterator SimulationFacade::begin() const
{
    return BodyIterator(m_universe.get());
}

BodyIterator SimulationFacade::end() const
{
    return BodyIterator(nullptr);
}

void SimulationFacade::updateSimulation(double timestep)
{
    for (Body& b1 : *this)
    {
        // Initial zero force vector for body it
        double xForce = 0.0,
               yForce = 0.0;

        for (Body& b2 : *this)
        {
            if (&b1 == &b2)
                continue;

            // Add attraction between it and every other body
            b1.addAttraction(b2, xForce, yForce);
        }
        // Update it with the new force vector for the current timestep
        b1.update(xForce, yForce, timestep);
    }
}
