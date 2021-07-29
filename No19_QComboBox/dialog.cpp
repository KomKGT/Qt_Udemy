#include "dialog.h"
#include "ui_dialog.h"
//#include <QString>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    init();
    load();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_comboBox_currentIndexChanged(int index)
{
    ui->lbSerectItem->setText( QString::number(index) + " = " + ui->comboBox->currentText());
}

void Dialog::on_btnSave_clicked()
{
    QSettings settings("MySoft", "MyApp");
    settings.setValue("settings", ui->comboBox->currentIndex());

    QMessageBox::information(this,"Saved","Selection saved, please close and re-open the application");
}

void Dialog::init()
{
    ui->comboBox->clear();

    for(int i = 0;i<10;i++)
    {
        ui->comboBox->addItem("Item number "+QString::number(i)); //addItem (เพิ่มตัวเลือกใน ComboBox)กับ addItems ต่างกัน
    }
}

void Dialog::load()
{
    QSettings settings("MySoft", "MyApp");        //ถ้าเป็นwindow ต้องใช้ QSettings settings("MySoft", "MyApp"); ไม่งั้นโปรแกรมจะไม่จำ combobox ล่าสุด
    QVariant value = settings.value("settings",0);  //เอาเป็นว่าเป็นตัวเก็บ combobox ที่ตั้งไว้ก่อนหน้านี้

    bool ok;
    int index = value.toInt(&ok);  //แปลงเป็น int
    qDebug() << index; //ไว้ check index

    if(!ok)  //ถ้ามีปัญหาให้โชว์
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection!");
        return;
    }

    if(index < ui->comboBox->count()) //ui->comboBox->count() คือ จำนวนcombobox ทั้งหมดคือ 10 ,index คือเก็บค่า combobox ที่ตั้งไว้ก่อนหน้านี้
    {
        ui->comboBox->setCurrentIndex(index); //ตั้งให้ combobox นั้นเป็นค่า default กรณี run โปรแกรมใหม่
        qDebug() << ui->comboBox->count();   //คือ 10 ไว้ check  ui->comboBox->count();
    }
    else
    {
        ui->comboBox->setCurrentIndex(0); //กรณีมากกว่าคือเมื่อโปรแกรมใช้งานครั้งแรกสุดต้องให้ Default เป็น 0
    }
}
