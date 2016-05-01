#include "listobjects.h"
#include "ui_listobjects.h"

#include "debug.h"

#include "simulationfacade.h"

ListObjects::ListObjects(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListObjects)
{
    ui->setupUi(this);
}

ListObjects::~ListObjects()
{
    delete ui;
    /*for (auto p : m_treeWidgetItems)
        delete p;
    */
}

void ListObjects::showEvent(QShowEvent *event)
{
    SimulationFacade* sim = SimulationFacade::getInstance();
    ui->treeWidget->clear();
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromStdString(sim->m_universe->getName())));
    //ui->treeWidget->addTopLevelItem(item);
    addObjects(item, sim->m_universe.get());
}

void ListObjects::addObjects(QTreeWidgetItem* parent, Cluster* object)
{
    DEBUG("Adding cluster: " + object->getName());
    for (std::unique_ptr<ObjectPrototype>& childObject : object->m_objects)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(parent, QStringList(QString::fromStdString(childObject->getName())));
        m_treeWidgetItems.push_back(item); // Keep track of memory
        if (childObject->isCluster())
        {
            addObjects(item, dynamic_cast<Cluster*>(childObject.get()));
        }
    }
}

void ListObjects::on_buttonBox_accepted()
{
    ui->treeWidget->clear();
    for (auto p : m_treeWidgetItems)
        delete p;
    m_treeWidgetItems.clear();
    this->hide();
}
