#ifndef HELLOGL_H
#define HELLOGL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

class HelloGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit HelloGL(QWidget* parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
};

#endif // HELLOGL_H
