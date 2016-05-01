#include "planetary_bodybuilder.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "listobjects.h"

// time step for the simulation (default 10000)
#define TIMESTEP (10000)

// width and height of dialog box
#define DIALOG_WIDTH (600)
#define DIALOG_HEIGHT (600)

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog),
  m_listObjects(new ListObjects(this)),
  m_sim(SimulationFacade::getInstance())
{
  // SimulationFacade reads config and builds the universe

  // Create the dialog
  ui->setupUi(this);
  this->update();
  this->resize(DIALOG_WIDTH, DIALOG_HEIGHT);

  // Use a black background because it's SPAAAAAAAAAAAAAAACE
  //this->setStyleSheet("background-color: #000000;");

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

  m_sim->updateSimulation(TIMESTEP);

  update();
}

Dialog::~Dialog()
{
  DEBUG("Dialog destructor");

  delete ui;
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
  for (auto it = m_sim->bodyBegin(); it != m_sim->bodyEnd(); ++it)
  {
    // Create a QColour and brush from the hexadecimal colour code
    QColor colour(it->getColour().c_str());
    QBrush brush(colour);
    painter.setBrush(brush);
    painter.setPen(bodyPen);

    // use a QPointF and radius so the body is centered correctly
    painter.drawEllipse(QPointF(X_CENTER - it->getXPosition() * SCALE,
                                Y_CENTER - it->getYPosition() * SCALE),
                        it->getRadius(), it->getRadius());

    // paint the name of the body (extension for assign 1)
    if (it->getRenderName())
    {
      painter.setPen(textPen);
      painter.drawText(
         QPointF(X_CENTER - it->getXPosition() * SCALE + TXT_X_OFFSET,
            Y_CENTER - it->getYPosition() * SCALE + it->getRadius() + TXT_Y_OFFSET),
         it->getName().c_str());
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

void Dialog::on_btnListObjects_clicked()
{
    m_listObjects->show();
}
