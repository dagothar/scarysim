#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dt(0.0)
{
    ui->setupUi(this);

    connect(&tmr, SIGNAL(timeout()), this, SLOT(go()));
    tmr.setInterval(0);
    tmr.start();

    robot = new Scara(this);

    clk = clock();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go()
{
    dt = 1.0 * (clock() - clk) / CLOCKS_PER_SEC;
    clk = clock();
    t += dt;

    robot->go(dt);

    bool mode = ui->radioButtonTarget->isChecked();

    QString text;

    text.sprintf("%.3f", robot->getTh1());
    ui->labelTh1->setText(text);

    text.sprintf("%.3f", robot->getTh2());
    ui->labelTh2->setText(text);

    text.sprintf("%.3f", robot->getZ());
    ui->labelThZ->setText(text);

    text.sprintf("%.3f", robot->getY());
    ui->labelY->setText(text);

    text.sprintf("%.3f", robot->getX());
    ui->labelX->setText(text);

    text.sprintf("%.3f", robot->getY());
    ui->labelY->setText(text);

    text.sprintf("%.3f", robot->getZ());
    ui->labelZ->setText(text);

    if(mode) {
        ui->horizontalSliderTh1->setValue(robot->getTh1());
        ui->horizontalSliderTh2->setValue(robot->getTh2());
        ui->horizontalSliderZ->setValue(100.0*robot->getZ());
    }

    ui->view->updateGL();
}

void MainWindow::on_verticalSliderPitch_valueChanged(int value)
{
    ui->view->setPitch(value);
}

void MainWindow::on_horizontalSliderYaw_valueChanged(int value)
{
    ui->view->setYaw(value);
}

void MainWindow::on_horizontalSliderTh1_valueChanged(int value)
{
    mode = ui->radioButtonTarget->isChecked();

    if(!mode) robot->setTh1(value);
}

void MainWindow::on_horizontalSliderTh2_valueChanged(int value)
{
    mode = ui->radioButtonTarget->isChecked();

    if(!mode) robot->setTh2(value);
}

void MainWindow::on_horizontalSliderZ_valueChanged(int value)
{
    mode = ui->radioButtonTarget->isChecked();

    if(!mode) robot->setZ(0.01 * value);
}

void MainWindow::on_commandLinkButtonGo_clicked()
{
    robot->setTarget(ui->lineEditTx->text().toDouble(), ui->lineEditTy->text().toDouble(), ui->lineEditTz->text().toDouble());
}

void MainWindow::on_radioButtonSimple_clicked()
{
    robot->setMode(SIMPLE);

    ui->groupBoxSimple->setEnabled(true);
    ui->groupBoxTarget->setDisabled(true);
}

void MainWindow::on_radioButtonTarget_clicked()
{
    robot->setMode(TARGET);

    ui->groupBoxSimple->setDisabled(true);
    ui->groupBoxTarget->setEnabled(true);
}
