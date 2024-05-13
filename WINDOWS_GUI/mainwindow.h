#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum status {
        UPDATE,
        INFO,
        ERROR,
        RESET
    };

    void updateStatus(MainWindow::status s, QString str);

private slots:
    void comboBoxIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QComboBox *secondComboBox;
};
#endif // MAINWINDOW_H
