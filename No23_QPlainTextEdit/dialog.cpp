#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowContextHelpButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    /*สร้างปุ่ม*/
    QPushButton *btnCopy = new QPushButton("Copy",this);
    QPushButton *btnCut = new QPushButton("Cut",this);
    QPushButton *btnPaste = new QPushButton("Paste",this);
    QPushButton *btnUndo = new QPushButton("Undo",this);
    QPushButton *btnRedo = new QPushButton("Redo",this);
    /*สร้างปุ่มแต่เนื่องจาก Run แล้วมันทับกันเลยต้องมีโค้ดด้านล่าง*/

    /*ทำให้ปุ่มเรียง*/
    ui->buttonBox->addButton(btnCopy,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnCut,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnPaste,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnUndo,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnRedo,QDialogButtonBox::ActionRole);
    /*ทำให้ปุ่มเรียง*/

    connect(btnCopy,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::copy); //ตรง ui->plainTextEdit ที่ไม่ใช้ this น่าจะเพราะ slot QPlainTextEdit::copy ฟังชัน มันไม่ได้เขียนในหน้านี้
    connect(btnCut,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::cut);
    connect(btnPaste,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::paste);
    connect(btnUndo,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::undo);
    connect(btnRedo,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::redo);

    qDebug()<<m_save; //check m_save

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_plainTextEdit_textChanged()
{
    m_save = false;         //ถ้ามีการเขียนใน plainTextEdit  ปุ๊บ m_save จะเป็น false (ไว้check ว่าเซฟยัง)
    qDebug() << m_save;     //check m_save
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text().contains("Open"))
    {
        load();
        return;
    }
    if(button->text().contains("Save"))
    {
        save();

        return;
    }
}

void Dialog::load()
{
    ui->plainTextEdit->clear();
    QFile file("file.txt");
    if(!file.exists())
        return;
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }
    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());

    file.close();
    m_save = true;
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
    m_save = true;

    QMessageBox::information(this,"Saved","We saved the file");
}

void Dialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}
