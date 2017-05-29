#ifndef LOCALTMP_H
#define LOCALTMP_H
#include <QTimer>

class LocalTmp: public QObject
{
    Q_OBJECT
public:
    static LocalTmp & getInstance();
    //double TmpGap(double);
signals:
    void TmpUp(double range);
private slots:
    void startTick();
    void TimeOut();
    void killTimer();
private:
    QTimer* activeTimer;
};

#endif // LOCALTMP_H
