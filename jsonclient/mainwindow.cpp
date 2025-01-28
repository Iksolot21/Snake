#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "application.h"
#include <QTableView>
#include "crypter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(Application::getSocket(), &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(Application::getSocket(), &QTcpSocket::disconnected, Application::getSocket(), &QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotReadyRead()
{
    qDebug() << "slotReadyRead() called";
    QTcpSocket *socket = Application::getSocket();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if (nextBlockSize == 0)
            {
                if (socket->bytesAvailable()<2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize =0;
            ui->textBrowser->append(time.toString() + " " + str);
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }

}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked() called";

    Application::getSocket()->connectToHost("127.0.0.1",23232);


    if(Application::getSocket()->waitForConnected(1000))
    {
        qDebug() << "Connected to server";
    }
    else
    {
        qDebug() << "Failed to connect to server:" << Application::getSocket()->errorString();
    }
}
void MainWindow::SendToServer(QString queryStr)
{
    if (!Application::getSocket()->isOpen()) {
        qDebug() << "Socket is not open!";
        return;
    }
    // Шифрование строки запроса
    QString encryptedQuery = Crypter::cryptString(queryStr);
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << QTime::currentTime() << encryptedQuery;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    qint64 bytesWritten = Application::getSocket()->write(Data);
    if (bytesWritten == -1) {
        qDebug() << "Error writing to socket:" << Application::getSocket()->errorString();
    } else {
        qDebug() << "Data sent successfully!";
    }

    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_3_clicked()
{
    QString echoString = "ECHO " + ui->lineEdit->text();
    SendToServer(echoString);
}


void MainWindow::on_lineEdit_returnPressed()
{
    QString echoString = "ECHO " + ui->lineEdit->text();
    SendToServer(echoString);
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Qt/project/jsonserver/users.db");

    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT name,score FROM listworkers");
        if (query.exec())
        {
            QSqlTableModel *model = new QSqlTableModel(this);
            model->setTable("listworkers");
            model->setHeaderData(0, Qt::Horizontal, tr("Player"));
            model->setHeaderData(1, Qt::Horizontal, tr("Score"));
            model->setQuery(query);
            ui->tableView->setModel(model);
            QString styleSheet = "\
                QTableView {\
                    border: 2px solid darkgreen;\
                    border-radius: 10px;\
                    background-color: gold;\
                    font-family: Arial;\
                    font-size: 12px;\
            }\
                QTableView::item {\
                    padding: 5px;\
                    color: darkgreen;\
            }\
                QHeaderView::section {\
                    background-color: green;\
                    color: gold;\
                    font-size: 14px;\
            }";
                ui->tableView->setStyleSheet(styleSheet);
            ui->tableView->show();
                int rowCount = model->rowCount();
                ui->progressBar->setMaximum(rowCount);
                for (int i = 0; i < rowCount; ++i)
                {
                    ui->progressBar->setValue(i + 1);
                    QApplication::processEvents();
        }
        }
        else
        {
            qDebug() << "Error executing query:";
        }
    }
    else
    {
        qDebug() << "Failed to open database:" ;
    }
}


