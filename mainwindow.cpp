#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_Do->setEnabled(false);
    ui->pushButton_Undo->setEnabled(false);
    ui->pushButton_Cut->setEnabled(false);
    ui->pushButton_copy->setEnabled(false);
    ui->action_8->setEnabled((false));
    ui->action_9->setEnabled(false);

    ui->action_11->setEnabled(false);
    ui->action_12->setEnabled(false);
    QClipboard* c = QApplication::clipboard();
    if(c->text().isEmpty())
        ui->pushButton_insert->setEnabled((false));
    else
        ui->pushButton_insert->setEnabled((true));
    QSettings s(QCoreApplication::applicationDirPath()+QDir::separator()+"settings.ini",QSettings::IniFormat);
    this->font=qvariant_cast<QFont>(s.value("font",this->font));
    ui->textEdit->setFont(this->font);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Create_clicked()
{
    MainWindow *w = new MainWindow;
    if(!this->next)
    {
        this->next=w;
        w->prev=this;
        w->next=NULL;

    } else {
        w->next=this->next;
        this->next->prev=w;
        w->prev=this;
        this->next=w;
    }
    w->show();
}

void MainWindow::on_pushButton_Save_clicked()
{
    if (changed)
    {
        if(filePath.isEmpty())
        {
            filePath = QFileDialog::getSaveFileName(0, "Open Dialog", "", "*.txt *.doc");
        }
        fileName=filePath.split("/")[filePath.split("/").length()-1];
        if (fileName != "") {
            this->setWindowTitle(fileName+" - Text_edit");
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
                return;
            } else {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                stream.flush();
                file.close();
                saved=true;
                changed=false;
            }
        }
    }
}

void MainWindow::on_pushButton_Do_clicked()
{
    ui->textEdit->redo();
}

void MainWindow::on_pushButton_Undo_clicked()
{
    ui->textEdit->undo();
}

void MainWindow::on_pushButton_copy_clicked()
{

     ui->textEdit->copy();
     QClipboard* c = QApplication::clipboard();
     if(c->text().isEmpty()){
         ui->pushButton_insert->setEnabled((false));
         ui->action_10->setEnabled((false));
     }
     else{
         ui->pushButton_insert->setEnabled((true));
         ui->action_10->setEnabled((true));
     }

}


void MainWindow::on_pushButton_insert_clicked()
{
    ui->textEdit->paste();
}

void MainWindow::on_pushButton_Open_clicked()
{
    if (changed){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, fileName+QString::fromUtf8(" Text_edit"),
        QString::fromUtf8("Хотите сохранить файл перед закрытием?"),
        QMessageBox::Yes |QMessageBox::No | QMessageBox::Cancel,QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            on_pushButton_Save_clicked();

        };
    }

    filePath = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt *.doc");
    fileName=filePath.split("/")[filePath.split("/").length()-1];
        if (filePath !=""){

            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly)){
                QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
            file.close();
            this->setWindowTitle(fileName+" - Text_edit");
        }
     saved=true;
     changed=false;
}

void MainWindow::on_textEdit_textChanged()
{
    changed=true;
    saved=false;
    if (fileName.isEmpty())
        this->setWindowTitle("unnamed* - Text_edit");
    else
        this->setWindowTitle(fileName+"* - Text_edit");
    QClipboard* c = QApplication::clipboard();
    if(c->text().isEmpty()){
        ui->pushButton_insert->setEnabled((false));
        ui->action_10->setEnabled((false));
    }
    else{
        ui->pushButton_insert->setEnabled((true));
        ui->action_10->setEnabled((true));
    }

}

void MainWindow::on_action_5_triggered()
{
    filePath = QFileDialog::getSaveFileName(0, "Open Dialog", "", "*.txt *.doc");
    fileName=filePath.split("/")[filePath.split("/").length()-1];
    if (fileName != "") {
        this->setWindowTitle(fileName+" - Text_edit");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        } else {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
            saved=true;
            changed=false;
        }
    }
}

void MainWindow::on_pushButton_Close_clicked()
{
     this->close();
}

void MainWindow::closeEvent(QCloseEvent *event){
if(!changed)
{
    event->accept();
}
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, fileName+QString::fromUtf8(" Text_edit"),
        QString::fromUtf8("Хотите сохранить файл перед закрытием?"),
        QMessageBox::Yes |QMessageBox::No | QMessageBox::Cancel,QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            on_pushButton_Save_clicked();
            if(saved)
            event->accept();
        else
        event->ignore();

        }
        else if (reply == QMessageBox::No)
             {
                 event->accept();
             }
             else
                  event->ignore();

    }
}


void MainWindow::on_pushButton_Exit_clicked()
{

    if(this->next){
        this->next->prev=NULL;
        this->next->on_pushButton_Exit_clicked();

    }
    if (this->prev){
        this->prev->next=NULL;
        this->prev->on_pushButton_Exit_clicked();
    }
    this->on_pushButton_Close_clicked();

}

void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->pushButton_Do->setEnabled(b);
    ui->action_11->setEnabled(b);
}


void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->pushButton_Undo->setEnabled(b);
    ui->action_12->setEnabled(b);
}

void MainWindow::on_pushButton_font_clicked()
{     
    bool acception;
    QFont initial (QApplication::font());
    font = QFontDialog::getFont(&acception, initial, this);
    if (acception)
    {
    ui->textEdit->setFont(font);
    QSettings s(QCoreApplication::applicationDirPath()+QDir::separator()+"settings.ini",QSettings::IniFormat);
    s.setValue("font", font);
    }


}

void MainWindow::on_action_14_triggered()
{
    QMessageBox::about(this,"О программе","Программное обепечение было разработано Слесаревым Кириллом Б15-501 ");
}

void MainWindow::on_action_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->pushButton_Cut->setEnabled(b);
    ui->pushButton_copy->setEnabled(b);
    ui->action_8->setEnabled(b);
    ui->action_9->setEnabled(b);
}

void MainWindow::on_pushButton_Cut_clicked()
{
    ui->textEdit->cut();
    QClipboard* c = QApplication::clipboard();
    if(c->text().isEmpty()){
        ui->pushButton_insert->setEnabled((false));
        ui->action_10->setEnabled(false);
    }
    else{
        ui->pushButton_insert->setEnabled((true));
        ui->action_10->setEnabled((true));
    }
}
