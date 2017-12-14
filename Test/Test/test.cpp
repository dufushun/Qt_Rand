#include "test.h"

Test::Test(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),m_pThread(NULL),
    m_pTcpSocket(NULL),m_pTimer(NULL),m_bFisrt(false)
{
    ui = new Ui::Test();
    ui->setupUi(this);
    m_pThread = new CRandThread(this);
    connect(m_pThread,SIGNAL(signalSetNum(int)), this, SLOT(slotSetNum(int)));
    m_pThread->start();

    m_pTcpServer = new QTcpServer(this);
    //m_pTcpSocket = new QTcpSocket(this);
    NewListen();
    connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    
    m_pThread1 = new CRandThread(this);
    m_pThread1->start();
    m_pThread2 = new CRandThread(this);
    m_pThread2->start();
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    m_pTimer->start(3000);
}

Test::~Test()
{
    delete ui;
}

void Test::slotSetNum(int num)
{
    ui->label->setText(QString::number(num));
}

void Test::slotNewConnection()
{
    m_pTcpSocket = m_pTcpServer->nextPendingConnection();
    connect(m_pTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
        this,SLOT(slotDisplayError(QAbstractSocket::SocketError)));
    connect(m_pTcpSocket,SIGNAL(readyRead()),this,SLOT(slotRevData()));
}

void Test::slotDisplayError(QAbstractSocket::SocketError)
{
    disconnect(m_pTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
        this,SLOT(slotDisplayError(QAbstractSocket::SocketError)));
    m_pTcpSocket->close();
    m_pTcpSocket = NULL;
}

void Test::on_btn_send_clicked()
{
    if (m_pTcpSocket == NULL)
    {
        return;
    }
    QString str = ui->textEdit->toPlainText();
    m_pTcpSocket->write(str.toLatin1(), str.size());
}

void Test::slotRevData()
{
    QString datas = m_pTcpSocket->readAll();
    //接收字符串数据。
    ui->textEdit->setText(datas);
    //显示字符串数据。
}

void Test::slotTimeout()
{
    if (m_bFisrt)
    {
        ui->label_2->setText("Thread1:" + QString::number(m_pThread1->GetRandNum()));
        m_bFisrt = false;
    }else{
        ui->label_2->setText("Thread2:" + QString::number(m_pThread2->GetRandNum()));
        m_bFisrt = true;
    }
}

void Test::NewListen()
{
    if(!m_pTcpServer->listen(QHostAddress::Any,6666))
    {
        qDebug()<<m_pTcpServer->errorString();
        close();
        return;
    }
}
