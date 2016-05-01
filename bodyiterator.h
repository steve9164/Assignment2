#ifndef BODYITERATOR_H
#define BODYITERATOR_H

#include <iterator>
#include <stack>

class ObjectPrototype;
class Body;

// Iterate over the cluster & body tree and return references to all bodies



// Iterator is only valid if it is empty, or has an object at the top of the stack.
// The function iterateToNextBody ensures validity

class BodyIterator : public std::iterator<std::input_iterator_tag, int>
{
public:
    struct Info
    {
        ObjectPrototype& object;
        size_t index;
    };
    BodyIterator(ObjectPrototype* object);

    BodyIterator& operator++();

    BodyIterator operator++(int);

    Body& operator*();
    Body* operator->();

    bool operator==(const BodyIterator &other) const;
    bool operator!=(const BodyIterator &other) const;

private:
    void iterateToNextBody();
    std::stack<Info> m_iterationStack;
};

#endif // BODYITERATOR_H
