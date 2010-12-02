#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsView>
#include <QMouseEventTransition>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include <QStateMachine>

#include "worker.h"
#include "mysvg.h"

Worker::Worker() : machine()
{
        // QGraphicsScene is an object to keep graphical items
        QGraphicsScene *scene = new QGraphicsScene();
        scene->setBackgroundBrush(Qt::gray);

        // QGraphicsView shows QGraphicsScene on the screen
        QGraphicsView *view = new QGraphicsView(scene);
        view->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        setCentralWidget(view);
        view->setMinimumSize(800, 480);

        MySvg *flagF = new MySvg("Flag_of_Finland.svg");
        MySvg *flagR = new MySvg("Flag_of_Russia.svg");

        scene->addItem(flagF);
        scene->addItem(flagR);

        flagF->setPos(0, 0);
        flagF->setProperty("scale", 0.1);
        flagF->setProperty("z", 0);

        flagR->setPos(400, 0);
        flagR->setProperty("scale", 0.1);
        flagR->setProperty("z", 0);

        QState *thumb_state = new QState();
        QState *max_state = new QState();
        QState *fin_state = new QState(max_state);
        QState *rus_state = new QState(max_state);

        machine.addState(thumb_state);
        machine.addState(max_state);
        machine.setInitialState(thumb_state);

        machine.setGlobalRestorePolicy(QStateMachine::RestoreProperties);

        fin_state->assignProperty(flagF, "scale", 0.3);
        fin_state->assignProperty(flagF, "z", 1);
        fin_state->assignProperty(flagF, "x", 100);
        fin_state->assignProperty(flagF, "y", 65);

        rus_state->assignProperty(flagR, "scale", 0.3);
        rus_state->assignProperty(flagR, "z", 1);
        rus_state->assignProperty(flagR, "x", 100);
        rus_state->assignProperty(flagR, "y", 65);

        QSignalTransition *ts =
                thumb_state->addTransition(flagF, SIGNAL(click()), fin_state);

        ts->addAnimation(new QPropertyAnimation(flagF, "scale"));
        ts->addAnimation(new QPropertyAnimation(flagF, "x"));
        ts->addAnimation(new QPropertyAnimation(flagF, "y"));
        // Exercise: try to comment out all animations for "z" (layer level)
        // and see what happens. Why?
        ts->addAnimation(new QPropertyAnimation(flagF, "z"));

        ts = thumb_state->addTransition(flagR, SIGNAL(click()), rus_state);

        ts->addAnimation(new QPropertyAnimation(flagR, "scale"));
        ts->addAnimation(new QPropertyAnimation(flagR, "x"));
        ts->addAnimation(new QPropertyAnimation(flagR, "y"));
        ts->addAnimation(new QPropertyAnimation(flagR, "z"));

        QMouseEventTransition *tm = new QMouseEventTransition(view,
                        QEvent::MouseButtonPress, Qt::LeftButton);

        tm->setTargetState(thumb_state);
        max_state->addTransition(tm);

        tm->addAnimation(new QPropertyAnimation(flagR, "scale"));
        tm->addAnimation(new QPropertyAnimation(flagR, "x"));
        tm->addAnimation(new QPropertyAnimation(flagR, "y"));
        tm->addAnimation(new QPropertyAnimation(flagR, "z"));

        tm->addAnimation(new QPropertyAnimation(flagF, "scale"));
        tm->addAnimation(new QPropertyAnimation(flagF, "x"));
        tm->addAnimation(new QPropertyAnimation(flagF, "y"));
        tm->addAnimation(new QPropertyAnimation(flagF, "z"));

        // NB: in the case of this application machine.addDefaultAnimation()
        // should be used instead. See Qt documentation.
        // I use addAnimation() to show the basic principle.

        machine.start();

        view->show();
}

Worker::~Worker()
{}
