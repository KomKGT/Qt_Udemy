#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->btnOne,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnTwo,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnThree,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnFour,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnFive,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnSix,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnSeven,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnEight,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnNine,&QPushButton::clicked,this,&Dialog::append);
    connect(ui->btnZero,&QPushButton::clicked,this,&Dialog::append);

  //connect(ui->ชื่อObjectที่ตั้ง,Signal,this,ฟังก์ชั่นที่เขียนขึ้นมาเองหรือเรียกว่าSlot);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::append()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(!btn)
        return;
    temp.append(btn->text());
    ui->lbNotify->setText("Type : "+temp);

    if(code.isEmpty())  //ถ้าที่เก็บตัวเลขยังไม่มีอะไรใส่เข้ามาก็ยังสามารถกด Save ได้อยู่
    {
        ui->btnSave->setEnabled(true);
        ui->btnVerify->setEnabled(false);
    }
    else                //ถ้าที่เก็บใส่ตัวเลข(ต้องกด Save แล้ว)แล้วให้ล็อกปุ่ม Save แล้วให้สามารถกดปุ่ม Verify ได้
    {
        ui->btnSave->setEnabled(false);
        ui->btnVerify->setEnabled(true);
    }
}


void Dialog::on_btnSave_clicked()   //ถ้ากด Save แล้วให้ล็อกไม่ได้กดได้อีก
{
    code = temp;
    temp.clear();
    ui->btnSave->setEnabled(false);
    ui->btnVerify->setEnabled(true);

    ui->lbNotify->setText("Code save, Please re-enter the code and click verify");

}

void Dialog::on_btnVerify_clicked()
{
    if(code == temp)       //ถ้าสิ่งที่พิมพ์เข้ามาใหม่ตรงกับที่ Code เก็บไว้ก็โชว์ว่า Match กัน
    {
        QMessageBox::information(this,"Code","The codes match");
    }
    else
        QMessageBox::information(this,"Code","The codes do not match");

    temp.clear();
    ui->lbNotify->setText("Enter the code and click verify");
}
