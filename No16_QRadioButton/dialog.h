#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnOK_clicked();

    void on_btnCancle_clicked();

private:
    Ui::Dialog *ui;

    QString getOption(QObject* obj);
};
#endif // DIALOG_H
