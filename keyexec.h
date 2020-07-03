#ifndef KEYEXEC_H
#define KEYEXEC_H

#include <QWidget>
#include <virtualkey.h>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class keyExec;
}

class keyExec : public VirtualKey
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit keyExec(QWidget *parent = nullptr);
    ~keyExec();

protected:
    void keypressed(bool);
    void upDatePic(QPixmap);
    void keypressedGUI();
    void keyDoubleClickGUI();
    void revertSystemInfo(QVariant,QVariant);
    void createdVirtual();

    QVariant getConfig();
    void SetConfig(QVariant);

    void setEnabledfromFlag();

private slots:
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_pushButton_pressed();
    void printResult(int,QProcess::ExitStatus);

private:
    Ui::keyExec *ui;
    int _choose_flag = 0;
    QString _execPath;
    QString _shellPath;
    QProcess* _Process;
};

#endif // KEYEXEC_H
