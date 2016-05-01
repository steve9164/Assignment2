#ifndef DIALOG_H
#define DIALOG_H

#include <list>
#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

#include "simulationfacade.h"
#include "listobjects.h"

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

private slots:
  void on_btnListObjects_clicked();

private:
  Ui::Dialog* ui;
  ListObjects* m_listObjects;

  SimulationFacade* m_sim;

  // Whether or not the simulation is currently paused
  bool paused;

};

#endif // DIALOG_H
