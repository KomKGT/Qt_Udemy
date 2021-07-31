#include "dialog.h"
#include "ui_dialog.h"
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

void Dialog::init()
{
    ui->comboBox->setEnabled(true);
    ui->buttonBox->addButton("Clear",QDialogButtonBox::ButtonRole::AcceptRole);
    ui->buttonBox->addButton("Remove",QDialogButtonBox::ButtonRole::AcceptRole);
}

void Dialog::load()
{
    QSettings settings("MyCompany","MyApp");

    ui->comboBox->setCurrentText(settings.value("text","").toString());   //นำข้อมูลที่เก็บในการเข้าคีย์ "text" มาใช้ตอน load

    int combosize = settings.beginReadArray("combo");
    for(int i = 0;i<combosize;i++)
    {
        settings.setArrayIndex(i);
        ui->comboBox->addItem(settings.value("item","").toString());
    }
    settings.endArray();

    int listsize = settings.beginReadArray("list");
    for(int i = 0;i<listsize;i++)
    {
        settings.setArrayIndex(i);
        ui->listWidget->addItem(settings.value("item","").toString());
    }
    settings.endArray();
}

void Dialog::save()
{
    QSettings settings("MyCompany","MyApp");
    settings.clear();

    settings.setValue("text",ui->comboBox->currentText());

    settings.beginWriteArray("combo");
    for(int i = 0;i<ui->comboBox->count();i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("item",ui->comboBox->itemText(i));
    }
    settings.endArray();

    settings.beginWriteArray("list");
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("item",ui->listWidget->item(i)->text());
    }
    settings.endArray();
}


void Dialog::on_btnAdd_clicked()
{
    if(ui->comboBox->findText(ui->comboBox->currentText()) < 0) //เหมือนกับว่าถ้าพิมพ์ในช่องแล้วมันจะหาว่าเคยมีอยู่ไหม ถ้าไม่มี(คือ <0) ก็จะเข้า condition นี้
    {
        ui->comboBox->addItem(ui->comboBox->currentText());  //เพิ่มตัวเลือกในถาด combobox
    }
    ui->listWidget->addItem(ui->comboBox->currentText());  //เพิ่มที่พิมพ์ใน combobox ใน list widget
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug() << button->text();
    if(button->text().contains("OK"))
    {
        save();
        accept();
        return;
    }
    if(button->text().contains("Cancel"))
    {
        reject();
        return;
    }
    if(button->text().contains("Clear"))
    {
        ui->comboBox->clear();
        ui->listWidget->clear();
        return;
    }
    if(button->text().contains("Remove"))
    {
        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
        foreach(QListWidgetItem* item,items)
        {
            ui->listWidget->removeItemWidget(item);
            delete item;
        }
    }
}
