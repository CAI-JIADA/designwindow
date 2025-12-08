#include "mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
//#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow() {}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        tr("儲存檔案"), 
        "", 
        tr("文字檔案 (*.txt)"));
    
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("錯誤"), tr("無法儲存檔案"));
        return;
    }
    
    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, 
        tr("開啟檔案"), 
        "", 
        tr("文字檔案 (*.txt)"));
    
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("錯誤"), tr("無法開啟檔案"));
        return;
    }
    
    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();
}

