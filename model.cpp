#include "model.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include <QFileInfo>

Model::Model(QObject *parent) :
    QObject(parent)
{
}

void replace(std::string &str, const char from, const char to)
{
    std::string::iterator i;
    for(i = str.begin(); i < str.end(); ++i)
        if(*i == from) *i = to;
}

void Model::load(const char *filename)
{
    std::cout << "Loading obj\n";

    //wyczysc
    materials.clear();
    vertex.clear();
    faces.clear();
    normals.clear();

    std::ifstream file(filename);

    if(!file) {
        std::cout << "Obj file not found\n";
        exit(-1);
    }

    std::string s;
    int current_material = -1;

    while(getline(file, s)) {
        std::stringstream sstr;

        replace(s, '/', ' ');
        sstr << s;

        std::string cmd;
        sstr >> cmd;

        if(cmd == "mtllib") {
            sstr >> matfile;

            std::cout << matfile << "\n";

            load_materials();
        }

        if(cmd == "v") {
            Vertex vtx;

            sstr >> vtx.x[0] >> vtx.x[1] >> vtx.x[2];

            //vtx.x[1] *= -1; //odwroc y

            vertex.push_back(vtx);
        }

        if(cmd == "vn") {
            Vertex nrm;

            sstr >> nrm.x[0] >> nrm.x[1] >> nrm.x[2];

            for(int i = 0; i < 3; nrm.x[i++] *= -1);
            nrm.x[0] *= -1; //odwroc normale
            nrm.x[1] *= -1;
            nrm.x[2] *= -1;

            normals.push_back(nrm);
        }

        if(cmd == "f") {
            Face face;

            for(int i = 0; i < 3; ++i) {
                sstr >> face.vertex[i] >> face.normal;
            }

            face.material = current_material;

            faces.push_back(face);
       }

       if(cmd == "usemtl") {
            std::string matname;
            sstr >> matname;

            // znajdz numer materialu
            int i = 0;
            for(; i < materials.size(); ++i) {
                if(matname == materials[i].name) break;
            }

            current_material = i;
        }
    }

    file.close();

    std::cout << "Obj loaded\n";
}

void Model::load_materials()
{
    std::cout << "Loading materials: " << matfile.c_str() << "\n";

    std::ifstream file(matfile.c_str());

    if(!file) {
        std::cout << "Mat file not found\n";
        exit(-1);
    }

    std::string line;
    Material nmat;

    while(getline(file, line)) {
        std::stringstream sstr;
        sstr << line;

        std::string cmd;
        sstr >> cmd;

        if(cmd == "newmtl") {
            sstr >> nmat.name;
        }

        if(cmd == "Ns") {
            sstr >> nmat.shininess;
        }

        if(cmd == "Ka") {
            sstr >> nmat.ambient[0] >> nmat.ambient[1] >> nmat.ambient[2];
        }

        if(cmd == "Kd") {
            sstr >> nmat.diffuse[0] >> nmat.diffuse[1] >> nmat.diffuse[2];
        }

        if(cmd == "Ks") {
            sstr >> nmat.specular[0] >> nmat.specular[1] >> nmat.specular[2];
        }

        if(cmd == "d") {
            float alpha;
            sstr >> alpha;
            nmat.ambient[3] = alpha;
            nmat.diffuse[3] = alpha;
            nmat.specular[3] = alpha;
        }

        // illum bo akurat program konczy blok tym i nie ma oprocz tego zadnego znaczenia
        if(cmd == "illum") {
            materials.push_back(nmat);
        }
    }

    file.close();

    std::cout << "Materials loaded\n";
}

void Model::display()
{
    //std::cout << "display()\n";

    GLfloat emiss[4] = { 0.0, 0.0, 0.0, 0.0 };

    glBegin(GL_TRIANGLES);

    int current_material = -1;

    std::vector<Face>::iterator i;
    for(i = faces.begin(); i < faces.end(); ++i) {
        // jaki material?
        int mat = (*i).material;

        if(current_material != mat) { // ustaw nowe parametry tylko kiedy nastepuje zmiana materialu
            Material m = materials[mat];

            glEnd();
            glMaterialfv(GL_FRONT, GL_AMBIENT, m.diffuse);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, m.diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, m.specular);
            glMaterialfv(GL_FRONT, GL_EMISSION, emiss);
            glMaterialfv(GL_FRONT, GL_SHININESS, &m.shininess);

            current_material = mat;
            glBegin(GL_TRIANGLES);
        }

        int n_normal = (*i).normal - 1;

        glNormal3fv(normals[n_normal].x);
        for(int j = 0; j < 3; ++j) {
            int n_vtx = (*i).vertex[j] - 1;
            glVertex3fv(vertex[n_vtx].x);
        }
    }
    glEnd();
}
