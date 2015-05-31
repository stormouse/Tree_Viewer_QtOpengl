#include "treeviewwidget.h"
#include "ui_treeviewwidget.h"

#include <gl/GLU.h>

TreeViewWidget::TreeViewWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::TreeViewWidget)
{
    ui->setupUi(this);
    treeCount = 0;
    img = NULL;
}

TreeViewWidget::~TreeViewWidget()
{
    delete ui;
}

void TreeViewWidget::AddTree(const TreeInfo &info)
{
    Object *obj = new Object();
    QString tname = "TREE" + QString::number(treeCount++);
    if(obj->Load(info))
    {
        obj->setName(tname);
        objectFactory.AddObject(obj);
    }
    else
    {
        // failed to add model;
    }
}

void TreeViewWidget::RemoveTree(const QString &name)
{
    objectFactory.RemoveObject(name);
}

void TreeViewWidget::SelectTree(const QString &name)
{
    Object *obj = objectFactory.FindObjectByName(name);
    if(obj->isSelected())
    {
        for(int i=0;i<selectedList.size();i++)
        {
            if(selectedList.at(i)->Name() == name)
            {
                selectedList.removeAt(i);
                break;
            }
        }
        obj->ToggleSelected(false);
    }
    else
    {
        obj->ToggleSelected(true);
        selectedList.append(obj);
    }
}

void TreeViewWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,640,480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    LoadBGImage("bg1.jpg");
    AddTree(TreeInfo("perfect","hehuan.obj"));
}

void TreeViewWidget::paintGL()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /* draw background image */
    if(bgTexId != 0)
    {   // has bg image
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bgTexId);
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-bgWidthProj, -bgHeightProj, -z_back+0.01);

            glTexCoord2d(1.0, 0.0);
            glVertex3d(bgWidthProj, -bgHeightProj, -z_back+0.01);

            glTexCoord2d(1.0, 1.0);
            glVertex3d(bgWidthProj, bgHeightProj, -z_back+0.01);

            glTexCoord2d(0.0, 1.0);
            glVertex3d(-bgWidthProj, bgHeightProj, -z_back+0.01);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    /* draw objects */
    QMap<QString, Object*>::const_iterator it;
    const QMap<QString, Object*> *list = objectFactory.Factory();
    for(it = list->begin(); it!=list->end(); it++)
    {
        it.value()->Draw(0);
    }
}


void TreeViewWidget::resizeGL(int width, int height)
{
    this->width = width;
    this->height = height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, (float)width/(float)height, z_front, z_back);

    ratio = (float)width/(float)height;

    bgHeightProj = tany * z_back;
    bgWidthProj = bgHeightProj * ratio;

    kx = tany * 2 / (double)height;
    ky = tany * 2 / (double)height;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TreeViewWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Z)
    {
        TreeInfo info("perfect", "try.obj");
        AddTree(info);
    }

    switch(e->key())
    {
    case Qt::Key_Left:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Translate(QVector3D(-0.5, 0.0, 0.0));
        break;
    case Qt::Key_Right:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Translate(QVector3D(0.5, 0.0, 0.0));
        break;
    case Qt::Key_Up:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Translate(QVector3D(0.0, 0.0, -0.5));
        break;
    case Qt::Key_Down:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Translate(QVector3D(0.0, 0.0, 0.5));
        break;
    case Qt::Key_R:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Rotate(15, QVector3D(0.0, 1.0, 0.0));
        break;
    case Qt::Key_E:
        for(int i=0;i<selectedList.size();i++)
            selectedList[i]->Rotate(15, QVector3D(1.0, 0.0, 0.0));
        break;

    case Qt::Key_Control:
        groupSelecting = true; break;

    case Qt::Key_Delete:
        for(int i=0;i<selectedList.size();i++)
        {
            RemoveTree(selectedList[i]->Name());
        }
        selectedList.clear();
        break;
    }

    update();
}

void TreeViewWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Control:
        groupSelecting = false; break;
    }
}

void TreeViewWidget::mousePressEvent(QMouseEvent *e)
{
    QVector3D ori(0,0,0);
    double x = e->x() - width/2;
    double y = height/2 - e->y();

    QVector3D dir(kx*x, ky*y, -1);

    QMap<QString, Object*>::const_iterator it;
    Object *most_front = NULL;
    for(it = objectFactory.Factory()->begin(); it != objectFactory.Factory()->end(); ++it)
    {
        if(it.value()->Bounding()->Intersect(it.value()->ModelViewMatrix(), ori, dir))
        {
            if(most_front == NULL || most_front->Position().z() < it.value()->Position().z())
                most_front = it.value();
        }
        else
        {
            if(!groupSelecting && it.value()->isSelected())
            {
                for(int i=0;i<selectedList.size();i++)
                    if(selectedList[i] == it.value())
                        selectedList.removeAt(i);
            }
            it.value()->ToggleSelected(false);
        }
    }
    if(most_front != NULL)
    {
        if(!most_front->isSelected())
        {
            if(groupSelecting)
            {
                most_front->ToggleSelected(true);
                selectedList.append(most_front);
            }
            else
            {
                for(int i=0;i<selectedList.size();i++)
                {
                    selectedList[i]->ToggleSelected(false);
                }
                selectedList.clear();
                selectedList.append(most_front);
                most_front->ToggleSelected(true);
            }
        }
        else
        {
            if(groupSelecting)
            {
                for(int i=0;i<selectedList.size();i++)
                {
                    if(selectedList[i] == most_front)
                        selectedList.removeAt(i);
                }
                most_front->ToggleSelected(false);
            }
        }
    }

    update();
}

void TreeViewWidget::LoadBGImage(const QString &filepath)
{
    QImage *buf = new QImage();
    if(buf->load(filepath))
    {
        if(img != NULL)delete img;
        img = new QImage(QGLWidget::convertToGLFormat(*buf));
        fitForBGImage();

        if(bgTexId == 0)
            glGenTextures(1, &bgTexId);

        glBindTexture(GL_TEXTURE_2D, bgTexId);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, img->width(), img->height(), 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, img->bits());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    else delete buf;
}

void TreeViewWidget::fitForBGImage()
{
    int w = img->width();
    int h = img->height();

    while(w>1366 || h>768)
    {
        w/=2;
        h/=2;
    }
    resizeGL(w,h);
}
