#ifndef CANGOTEDLG_H
#define CANGOTEDLG_H

#include <QMainWindow>
#include <QSystemTrayIcon>

struct GNUnetManager;



//Opaque definitions
class NetworkWnd;
class TransferWnd;
class SearchWnd;

namespace Ui {
class CangoteDlg;
}

class CangoteDlg : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CangoteDlg(QWidget *parent = 0);
    ~CangoteDlg();

    void Connect();

    //Dialogs
    NetworkWnd* networkWnd;
    TransferWnd* transferWnd;
    SearchWnd* searchWnd;
private slots:
    void on_actionSettings_triggered();
    void on_trayAction( QSystemTrayIcon::ActivationReason reason );

    void on_actionNetwork_triggered();

    void on_actionTransfer_triggered();

    void on_actionSearch_triggered();

private:
    Ui::CangoteDlg *ui;





    void InitDialogs();

    //Tray
    QSystemTrayIcon * m_trayIcon;

    void createTrayIcon();


};

#endif // CANGOTEDLG_H
