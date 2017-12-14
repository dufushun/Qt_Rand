#include "CRandThread.h"
#include <QTime>

CRandThread::CRandThread(QObject* parent):QThread(parent),
m_bExit(false), m_randNum(0)
{
}

CRandThread::~CRandThread()
{
    int quitTimes = 0;
    m_bExit = true;
    while (!wait(5)) {
        QThread::msleep(50);
        if (++quitTimes > 10) {
            quit();
        }
    }
}

int CRandThread::GetRandNum()
{
    return m_randNum;
}

void CRandThread::run()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    while (!m_bExit)
    {
        m_randNum = qrand()%100;
        emit signalSetNum(qrand()%100);
        for (int i = 0; i< 10; i++)
        {
            if (m_bExit)
            {
                return;
            }
            QThread::msleep(100);
        } 
    }
}

