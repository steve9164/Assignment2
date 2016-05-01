#include "planetary_bodybuilder.h"
#include <QString>
#include <utility>
#define CONF_COL   ("colour")
#define CONF_RAD   ("radius")
#define CONF_MASS  ("mass")
#define CONF_X_POS ("pos_x")
#define CONF_Y_POS ("pos_y")
#define CONF_X_VEL ("vel_x")
#define CONF_Y_VEL ("vel_y")
#define CONF_LABEL ("label")



void PlanetaryBodyBuilder::buildBody(ConfigSection *cs)
{
  m_configSection = cs;
  ConfigKeyValue* kv;

  // Read properties from config

  // Set body name to be same as config section name
  m_newBody->setName(m_configSection->getName());

  try
  {
    kv = m_configSection->getByKey(CONF_COL);
    m_newBody->setColour(kv->getValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_COL, m_newBody->getColour());
  }

  // Mass
  try
  {
    kv = m_configSection->getByKey(CONF_MASS);
    m_newBody->setMass(kv->getDoubleValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_MASS,
                 QString::number(m_newBody->getMass()).toStdString());
  }

  // Radius
  try
  {
    kv = m_configSection->getByKey(CONF_RAD);
    m_newBody->setRadius(kv->getDoubleValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_RAD,
                 QString::number(m_newBody->getRadius()).toStdString());
  }

  // Position vector
  try
  {
    kv = m_configSection->getByKey(CONF_X_POS);
    m_newBody->setXPosition(kv->getDoubleValue() * AU);
  }
  catch (...)
  {
    configError(m_configSection, CONF_X_POS,
                 QString::number(m_newBody->getXPosition()).toStdString());
  }

  try
  {
    kv = m_configSection->getByKey(CONF_Y_POS);
    m_newBody->setYPosition(kv->getDoubleValue() * AU);
  }
  catch (...)
  {
    configError(m_configSection, CONF_Y_POS,
                 QString::number(m_newBody->getYPosition()).toStdString());
  }

  // Velocity vector
  try
  {
    kv = m_configSection->getByKey(CONF_X_VEL);
    m_newBody->setXVelocity(kv->getDoubleValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_X_VEL,
                 QString::number(m_newBody->getXVelocity()).toStdString());
  }

  try
  {
    kv = m_configSection->getByKey(CONF_Y_VEL);
    m_newBody->setYVelocity(kv->getDoubleValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_Y_VEL,
                 QString::number(m_newBody->getYVelocity()).toStdString());
  }

  // Render name option
  try
  {
    kv = m_configSection->getByKey(CONF_LABEL);
    m_newBody->setRenderName(kv->getBoolValue());
  }
  catch (...)
  {
    configError(m_configSection, CONF_LABEL, m_newBody->getRenderName() ? "true" : "false");
  }
}

std::unique_ptr<Body> PlanetaryBodyBuilder::getBody()
{
  return std::move(m_newBody);
}


