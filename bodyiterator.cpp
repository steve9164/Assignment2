#include "bodyiterator.h"
#include "cluster.h"
#include "body.h"


BodyIterator::BodyIterator(ObjectPrototype* object)
{
    // nullptr used for end iterator
    if (object != nullptr)
        m_iterationStack.push(object->getIteratorInfo());
    iterateToNextBody();
}

BodyIterator& BodyIterator::operator++()
{
    // Pop the current body off the stack (must be a body, otherwise iterator is invalid)
    m_iterationStack.pop();
    iterateToNextBody();
    return *this;
}

BodyIterator BodyIterator::operator++(int)
{
    BodyIterator temp(*this);
    ++(*this);
    return temp;
}

Body& BodyIterator::operator*()
{
    // Throws if stack is empty. This is fine, because you can't dereference an end iterator
    return dynamic_cast<Body&>(m_iterationStack.top().object);
}

Body* BodyIterator::operator->()
{
    // Throws if stack is empty. This is fine, because you can't dereference an end iterator
    // Dynamic cast Base -> Derived is always safe because the iterator is only valid if top is a Body
    return dynamic_cast<Body*>(&m_iterationStack.top().object);
}

bool BodyIterator::operator==(const BodyIterator &other) const
{
    // Equal if both empty, or if the top body is the same for both
    // (1 body can't be in 2 different clusters because of the unique ownership constraint imposed by unique_ptr)
    bool bothEmpty = m_iterationStack.empty() && other.m_iterationStack.empty();
    bool bothNotEmpty = !m_iterationStack.empty() && !other.m_iterationStack.empty();
    return bothEmpty || (bothNotEmpty && (&m_iterationStack.top().object == &other.m_iterationStack.top().object));
}

bool BodyIterator::operator!=(const BodyIterator &other) const
{
    return !(*this == other);
}

void BodyIterator::iterateToNextBody()
{
    while (!m_iterationStack.empty() && m_iterationStack.top().object.isCluster())
    {
        Info& top = m_iterationStack.top();
        const Cluster& cluster = dynamic_cast<const Cluster&>(top.object);

        // If all objects of this cluster have already been visited
        if (top.index >= cluster.m_objects.size())
        {
            m_iterationStack.pop();
        }
        else
        {
            // Add object from cluster and increment cluster index
            m_iterationStack.push(cluster.m_objects[top.index++]->getIteratorInfo());
        }
    }

    // The stack is now either empty or has the next body at the top
}
