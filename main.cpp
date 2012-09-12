#include "cangoteDlg.h"
#include <QApplication>

#include "cangote.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    theApp = new Cangote();
    return a.exec();
}
