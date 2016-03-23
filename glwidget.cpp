#include "glwidget.h"

#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    pitch(30.0), yaw(0.0), distance(7.0)
{
}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glEnable(GL_CULL_FACE);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setView();
    setLight();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor4f(0.0, 0.5, 0.0, 0.5);
    for(int i = 0; i <= 20; ++i) {
        glBegin(GL_LINES);
            glVertex3f(-5.0+0.5*i, -5.0, 0.0); glVertex3f(-5.0+0.5*i, 5.0, 0.0);
            glVertex3f(-5.0, -5.0+0.5*i, 0.0); glVertex3f(5.0, -5.0+0.5*i, 0.0);
        glEnd();
    }
    glColor4f(0.5, 0.5, 0.0, 0.5);
    glBegin(GL_LINES);
        glVertex3f(robot->getY(), -robot->getX(), 0.0); glVertex3f(robot->getY(), -robot->getX(), robot->getZ()+0.5);
    glEnd();

    glColor4f(0.9, 0.0, 0.0, 0.5);
    robot->displayPath();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    robot->display();

    glFlush();
}

void GLWidget::resizeGL(int _w, int _h)
{
    w = _w; h = _h;

    glViewport(0.0, 0.0, w, h);

    setView();
}

void GLWidget::setPitch(double _pitch)
{
    pitch = _pitch;
}

void GLWidget::setYaw(double _yaw)
{
    yaw = _yaw;
}

void GLWidget::setDistance(double _distance)
{
    distance = _distance;
}

void GLWidget::setView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*w/h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(-distance, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
    glRotatef(pitch, 0.0, -1.0, 0.0);
    glRotatef(yaw, 0.0, 0.0, -1.0);
}

void GLWidget::setLight()
{
    GLfloat lamb[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat ldif[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lpos[] = { -10.0, -10.0, 10.0, 1.0 };

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColor4fv(ldif);
    glBegin(GL_POINTS);
        glVertex4fv(lpos);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldif);
}
