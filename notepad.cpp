#include "notepad.h"
#include "ui_notepad.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <boost/foreach.hpp>
#include <QFileInfo>
#include <QtSql>

#define Path_to_DB "/Users/kimso/Development/SQLite"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_quitButton_clicked()
{
    qApp->quit();
}

void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
            file.close();
        }
}

void Notepad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void Notepad::on_setButton_clicked()
{
    std::string hello( "Hello, world!" );

    QString tmpStr;

        BOOST_FOREACH( char ch, hello )
        {
            tmpStr.append(ch);
        }


    ui->dLabel->setText(tmpStr);

    QSqlDatabase dbconn=QSqlDatabase::addDatabase("QSQLITE");

    dbconn.setDatabaseName("test.sqlite");

    if(!dbconn.open())
    {
        ui->dLabel->setText("Connection not open");
    }
    QSqlQuery query;
    query.exec("Select * from student");

    QSqlRecord rec = query.record();
    int nameCol = rec.indexOf("name");

    query.next();
    ui->dLabel->setText(query.value(nameCol).toString());
}
