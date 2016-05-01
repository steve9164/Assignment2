#ifndef CLUSTERBUILDER_H
#define CLUSTERBUILDER_H

#include <map>

#include "bodybuilder.h"
#include "config_section.h"
#include "cluster.h"

#define CONF_CLUSTER ("cluster")

class ClusterBuilder : public BodyBuilder
{
public:
    ClusterBuilder(std::map<std::string, std::unique_ptr<ObjectPrototype>>& freeObjects)
        : m_freeObjects(freeObjects) { }

    virtual ~ClusterBuilder() { }

    virtual void buildBody(ConfigSection* cs);

    std::unique_ptr<Cluster> getCluster();

private:
    std::unique_ptr<Cluster> m_newCluster;
    ConfigSection* m_configSection;
    std::map<std::string, std::unique_ptr<ObjectPrototype>>& m_freeObjects;
};

#endif // CLUSTERBUILDER_H
