#ifndef CRAND_THREAD_H 
#define CRAND_THREAD_H
#include <QThread>

class CRandThread:public QThread
{
    Q_OBJECT
public:
    CRandThread( QObject* parent);
    ~CRandThread();
public:
    int GetRandNum();
signals:
    void signalSetNum(int num);
protected:
    virtual void run();
private:
    bool m_bExit;
    int m_randNum;
};




#endif//CRAND_THREAD_H
