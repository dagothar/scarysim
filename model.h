#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QGLWidget>
#include <string>

typedef struct {
    std::string name;

    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];

    GLfloat shininess;
} Material;

typedef struct {
    GLfloat x[3];
} Vertex;

typedef struct {
    int normal;
    int vertex[3];

    int material;
} Face;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

signals:

public slots:
    void load(const char *filename);
    void display();

private:
    std::string matfile;

    std::vector<Material> materials;
    std::vector<Vertex> vertex;
    std::vector<Vertex> normals;
    std::vector<Face> faces;

    void load_materials();
};

#endif // MODEL_H
