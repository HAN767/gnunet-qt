#include "cangoteDlg.h"
#include "ui_cangoteDlg.h"
#include "preferences.h"
#include "gnunetmanager.h"
#include "cangote.h"

#include "networkwnd.h"
#include "transferwnd.h"
#include "searchwnd.h"
#include <QStringListModel>

CangoteDlg::CangoteDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CangoteDlg)
{
    ui->setupUi(this);

    createTrayIcon();

    InitDialogs();
}

CangoteDlg::~CangoteDlg()
{
    delete ui;
}


void CangoteDlg::Connect()
{
    connect( theApp->gnunetMgr, SIGNAL(PeerAdded(QString)), networkWnd, SLOT(PeerEvent(QString)) );
}



void CangoteDlg::on_actionSettings_triggered()
{
    Preferences dialog;
    dialog.exec();
}

void CangoteDlg::InitDialogs()
{
    networkWnd = new NetworkWnd();
    transferWnd = new TransferWnd();
    searchWnd = new SearchWnd();
    ui->stackedWidget->addWidget(networkWnd);
    ui->stackedWidget->addWidget(searchWnd);
    ui->stackedWidget->addWidget(transferWnd);

    ui->stackedWidget->setCurrentIndex(0);

}


void CangoteDlg::createTrayIcon()
{
   m_trayIcon = new QSystemTrayIcon(QIcon(":/images/config.png"), this);

   connect( m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayAction(QSystemTrayIcon::ActivationReason)) );

   QAction *quit_action = new QAction( "Exit", m_trayIcon );
   connect( quit_action, SIGNAL(triggered()), qApp, SLOT(quit()) );

   QMenu *tray_icon_menu = new QMenu;
   tray_icon_menu->addAction( quit_action );

   m_trayIcon->setContextMenu( tray_icon_menu );

   m_trayIcon->show();
 }

void CangoteDlg::on_trayAction( QSystemTrayIcon::ActivationReason reason )
{
    if( reason )
    {
        if( reason != QSystemTrayIcon::DoubleClick )
        return;
    }

    if( isVisible() )
    {
        hide();
    }
    else
    {
        show();
        raise();
        setFocus();
    }
}



void CangoteDlg::on_actionNetwork_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void CangoteDlg::on_actionSearch_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CangoteDlg::on_actionTransfer_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}
