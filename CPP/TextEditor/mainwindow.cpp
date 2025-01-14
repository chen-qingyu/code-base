#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 手动初始化部分UI组件
    initUI();

    // 手动初始化关联槽函数
    initSignalSlots();

    isSaved = true;
    openedFile = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    spinBox = new QSpinBox;
    spinBox->setMinimum(5);
    spinBox->setMaximum(50);
    spinBox->setValue(12);
    ui->textEdit->setFontPointSize(spinBox->value());
    spinBox->setMinimumWidth(50);
    ui->toolBar->addWidget(new QLabel("字体大小"));
    ui->toolBar->addWidget(spinBox);

    ui->toolBar->addSeparator();

    fontComboBox = new QFontComboBox;
    fontComboBox->setMinimumWidth(150);
    ui->toolBar->addWidget(new QLabel("字体"));
    ui->toolBar->addWidget(fontComboBox);

    setCentralWidget(ui->textEdit);
}

void MainWindow::initSignalSlots()
{
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(my_spinBox_valueChanged(int)));
    connect(fontComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(my_fontComboBox_currentIndexChanged(const QString&)));
}

void MainWindow::my_spinBox_valueChanged(int fontSize)
{
    ui->textEdit->setFontPointSize(fontSize);
}

void MainWindow::my_fontComboBox_currentIndexChanged(const QString& font)
{
    ui->textEdit->setFontFamily(font);
}

void MainWindow::on_actionBold_triggered(bool checked)
{
    // 获取选中的文字格式
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    // 有内容可以被复制时启用剪切和复制功能
    ui->actionCut->setEnabled(b);
    ui->actionCopy->setEnabled(b);
    // 有内容可以被粘贴时启用粘贴功能
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    // 获取选中的文字格式
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    // 因为有多种粗体枚举（QFont::Weight），所以和下面两个不一样
    ui->actionBold->setChecked(format.fontWeight() == QFont::Bold);
    ui->actionItalic->setChecked(format.fontItalic());
    ui->actionUnderline->setChecked(format.fontUnderline());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "关于", "富文本编辑器 V1.0\nBy 青羽");
}

void MainWindow::on_actionSave_triggered()
{
    if (openedFile == "")
    {
        openedFile = QFileDialog::getSaveFileName(Q_NULLPTR, QString(), QString(), "*.html");
    }

    QFile file(openedFile);
    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);
    stream << ui->textEdit->toHtml();
    file.close();

    isSaved = true;

    setWindowTitle(openedFile);
}

void MainWindow::on_actionOpen_triggered()
{
    checkSave();

    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, QString(), QString(), "*.html");
    if (fileName != "")
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        QString html = stream.readAll(); // >> only read a word
        file.close();

        setWindowTitle(fileName);

        ui->textEdit->setHtml(html); // will call on_textEdit_textChanged()

        openedFile = fileName;
    }
}

void MainWindow::on_actionNew_triggered()
{
    checkSave();
    ui->textEdit->clear(); // will call on_textEdit_textChanged()

    setWindowTitle("新建文件");

    isSaved = true;

    openedFile = "";
}

void MainWindow::on_actionExit_triggered()
{
    checkSave();

    close();
}

void MainWindow::on_textEdit_textChanged()
{
    if (isSaved)
    {
        setWindowTitle(windowTitle() + " *");
    }
    isSaved = false;
}

void MainWindow::checkSave()
{
    if (!isSaved)
    {
        if (QMessageBox::question(this, "文件已修改", "文件已修改，是否保存？") == QMessageBox::Yes)
        {
            on_actionSave_triggered();
        }
    }
}
