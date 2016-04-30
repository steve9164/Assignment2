#ifndef DIALOG_H
#define DIALOG_H

#include <list>
#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

#include "body.h"
#include "config.h"

namespace Ui {
  class Dialog;
}

/*
 * Represents a Qt Dialog
 */
class Dialog : public QDialog
{

  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  virtual ~Dialog();

public slots:
  void nextFrame();

protected:
  void paintEvent(QPaintEvent*);
  void keyPressEvent(QKeyEvent* event);

private:
  Ui::Dialog* ui;
  std::list<Body*> m_bodies;
  Config* m_config;

  // Whether or not the simulation is currently paused
  bool paused;

};

#endif // DIALOG_H
