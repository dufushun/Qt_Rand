#ifndef TEST_H
#define TEST_H

#include <QtGui/QMainWindow>
#include "ui_test.h"
#include "CRandThread.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

class Test : public QMainWindow
{
    Q_OBJECT

public:
    Test(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Test();
private slots:
    void slotSetNum(int);
    void slotNewConnection();
    void slotDisplayError(QAbstractSocket::SocketError);
    void on_btn_send_clicked();
    void slotRevData();
    void slotTimeout();
private:
    void NewListen();
private:
    Ui::Test* ui;
    CRandThread* m_pThread;
    QTcpSocket* m_pTcpSocket;
    QTcpServer* m_pTcpServer;
    QTimer* m_pTimer;

    CRandThread* m_pThread1;
    CRandThread* m_pThread2;
    bool m_bFisrt;

};

#endif // TEST_H
