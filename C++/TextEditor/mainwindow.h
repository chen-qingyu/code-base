#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFontComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBold_triggered(bool checked);
    void on_textEdit_copyAvailable(bool b);
    void on_textEdit_selectionChanged();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_textEdit_textChanged();

    // 自定义槽函数
    void my_spinBox_valueChanged(int fontSize);                    // 改变字体大小
    void my_fontComboBox_currentIndexChanged(const QString& font); // 选择字体

private:
    Ui::MainWindow* ui;

    QSpinBox* spinBox;           // 选择字号
    QFontComboBox* fontComboBox; // 选择字体

    bool isSaved;       // 已保存文件标志
    QString openedFile; // 已打开文件名称

    void initUI();
    void initSignalSlots(); // 手动关联信号与槽
    void checkSave();
};
#endif // MAINWINDOW_H
