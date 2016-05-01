#ifndef PLANETARYBODYBUILDER_H
#define PLANETARYBODYBUILDER_H

#include "body.h"
#include "bodybuilder.h"
#include "config_section.h"

/*
 * Builds a new planetary Body object.
 */
class PlanetaryBodyBuilder : public BodyBuilder
{

public:
  PlanetaryBodyBuilder()
      : m_newBody(Body::getNewInstance()) { }

  /*
   * Builds a new Planetary Body object from the values contained
   * within the provided ConfigSection.
   */
  void buildBody(ConfigSection* cs);

  /*
   * Returns a pointer to the built Body object.
   */
  std::unique_ptr<Body> getBody();

  /*
   * DESTRUCTOR NOTE: newly created Body is **NOT** deleted here.
   * The user must delete it with the pointer returned by getBody().
   */
  virtual ~PlanetaryBodyBuilder() { }

private:
  std::unique_ptr<Body> m_newBody;
  ConfigSection* m_configSection;

};

#endif // PLANETARYBODYBUILDER_H
