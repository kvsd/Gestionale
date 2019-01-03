#ifndef DOCUMENTIWINDOW_H
#define DOCUMENTIWINDOW_H

#include "libs/customwindow.h"
#include "libs/custommodel.h"
#include "documenti_const.h"
#include "documentiadddialog.h"

#include <QCloseEvent>
#include <QShowEvent>
#include <QSqlRecord>

namespace Ui {
class DocumentiWindow;
}

class DocumentiWindow : public CustomWindow
{
    Q_OBJECT

public:
    explicit DocumentiWindow(QWidget *parent = 0);
    ~DocumentiWindow();
    void loadConfigSettings();
    void saveConfigSettings();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

private:
    Ui::DocumentiWindow *ui;
    CustomModel *m_docModel;
    QString m_query;

    void initModel();

private slots:
    void addFattura();
    void removeRecord();
};

#endif // DOCUMENTIWINDOW_H
