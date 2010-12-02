#ifndef __WORKER_H_
#define __WORKER_H_

#include <QObject>
#include <QStateMachine>
#include <QMainWindow>

class Worker : public QMainWindow
{
        Q_OBJECT
        public:
                Worker();
                ~Worker();
        private:
                QStateMachine machine;
};

#endif
