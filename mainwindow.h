#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QCoreApplication>
#include <QAction>
#include<QString>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QCloseEvent>
#include<QClipboard>
#include<QFont>
#include<QFontDialog>
#include<QSettings>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow *next=NULL;
    MainWindow *prev=NULL;
    QFont font;

private slots:
    void closeEvent(QCloseEvent *event);

    void on_pushButton_Create_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Do_clicked();

    void on_pushButton_Undo_clicked();

    void on_pushButton_copy_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_Open_clicked();

    void on_textEdit_textChanged();

    void on_action_5_triggered();

    void on_pushButton_Close_clicked();

    void on_pushButton_Exit_clicked();

    void on_textEdit_redoAvailable(bool b);

    void on_textEdit_undoAvailable(bool b);

    void on_pushButton_font_clicked();

    void on_action_14_triggered();

    void on_action_Qt_triggered();

    void on_textEdit_copyAvailable(bool b);

    void on_pushButton_Cut_clicked();

private:
    bool changed=false;
    bool saved=false;
    QString filePath;
    QString fileName;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
