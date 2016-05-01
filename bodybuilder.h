#ifndef BUILDER_H
#define BUILDER_H

#include "config_section.h"

/*
 * An abstract Builder class from which conrete Body Builders should inherit.
 */
class BodyBuilder
{

public:
  // Builds a generic Body (abstract method)
  virtual void buildBody(ConfigSection* confSec) = 0;

protected:
    // Prints to stderr that keyName wasn't set properly, and
    // the value that will be used instead (from the prototype).
    // Error handling, yay!
    void configError(ConfigSection* cs, std::string keyName, std::string def);
};

#endif // BUILDER_H
