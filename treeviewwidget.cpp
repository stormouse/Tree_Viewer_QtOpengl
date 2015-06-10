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

void TreeViewWidget::AddTree(const TreeInfo &info, double x, double y)
{
    if(x<0) x = width/2;
    if(y<0) y = height/2;
    Object *obj = new Object();
    QString tname = "TREE" + QString::number(treeCount++);
    if(obj->Load(info))
    {
        obj->setName(tname);
        obj->SetPosition(QVector3D(50*kx*(x - width/2), 50*ky*(y - height/2), -50.0));
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
	//LoadBGImage("bg2.jpg");
    AddTree(TreeInfo("first","try.obj"));
	AddTree(TreeInfo("second", "try.obj"), 250, 100);
	AddTree(TreeInfo("third", "try.obj"), 500, 100);

	//this->setFocusPolicy(Qt::StrongFocus);
	
	//TreeFile projetFile;
	//projetFile.ReadXMLFile("testxml.xml", &objectFactory, LoadBGImage);
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
		for (int i = 0; i<selectedList.size(); i++)
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
	case Qt::Key_G:
		LoadBGImage("bg2.jpg");
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

    case Qt::Key_X:
        /*debug*/
        ClearAllTrees();
        /*debug*/
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

void TreeViewWidget::mouseMoveEvent(QMouseEvent *e)
{
    double dx = e->x() - mousepos[0];
    double dy = e->y() - mousepos[1];

    mousepos[0] = e->x();
    mousepos[1] = e->y();

    for(int i = 0;i<selectedList.length();i++)
    {
        selectedList[i]->Translate2D(QVector2D(dx, dy), -kx, ky);
    }

    update();
}

void TreeViewWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mousedown = false;
}

void TreeViewWidget::ClearAllTrees()
{
    QVector<QString> list;
    selectedList.clear();
    QMap<QString, Object*>::const_iterator it;
    for(it = objectFactory.Factory()->begin(); it!=objectFactory.Factory()->end();it++)
    {
        list<<it.value()->Name();
    }
    for(int i=0;i<list.length();i++)
    {
        objectFactory.RemoveObject(list[i]);
    }
    update();
}

void TreeViewWidget::mousePressEvent(QMouseEvent *e)
{
    mousedown = true;
    mousepos[0] = e->x();
    mousepos[1] = e->y();

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
            if(most_front == NULL || most_front->GetPosition().z() < it.value()->GetPosition().z())
                most_front = it.value();
        }
        else
        {
            if(!groupSelecting && it.value()->isSelected())
            {
                for(int i=0;i<selectedList.size();i++)
                    if(selectedList[i] == it.value())
                        selectedList.removeAt(i);
                it.value()->ToggleSelected(false);
            }

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
		int width = size().width();
		int height = size().height();
		int img_width = img->width();
		int img_height = img->height();
		if (height*img_width > width*img_height)
			height = width*img_height / img_width;
		else
			width = height*img_width / img_height;
		resize(width, height);

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
