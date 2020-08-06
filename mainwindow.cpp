#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartdata.h"

#include <QQuickWidget>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/qml/QMLChart.qml"));
}

void MainWindow::callDataWindow()
{
    ChartData* window = new ChartData(this, springs.getSpringData(ui->listWidget->currentRow()));
    window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QDir mDir;
    QString filePath = mDir.filePath(QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("CSV (*.csv)")));

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int springCount;
    QString line1 = in.readLine();
    QString line2 = in.readLine();
    QString line3 = in.readLine();
    QStringList list1 = line1.split(";");
    QStringList list2 = line3.split(";");
    springCount = (list2.size() - 1)/2;

    QVector<QString> stringNames;
    for (int i = 0; i < springCount; i++){
        stringNames.append(list1[2 * (1 + i)].trimmed());
    }

    QVector<QVector<QVector<double>>> vecSprings(springCount);
    QVector<QString> stringVec;
    QVector<double> vecTimes;


    stringVec.append(line3);
    int lineCount = 0;
    while (!in.atEnd()) {
        stringVec.append(in.readLine());
        lineCount++;
    }

    for (int j = 0; j < springCount; j++){
        QVector<double> vec(lineCount, 0);
        QVector<double> vec2(lineCount, 0);
        QVector<QVector<double>> vec3;
        vec3.append(vec);
        vec3.append(vec2);
        vecSprings[j] = vec3;
    }

    for (int j = 0; j < stringVec.size(); j++){
        QStringList list = stringVec[j].split(";");
        vecTimes.append(list[0].toDouble());

        for (int i = 1; i < list.size() - 3; i+=2){

            vecSprings[(i-1)/2][0][j] = list[i].toDouble();
            vecSprings[(i-1)/2][1][j] = list[i + 1].toDouble();
        }
    }
    springs.setSpringData(vecSprings);
    springs.setSpringNames(stringNames);
    springs.setTimeData(vecTimes);
    SetUpQMLContext();
    UpdateListView();
    SetUpSlider();
}

void MainWindow::SetUpQMLContext()
{
    ui->quickWidget->rootContext()->setContextProperty("springs", &springs);
    ui->quickWidget->rootContext()->setContextProperty("mainWindow", this);
}

void MainWindow::SetUpSlider()
{
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(springs.getTimeData().size());
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->setValue(1);
    ui->txt_Time->setPlainText(QString::number(springs.getTimeData()[0]));
}

void MainWindow::UpdateListView()
{
    for (int i = 0; i < springs.getNumberOfSprings(); i++){
        ui->listWidget->addItem(springs.getSpringName(i));
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    springs.CallUpdateChart(ui->listWidget->currentRow());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (springs.getNumberOfSprings() != 0) {
        ui->txt_Time->setPlainText(QString::number(springs.getTimeData()[value - 1]));
        if (ui->listWidget->currentRow() != -1){
            springs.CallDrawPointChart(ui->listWidget->currentRow(), value - 1);
        }
    }
}
