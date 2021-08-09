#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPushButton *btnAccept = new QPushButton(QIcon(":/dialog/images/accept.png"),"Accept",this); //วิธีสร้างปุ่มและใส่ภาพของปุ่ม dialog วิธี1
    QPushButton *btnReject = new QPushButton("Reject",this); //วิธี2 สร้างปุ่ม
    btnReject->setIcon(QIcon(":/dialog/images/cancel.png")); //วิธี 2 เพิ่มรูป

    ui->buttonBox->addButton(btnAccept,QDialogButtonBox::ButtonRole::AcceptRole);//เพิ่มปุ่มใน UI
    ui->buttonBox->addButton(btnReject,QDialogButtonBox::ButtonRole::RejectRole);//เพิ่มปุ่มใน UI

    connect(btnAccept,&QPushButton::clicked,this,&Dialog::accceptMe);//สร้าง signal&slot
    connect(btnReject,&QPushButton::clicked,this,&QDialog::reject);

    load();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnNew_clicked()
{
    ui->plainTextEdit->clear();

}

void Dialog::on_btnOpen_clicked()
{
    load();
}

void Dialog::on_btnSave_clicked()
{
    save();
    QMessageBox::information(this,"Saved","Your changes has been saved");
}

void Dialog::on_plainTextEdit_textChanged()
{
    m_saved = false;
}

void Dialog::accceptMe()
{
    save();
    accept();
}

void Dialog::load()
{
    QFile file("file.txt");
    if(!file.exists())
    {
        return;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }
    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    m_saved = true;
}

void Dialog::save()
{
    QFile file("file.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }
    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();
    file.close();

    m_saved = true;
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if(!m_saved)
    {
        QMessageBox::StandardButton btn = QMessageBox::question(this,"Save File!","Your file has change would you like to save it?");
        if(btn == QMessageBox::Yes)
            save();

    }
    event->accept();
}
