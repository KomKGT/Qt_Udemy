#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
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
    QString icecream = getOption(ui->grpIcecream);  //นำค่าที่ Return มาจาก fn getOption มาเก็บ
    QString toppings = getOption(ui->grpTopping);   //นำค่าที่ Return มาจาก fn getOption มาเก็บ
    QString syrup = getOption(ui->grpSyrup);        //นำค่าที่ Return มาจาก fn getOption มาเก็บ
    QString size = getOption(ui->grpSize);          //นำค่าที่ Return มาจาก fn getOption มาเก็บ

    QString order;
    order += "Order :\r\n";
    order += "Size : "+ size +"\r\n";
    order += "Flavor : "+ icecream +"\r\n";
    order += "Toppings : "+ toppings +"\r\n";
    order += "Syrup : "+ syrup +"\r\n";

    QMessageBox::information(this,"Order",order);
    accept();
}

void Dialog::on_btnCancle_clicked()
{
    QMessageBox::critical(this,"What!!","Youdo not want Itim");
    reject();
}

QString Dialog::getOption(QObject *obj)
{
    QString value = "None";
    QList<QRadioButton*> lst = obj->findChildren<QRadioButton*>(QString(),Qt::FindDirectChildrenOnly);

    foreach(QRadioButton* rdo,lst)  //วนซ้ำตัวที่มี RadioBox ทุกที่ เหมือนจะถูกเก็บเป็น list หรือ Stack อะ
    {
        if(rdo->isChecked())
        {
            value = rdo->text();    //ถ้า RadioBox ถูกติ๊กให้เก็บไว้ที่ value
            break;
        }
    }
    return value;
}
