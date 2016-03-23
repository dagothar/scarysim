#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <ctime>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void go();

    void on_verticalSliderPitch_valueChanged(int value);

    void on_horizontalSliderYaw_valueChanged(int value);

    void on_horizontalSliderTh1_valueChanged(int value);

    void on_horizontalSliderTh2_valueChanged(int value);

    void on_horizontalSliderZ_valueChanged(int value);

    void on_commandLinkButtonGo_clicked();

    void on_radioButtonSimple_clicked();

    void on_radioButtonTarget_clicked();

private:
    Ui::MainWindow *ui;

    QTimer tmr;
    double t, dt;
    clock_t clk;

    bool mode;
};

#endif // MAINWINDOW_H
