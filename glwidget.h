#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "scara.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

signals:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public slots:
    void setPitch(double pitch);
    void setYaw(double yaw);
    void setDistance(double distance);

private:
    void setView();
    void setLight();

    int w, h;
    double pitch, yaw, distance;
};

#endif // GLWIDGET_H
