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

private slots:
    void on_pushButton_clicked();


    void on_wordCount_clicked();

    void on_wordStats_clicked();

  //  void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    void getText();
    void getList();

};

#endif // MAINWINDOW_H
