#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QStackedWidget>
#include <QListWidget>
#include "pages.h"

class Preferences : public QDialog
{
    Q_OBJECT
public:
    explicit Preferences(QWidget *parent = 0);
    
signals:
    
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private:

    void createIcons();
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    
};

#endif // PREFERENCES_H
