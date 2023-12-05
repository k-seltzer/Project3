#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <iostream>
#include <queue>
#include "HashMap.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(HashMap hashMap, vector<pair<string, int>> keys, QWidget *parent = nullptr);
    ~MainWindow();
    void updateChart();
    void filterCategories(const QString& searchText);
    void onLineEditFromTextChanged(const QString &text);
    void onLineEditToTextChanged(const QString &text);
    void redraw();

private:
    Ui::MainWindow *ui;
    QVector<QBarSet*> sets;
    QChartView *chartView;
    int from;
    int to;
    vector<pair<string, int>> keys;
    HashMap hashMap;
};
#endif // MAINWINDOW_H
