#include "clusterbuilder.h"
#include <regex>

#define CONF_CONTAINS ("contains")

void ClusterBuilder::buildBody(ConfigSection* cs)
{
    static std::regex delimiter(",");
    m_configSection = cs;
    ConfigKeyValue* kv;

    // Read properties from config

    // Set body name to be same as config section name
    m_newCluster->setName(m_configSection->getName());

    try
    {
        kv = m_configSection->getByKey(CONF_CLUSTER);
        m_newCluster->setClusterType(kv->getValue());
    }
    catch (...)
    {
        configError(m_configSection, CONF_CLUSTER, m_newCluster->getClusterType());
    }


    std::string objects = m_configSection->getByKey(CONF_CONTAINS)->getValue();

    auto itEnd = std::sregex_token_iterator();
    auto it = std::sregex_token_iterator(objects.begin(), objects.end(), delimiter, -1);
    for (; it != itEnd; ++it)
    {
        if (m_freeObjects.count(*it) != 0)
        {
            // Move an object from the free objects map into a cluster
            m_newCluster->addSimulationObject(std::move(m_freeObjects[*it]));
        }

    }
}

std::unique_ptr<Cluster> ClusterBuilder::getCluster()
{
  return std::move(m_newCluster);
}
