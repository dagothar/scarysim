#ifndef SCARA_H
#define SCARA_H

#include <QObject>
#include <cmath>
#include <vector>

#include "model.h"

enum SteeringMode { SIMPLE, TARGET };

class Scara : public QObject
{
    Q_OBJECT
public:
    explicit Scara(QObject *parent = 0);

signals:

public slots:
    void go(double dt);
    void displayPath();
    void display();

    double getTh1();
    double getTh2();

    double getX();
    double getY();
    double getZ();

    void setTh1(double th1);
    void setTh2(double th2);
    void setZ(double z);

    void setMode(SteeringMode mode);
    void setTarget(double tx, double ty, double tz);

private slots:
    void kinPr();
    void kinOdwr();
    bool calcSpeed(double vx, double vy, double vz);

private:
    double th1, th2, z;
    double dth1, dth2, dz;
    double posx, posy, posz;
    double tx, ty, tz;

    SteeringMode mode;

    double r1, r2;

    Model baseModel, arm1Model, arm2Model, arm3Model;

    struct PathPoint { double x, y, z; };
    std::vector<PathPoint> path;
};

extern Scara *robot;

#endif // SCARA_H
