#include "springdata.h"

SpringData::SpringData(QObject *parent) : QObject(parent)
{

}

void SpringData::setSpringData(QVector<QVector<QVector<double> > > vecSprings)
{
    this->vecSprings = vecSprings;
}

void SpringData::setSpringNames(QVector<QString> stringNames)
{
    this->stringNames = stringNames;
}

void SpringData::setTimeData(QVector<double> times)
{
    this->times = times;
}

QVector<double> SpringData::getTimeData()
{
    return this->times;
}

int SpringData::getNumberOfSprings()
{
    return this->stringNames.size();
}

double SpringData::getSpringData(int springIndex, int row, int col)
{
    return this->vecSprings[springIndex][col][row];
}

QString SpringData::getSpringName(int springIndex)
{
    return this->stringNames[springIndex];
}

int SpringData::getNumberOfPoints()
{
    return this->vecSprings[0][0].size();
}

QVector<QVector<double>>* SpringData::getSpringData(int springIndex)
{
    return &this->vecSprings[springIndex];
}

void SpringData::CallUpdateChart(int index)
{
    emit doUpdateChart(index);
}

void SpringData::CallDrawPointChart(int springIndex, int pointIndex)
{
    emit doDrawPointChart(springIndex, pointIndex);
}
