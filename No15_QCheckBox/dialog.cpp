#include "dialog.h"
#include "ui_dialog.h"
#include <QObject>
//#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOK_clicked()
{
    QString toppings;
    QObjectList boxes = this->children();           //พวก children คือพวกที่อยู่ภายใต้ QDialog
    foreach(QObject* obj,boxes)
    {
        if(obj->inherits("QCheckBox"))              //เจาะจงไปที่ QCheckBox ที่เป็น Children
        {
            QCheckBox* box = qobject_cast<QCheckBox*>(obj);
            if(box->isChecked())                    //ถ้าถูกติ๊กให้เข้าเงื่อนไขนี้
                toppings += box->text()+ "\r\n";    //เก็บค่าที่เลือกใน Toppings
        }
    }
    QMessageBox::information(this,"Toppings","Topping include\r\n"+ toppings);  //Show information Dialog

    accept();
}
