#ifndef SIMULATIONCLUSTER_H
#define SIMULATIONCLUSTER_H

#include "objectprototype.h"
#include "bodyiterator.h"
#include <memory>
#include <vector>

class ListObjects;

class Cluster : public ObjectPrototype
{
public:
    virtual ~Cluster() { }

    virtual bool isCluster() const { return true; }

    Cluster* clone();

    static std::unique_ptr<Cluster> getNewInstance();

    // get object name
    std::string getName() const { return m_name; }
    void setName(std::string name) { m_name = name; }

    std::string getClusterType() const { return m_clusterType; }
    void setClusterType(std::string clusterType) { m_clusterType = clusterType; }

    // Add a body or cluster to this cluster
    void addSimulationObject(std::unique_ptr<ObjectPrototype> other);

protected:
    friend class BodyIterator; // Needs getIteratorInfo & access to m_objects
    BodyIterator::Info getIteratorInfo() { return {*this, 0}; }

private:
    friend class ListObjects; // Needs access to m_objects to show object hierarchy

    // Force cloning
    Cluster(std::string name, std::string clusterType)
        : m_name(name), m_clusterType(clusterType) { }

    // prototypical instance
    static std::unique_ptr<Cluster> typicalInstance;

    // Bodies and other clusters in this cluster
    // Use unique_ptr to show ownership of the pointer
    std::vector<std::unique_ptr<ObjectPrototype>> m_objects;

    std::string m_name; // name of body in simulation
    std::string m_clusterType; // Type of cluster (can be "solar system", "galaxy" or "cluster")
};

#endif // SIMULATIONCLUSTER_H
