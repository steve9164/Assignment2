#ifndef LISTOBJECTS_H
#define LISTOBJECTS_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <vector>
#include "cluster.h"

namespace Ui {
class ListObjects;
}

class ListObjects : public QDialog
{
    Q_OBJECT

public:
    explicit ListObjects(QWidget *parent = 0);
    ~ListObjects();


protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ListObjects *ui;
    std::vector<QTreeWidgetItem*> m_treeWidgetItems;

    void addObjects(QTreeWidgetItem* parent, Cluster* object);
};

#endif // LISTOBJECTS_H
