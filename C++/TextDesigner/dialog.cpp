#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->checkBoxBold, &QCheckBox::clicked, this, &Dialog::setTextFontStyle);
    connect(ui->checkBoxItalic, &QCheckBox::clicked, this, &Dialog::setTextFontStyle);
    connect(ui->checkBoxUnder, &QCheckBox::clicked, this, &Dialog::setTextFontStyle);

    connect(ui->radioButtonRed, &QRadioButton::clicked, this, &Dialog::setTextFontColor);
    connect(ui->radioButtonGreen, &QRadioButton::clicked, this, &Dialog::setTextFontColor);
    connect(ui->radioButtonBlue, &QRadioButton::clicked, this, &Dialog::setTextFontColor);
    connect(ui->radioButtonBlack, &QRadioButton::clicked, this, &Dialog::setTextFontColor);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setTextFontStyle()
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(ui->checkBoxBold->isChecked());
    font.setItalic(ui->checkBoxItalic->isChecked());
    font.setUnderline(ui->checkBoxUnder->isChecked());
    ui->plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QColor color;
    if (ui->radioButtonRed->isChecked())
    {
        color = Qt::red;
    }
    else if (ui->radioButtonGreen->isChecked())
    {
        color = Qt::green;
    }
    else if (ui->radioButtonBlue->isChecked())
    {
        color = Qt::blue;
    }
    else if (ui->radioButtonBlack->isChecked())
    {
        color = Qt::black;
    }
    QPalette pal = ui->plainTextEdit->palette();
    pal.setColor(QPalette::Text, color);
    ui->plainTextEdit->setPalette(pal);
}
