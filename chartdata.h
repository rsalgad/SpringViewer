#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QDialog>

namespace Ui {
class ChartData;
}

class ChartData : public QDialog
{
    Q_OBJECT

public:
    explicit ChartData(QWidget *parent = nullptr, QVector<QVector<double>>* data = nullptr);
    ~ChartData();
    void AddRoot(QString disp, QString force);
    void PopulateTreeWidget();

private:
    Ui::ChartData *ui;
    QString string;
    QVector<QVector<double>> *data;
};

#endif // CHARTDATA_H
