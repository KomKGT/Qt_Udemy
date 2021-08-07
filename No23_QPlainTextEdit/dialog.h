#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

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
    void on_plainTextEdit_textChanged();

    void on_buttonBox_clicked(QAbstractButton *button);

    void load();
    void save();
private:
    Ui::Dialog *ui;
    bool m_save;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // DIALOG_H
