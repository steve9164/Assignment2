#include <cmath>

#include "body.h"
#include "debug.h"

// This is auto-created by getNewInstance() when it is needed
std::unique_ptr<Body> Body::typicalInstance = nullptr;

Body *Body::clone()
{
  return new Body(m_mass,
                  m_radius,
                  m_xPosition,
                  m_yPosition,
                  m_xVelocity,
                  m_yVelocity);
}

std::unique_ptr<Body> Body::getNewInstance()
{
  // Create our prototypical instance if it doesn't exist
  if (Body::typicalInstance == nullptr)
  {
    Body::typicalInstance = std::unique_ptr<Body>(new Body(1,1,0,0,0,0));
  }
  // Now just return it
  return std::unique_ptr<Body>(Body::typicalInstance->clone());
}

double Body::getDistance(const Body &other) const
{
  double xDelta = other.getXPosition() - m_xPosition;
  double yDelta = other.getYPosition() - m_yPosition;
  double distance =  sqrt(xDelta * xDelta + yDelta * yDelta);
  return distance;
}

void Body::addAttraction(const Body &other, double &xForce, double &yForce)
{
  double distance = getDistance(other);
  double xDelta = other.getXPosition() - m_xPosition;
  double yDelta = other.getYPosition() - m_yPosition;
  double theta = atan2(yDelta, xDelta);
  double force = G * m_mass * other.getMass() / (distance * distance);
  xForce += force * cos(theta);
  yForce += force * sin(theta);
}

void Body::update(double xTotalForce, double yTotalForce, double timestep)
{
  // calculate acceleration
  double xAccel = xTotalForce / m_mass;
  double yAccel = yTotalForce / m_mass;

  // integrate acceleration
  m_xVelocity += xAccel * timestep;
  m_yVelocity += yAccel * timestep;

  // integrate velocity
  m_xPosition += m_xVelocity * timestep;
  m_yPosition += m_yVelocity * timestep;
}

bool Body::getRenderName() const
{
  return m_renderName;
}

void Body::setRenderName(bool renderName)
{
  m_renderName = renderName;
}

Body::~Body()
{
  DEBUG("Body destructor");
}
