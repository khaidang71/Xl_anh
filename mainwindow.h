#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DisplayImage(QImage &img, QString title);
    
private slots:
    void on_browse_clicked();

    void on_ab_mau_clicked();

    void on_ab_xam_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
