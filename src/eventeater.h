#ifndef EVENTEATER_H
#define EVENTEATER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

class EventEater: public QObject
{
    Q_OBJECT

signals:
    void showCalendarRequested(void);

public:
    explicit EventEater(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override{
        if (event->type() == QEvent::MouseButtonRelease) {
            emit showCalendarRequested();
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
};

#endif // EVENTEATER_H
