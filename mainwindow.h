#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "springdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Q_INVOKABLE void callDataWindow();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void SetUpQMLContext();
    void SetUpSlider();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    SpringData springs;
    void UpdateListView();
};
#endif // MAINWINDOW_H
