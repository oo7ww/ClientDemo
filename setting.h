#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();
signals:
    void Gotdata();
private slots:
    void on_setdone_clicked();
    void on_default_2_clicked();

private:
    Ui::setting *ui;
public:
    //initialization & settings
    QString IP;
    QString Port;
    int roomnum;
    int windspeed;
    double tmp;//default
};

#endif // SETTING_H
