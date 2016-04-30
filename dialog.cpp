#include "planetary_bodybuilder.h"
#include "dialog.h"
#include "ui_dialog.h"

// time step for the simulation (default 10000)
#define TIMESTEP (10000)

// width and height of dialog box
#define DIALOG_WIDTH (600)
#define DIALOG_HEIGHT (600)

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  // Read config file config.ini from the working dir
  try
  {
    m_config = new Config("config.ini");
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "No simulation config! Exiting..." << std::endl;
    exit(1);
  }

  // Build the bodies
  for (ConfigSection* cs : m_config->getSections())
  {
      PlanetaryBodyBuilder builder;
      builder.buildBody(cs);
      m_bodies.push_back(builder.getBody());
  }

  // Create the dialog
  ui->setupUi(this);
  this->update();
  this->resize(DIALOG_WIDTH, DIALOG_HEIGHT);

  // Use a black background because it's SPAAAAAAAAAAAAAAACE
  this->setStyleSheet("background-color: #000000;");

  // Simulation is initially not paused
  this->paused = false;

  // Update the velocities and positions, etc. every 16ms
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
  timer->start(16);
}

void Dialog::nextFrame()
{
  if (this->paused) {
      return;
  }

  // Update total forces for all bodies b1, b2 where b1 != b2
  for (Body* b1 : m_bodies)
  {
      // Initial zero force vector for b1
      double xForce = 0.0,
             yForce = 0.0;

      // Add attraction between b1 and every other body
      for (Body* b2 : m_bodies)
      {
        if (b1 != b2)
        {
          b1->addAttraction(*b2, xForce, yForce);
        }
      }

      // Update b1 with the new force vector for the current timestep
      b1->update(xForce, yForce, TIMESTEP);
  }

  update();
}

Dialog::~Dialog()
{
  DEBUG("Dialog destructor");

  delete ui;
  delete m_config;

  // Ensure every body destructor is called when the Dialog is closed
  for (Body* b : m_bodies)
  {
    delete b;
  }
  m_bodies.clear();
}

// location of center
#define X_CENTER (300)
#define Y_CENTER (300)

// offset for text rendering
#define TXT_X_OFFSET (-35)
#define TXT_Y_OFFSET (+15)

// scaling constant for rendering bodies on screen
// (zoomed out a bit compared to tutorial code)
#define SCALE (160 / AU)

void Dialog::paintEvent(QPaintEvent*)
{
  QPainter painter(this);

  // set pen
  QPen bodyPen(Qt::black);
  bodyPen.setWidth(1);

  // White brush for text
  QPen textPen(Qt::white);
  textPen.setWidth(1);

  // paint all bodies
  for (Body* b : m_bodies)
  {
    // Create a QColour and brush from the hexadecimal colour code
    QColor colour(b->getColour().c_str());
    QBrush brush(colour);
    painter.setBrush(brush);
    painter.setPen(bodyPen);

    // use a QPointF and radius so the body is centered correctly
    painter.drawEllipse(QPointF(X_CENTER - b->getXPosition() * SCALE,
                                Y_CENTER - b->getYPosition() * SCALE),
                        b->getRadius(), b->getRadius());

    // paint the name of the body (extension for assign 1)
    if (b->getRenderName())
    {
      painter.setPen(textPen);
      painter.drawText(
         QPointF(X_CENTER - b->getXPosition() * SCALE + TXT_X_OFFSET,
            Y_CENTER - b->getYPosition() * SCALE + b->getRadius() + TXT_Y_OFFSET),
         b->getName().c_str());
    }
  }
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space)
  {
    Dialog::paused = !this->paused;
  }
}
