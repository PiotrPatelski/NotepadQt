#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path_ = ""; //czyścimy ścieżkę pliku
    ui->textEdit->setText(""); //czyścimy text
}

void MainWindow::on_actionOpen_triggered()
{
    //ZCZYTYWANIE TEKSTU Z PLIKU
    QString file_name =QFileDialog::getOpenFileName(this,"Open the file");
    //zmienna z nazwą pliku
    QFile file(file_name);
    file_path_=file_name;
    //zapisujemy nazwę pliku globalnie do użycia w Save
    if(!file.open(QFile::ReadOnly|QFile::Text)){
      QMessageBox::warning(this, "..","file not opened");
      return;
    }
    //sprawdzanie czy plik otwarty
    QTextStream in(&file);
    //tworzymy strumień tekstu do pliku
    QString text = in.readAll();
    //zczytujemy string z strumienia
    ui->textEdit->setText(text);
    //ustawiamy text w edytorze na string ze strumienia
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    //ZAPISANIE PLIKU
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
      QMessageBox::warning(this, "..","file not opened");
      return;
    }
    //sprawdzanie czy plik otwarty
    QTextStream out(&file);
    //tworzymy strumień tekstu do pliku
    QString text = ui->textEdit->toPlainText();
    //zczytujemy string z edytora tekstu
    out << text;
    //wstawiamy text z edytora do strumienia
    out.flush();
    //spłukujemy strumień
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    //ZAPISANIE PLIKU
    QString file_name =QFileDialog::getSaveFileName(this,"Open the file");
    //zmienna z nazwą pliku
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
      QMessageBox::warning(this, "..","file not opened");
      return;
    }
    //sprawdzanie czy plik otwarty
    QTextStream out(&file);
    //tworzymy strumień tekstu do pliku
    QString text = ui->textEdit->toPlainText();
    //zczytujemy string z edytora tekstu
    out << text;
    //wstawiamy text z edytora do strumienia
    out.flush();
    //spłukujemy strumień
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
    //jeśli nic nie skopiujemy to wklei się "->textEdit"
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString about_text;
    about_text = "Author: Piotr Patelski\n";
    about_text+= "Version: 0.1\n";
    about_text+= "Date: 18.07.2020\n";
    QMessageBox::about(this,"About PatelNotepad",about_text);
}
