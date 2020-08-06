#include "chartdata.h"
#include "ui_chartdata.h"
#include <QTreeWidgetItem>

ChartData::ChartData(QWidget *parent, QVector<QVector<double>>* data) :
    QDialog(parent),
    ui(new Ui::ChartData)
{
    ui->setupUi(this);
    string = "Displacement\tForce\n";
    this->data = data;
    PopulateTreeWidget();
}

ChartData::~ChartData()
{
    delete ui;
}

void ChartData::AddRoot(QString disp, QString force)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, disp);
    item->setText(1, force);
    string += disp+ "\t" +force;
}

void ChartData::PopulateTreeWidget()
{
    for (int i = 0; i < data->at(0).size(); i++){
        AddRoot(QString::number(data->at(0).at(i)), QString::number(data->at(1).at(i)));
        if (i != data->at(0).size() - 1){
            string += "\n";
        }
    }
    ui->textEdit->setText(string);
}
