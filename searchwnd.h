#ifndef SEARCHWND_H
#define SEARCHWND_H

#include <QWidget>


class QLineEdit;
class QPushButton;
class QTreeView;
class QTabWidget;
class SearchWnd : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWnd(QWidget *parent = 0);
    void CreateNewSearchTab();

signals:
    
public slots:
    void OnSearch();

private:

    void Connect();

    QLineEdit *searchTermBox;
    QPushButton* searchBtn;
    QTreeView *searchResultList;
    QTabWidget *searchTab;
};

#endif // SEARCHWND_H
