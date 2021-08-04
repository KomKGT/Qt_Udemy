#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->chkEnabled->setChecked(ui->txtTest->isEnabled()); //นำค่า isEnabled ของ LineEdit ที่ชื่อ txtTest มาใส่ใน Checkbox ถ้า Enable จะมีเครื่องหมายถูก
    ui->chkReadOnly->setChecked(ui->txtTest->isReadOnly()); //นำค่า ReadOnly ของ LineEdit ที่ชื่อ txtTest มาใส่ใน Checkbox ถ้า Enable จะมีเครื่องหมายถูก
    ui->chkClear->setChecked(ui->txtTest->isClearButtonEnabled()); //นำค่า isClearButtonEnabled ของ LineEdit ที่ชื่อ txtTest มาใส่ใน Checkbox ถ้า Enable จะมีเครื่องหมายถูก

    QMetaEnum metaenum = QMetaEnum::fromType<QLineEdit::EchoMode>();
    for(int i = 0;i<metaenum.keyCount();i++)  //เอาค่า Mode ที่เป็นตัวเลือกของ LineEdit มาใส่ใน ComboBox ทั้งหมด
    {
        ui->cmbEcho->addItem(metaenum.valueToKey(i),metaenum.value(i));
        qDebug() << metaenum.valueToKey(i) << metaenum.value(i); //ทดลองดู valueToKey return เป็น char ,value return เป็น  int
    }
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_cmbEcho_currentIndexChanged(int index)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QLineEdit::EchoMode>();
    int value = metaenum.keyToValue(ui->cmbEcho->currentText().toLocal8Bit().data());
    qDebug() << value; //ลอง Check ดูว่ามีอะไรออกมา
    QLineEdit::EchoMode mode = static_cast<QLineEdit::EchoMode>(value);
    ui->txtTest->setEchoMode(mode); //ให้ช่อง txtTest มี Mode ตามที่เลือกใน ComboBox
}

void Dialog::on_txtDefault_textChanged(const QString &arg1) //นำค่าที่ User พิมพ์ช่อง txtDefault ไปใส่ในช่อง txtTest
{
    ui->txtTest->setText(arg1);
}

void Dialog::on_chkEnabled_toggled(bool checked) //bool checked รับค่ามาจาก line edit ที่ชื่อ txtTest ซึ่งมันมีตัวเลือก Enable ซึ่งมัน enable ตั้งแต่แรกแล้ว
{
    ui->txtTest->setEnabled(checked);
}

void Dialog::on_chkReadOnly_toggled(bool checked) //bool checked รับค่ามาจาก line edit ที่ชื่อ txtTest ซึ่งมันมีตัวเลือก ReadOnly แต่มัน unenable ตั้งแต่แรกแล้ว
{
    ui->txtTest->setReadOnly(checked);
}

void Dialog::on_chkClear_toggled(bool checked) //bool checked รับค่ามาจาก line edit ที่ชื่อ txtTest ซึ่งมันมีตัวเลือก Clear แต่มัน unenable ตั้งแต่แรกแล้ว
{
    ui->txtTest->setClearButtonEnabled(checked);
}

void Dialog::on_buttonBox_accepted() //ถ้ากดปุ่ม OK ก็ให้โชว์ MessageBox ขึ้นมา
{
    QMessageBox::information(this,"Entered","You Entered " + ui->txtTest->text());
    accept();
}
