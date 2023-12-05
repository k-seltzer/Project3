#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
using namespace std;


MainWindow::MainWindow(HashMap hashy, vector<pair<string, int>> sort, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    keys = sort;
    hashMap = hashy;
    ui->setupUi(this);

    ui->checkBox->setChecked(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    centralWidget()->setAutoFillBackground(true);
    centralWidget()->setPalette(pal);

    QVector<QString> names = {"Total", "Carrier Delays", "Late Aircraft", "NAS Delays", "Security Delays", "Weather Delays"};

    int from = 30;
    int to = 60;


    for (int i = 0; i < 6; i++) {
        QBarSet *set = new QBarSet(names.at(i));
        if (i == 0) {
            for (int j = from; j < to; j++) {
                *set << keys[j].second;
            }
        } else {
            for (int k = from; k < to; k++) {
                *set << hashMap.search(keys[k].first)[i-1];
                cout << hashMap.search(keys[k].first)[i-1];
            }
        }
        sets.append(set);
    }

    QBarSeries *series = new QBarSeries();
    series->append(sets[0]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i = from; i < to; i++) {
        categories << QString::fromStdString(keys[i].first);
    }

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chartView = new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);

    chartView->resize(1000, 700);

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::updateChart);
    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::updateChart);
    connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::updateChart);
    connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &MainWindow::updateChart);
    connect(ui->checkBox_5, &QCheckBox::stateChanged, this, &MainWindow::updateChart);
    connect(ui->checkBox_6, &QCheckBox::stateChanged, this, &MainWindow::updateChart);

    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::onLineEditFromTextChanged);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::onLineEditToTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateChart()
{
    QBarSeries *series = new QBarSeries();

    if (ui->checkBox->isChecked())
        series->append(sets.at(0));

    if (ui->checkBox_2->isChecked())
        series->append(sets.at(1));

    if (ui->checkBox_3->isChecked())
        series->append(sets.at(2));

    if (ui->checkBox_4->isChecked())
        series->append(sets.at(3));

    if (ui->checkBox_5->isChecked())
        series->append(sets.at(4));

    if (ui->checkBox_6->isChecked())
        series->append(sets.at(5));

    chartView->chart()->removeAllSeries();
    chartView->chart()->addSeries(series);
}

void MainWindow::onLineEditFromTextChanged(const QString &text) {
    bool number;
    from = text.toInt(&number);
    if (!number)
        from = to - 30;
    else
        from = text.toInt();
    redraw();
}

void MainWindow::onLineEditToTextChanged(const QString &text) {
    bool number;
    to = text.toInt(&number);
    if (!number)
        to = from + 30;
    else
        to = text.toInt();
    redraw();
}

void MainWindow::redraw() {
    QVector<QString> names = {"Total", "Carrier Delays", "Late Aircraft", "NAS Delays", "Security Delays", "Weather Delays"};
    sets.clear();

    for (int i = 0; i < 6; i++) {
        QBarSet *set = new QBarSet(names.at(i));
        if (i == 0) {
            for (int i = from; i < to; i++) {
                *set << keys[i].second;
            }
        } else {
            for (int i = from; i < to; i++)
                *set << hashMap.search(keys[i].first)[i-1];
        }
        sets.append(set);
    }

    QBarSeries *series = new QBarSeries();
    series->append(sets[0]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;

    from = qMax(0, from);
    to = qMin(100000, to);

    for (int i = from; i < to; i++) {
        categories << QString::fromStdString(keys[i].first);
    }

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chartView->setChart(chart);
}


