#ifndef SPRINGDATA_H
#define SPRINGDATA_H

#include <QObject>

class SpringData : public QObject
{
    Q_OBJECT
public:
    explicit SpringData(QObject *parent = nullptr);

    void setSpringData(QVector<QVector<QVector<double>>> vecSprings);
    void setSpringNames(QVector<QString> stringNames);
    void setTimeData(QVector<double> times);
    QVector<double> getTimeData();
    int getNumberOfSprings();
    Q_INVOKABLE double getSpringData(int springIndex, int row, int col);
    Q_INVOKABLE QString getSpringName(int springIndex);
    Q_INVOKABLE int getNumberOfPoints();
    QVector<QVector<double>>* getSpringData(int springIndex);
    void CallUpdateChart(int index);
    void CallDrawPointChart(int springIndex, int pointIndex);


signals:
    void doUpdateChart(int index);
    void doDrawPointChart(int springIndex, int pointIndex);

private:
    QVector<QVector<QVector<double>>> vecSprings;
    QVector<QString> stringNames;
    QVector<double> times;

};

#endif // SPRINGDATA_H
