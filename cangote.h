#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>



class GNUnetManager;
class CangoteDlg;
class Cangote : public QObject
{
    Q_OBJECT
public:
    explicit Cangote(QObject *parent = 0);
    
signals:
    
public slots:
    

public:
        GNUnetManager* gnunetMgr;

private:
        void Connect();
        CangoteDlg* cangoteDlg;
};

extern Cangote* theApp;

#endif // CANGOTE_H
