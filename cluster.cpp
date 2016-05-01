#include "cluster.h"


// This is auto-created by getNewInstance() when it is needed
std::unique_ptr<Cluster> Cluster::typicalInstance = nullptr;

Cluster* Cluster::clone()
{
    Cluster* newCluster = new Cluster(m_name, m_clusterType);
    // Deep copy each object in the cluster
    for (const std::unique_ptr<ObjectPrototype>& object : m_objects)
        newCluster->addSimulationObject(std::unique_ptr<ObjectPrototype>(object->clone()));

    return newCluster;
}

std::unique_ptr<Cluster> Cluster::getNewInstance()
{
  // Create our prototypical instance if it doesn't exist
  if (Cluster::typicalInstance == nullptr)
  {
    Cluster::typicalInstance.reset(new Cluster("", "cluster"));
  }
  // Now clone it
  return std::unique_ptr<Cluster>(Cluster::typicalInstance->clone());
}

void Cluster::addSimulationObject(std::unique_ptr<ObjectPrototype> other)
{
    if (other) // Don't add nullptrs
        m_objects.push_back(std::move(other));
}
