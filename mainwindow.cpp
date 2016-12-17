#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QIODevice>
#include <QMap>
#include <QDebug>
QString para;
QStringList paralist;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString word=ui->lineEdit->text();
    ui->textEdit->find(word,QTextDocument::FindWholeWords);
}

void MainWindow::getText(){
    QFile textf(":/test.txt");
    textf.open(QIODevice::ReadOnly);
    QTextStream stream(&textf);
   para=stream.readAll();
    textf.close();

   ui->textEdit->setPlainText(para);
  // QTextCursor textc=ui->textEdit->textCursor();
  // textc.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
}
void MainWindow::getList(){
    QRegExp rx("(\\ |\\,|\\.|\\:|\\t)");
    QString paratroll=para.replace(rx," ");
    //QString paratroll2=para.replace(" +"," ");
    QString parasim=paratroll.simplified();
    paralist=parasim.split(" ");
}

void MainWindow::on_wordCount_clicked()
{
    getList();

    QMap<QString,int> wordmap;
    for (QString entry:paralist){
        int i=wordmap.value(entry);
        if (i==0)wordmap.insert(entry,1);
        else wordmap.insert(entry,i+1);
    }
    ui->textBrowser->setText("Total words: "+ QString::number(paralist.length())+"\n"+"Unique Words: "+QString::number
                             (wordmap.size()));

}
void MainWindow::on_wordStats_clicked()
{
    getList();
    QMap<QString,int> wordmap;
    for (QString entry:paralist){
        int i=wordmap.value(entry);
        if (i==0)wordmap.insert(entry,1);
        else wordmap.insert(entry,i+1);
    }
    QList<int> values=wordmap.values();
    QList<QString> data=wordmap.keys();
    qSort(values.begin(), values.end(), qGreater<int>());
    wordmap.clear();
    QList<int>::Iterator i;
    QList<QString>::Iterator j;
    i=values.begin();
    j=data.begin();
    while(i!=values.end() && j!=data.end()){

         wordmap.insert(*j, *i);
         i++;
         j++;
     }
    QString output;
QMap<QString, int>::iterator it;
    for (it = wordmap.begin(); it != wordmap.end(); ++it) {

        output += QString("%1 : %2\n").arg(it.key()).arg(it.value());
    }
     ui->textBrowser->setText("Most Frequent Word: \n"+ output);
    //qDebug()<<wordmap;
}
/*
void MainWindow::on_textEdit_textChanged()
{
    QFile textf(":/test.txt");
    textf.open(QIODevice::ReadWrite);
    QString input=ui->textEdit->toPlainText();
    QTextStream stream(&textf);
    stream<<input;
    textf.close();
}
*/


