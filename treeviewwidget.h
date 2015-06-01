#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QVector>
#include <QMap>
#include "objectfactory.h"
#include "object.h"
#include "treeinfo.h"
#include <QMatrix>
#include <math.h>
#include <QImage>

namespace Ui {
class TreeViewWidget;
}

class TreeViewWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit TreeViewWidget(QWidget *parent = 0);
    ~TreeViewWidget();

    void AddTree(const TreeInfo &info, double scrx = -1.0, double scry = -1.0);
    void RemoveTree(const QString &name);
    void SelectTree(const QString &name);

    void Rotate(GLfloat angle, QVector3D ref);
    void Translate(GLfloat dx, GLfloat dy, GLfloat dz);
    void Translate(QVector3D vec);
    void Scale(GLfloat dx, GLfloat dy, GLfloat dz);
    void Scale(GLfloat dr, GLfloat dh);
    void Scale(QVector3D vec);
    void Scale(QVector2D vec_wh);

    void LoadBGImage(const QString &filepath);
protected:
    // override built-in OpenGL functions
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    bool fullscreen;
    void mousePressEvent(QMouseEvent *);
private:

    void fitForBGImage();

    double fovy = 60.0;
    double tany = tan(fovy*3.1415926/360);
    double z_front = 0.1;
    double z_back = 150.0;
    double kx;
    double ky;
    double width, height;
    double ratio;
    double bgWidthProj, bgHeightProj;

    Ui::TreeViewWidget *ui;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;
    ObjectFactory objectFactory;
    QVector<Object*> selectedList;
    int treeCount;
    bool groupSelecting = false;

    QImage *img;
    GLuint bgTexId = 0;
};

#endif // TREEVIEWWIDGET_H
