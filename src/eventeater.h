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
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug("Ate key press %d", keyEvent->key());
            emit showCalendarRequested();
            // return QObject::eventFilter(obj, event);
            return true;
        } else {
            // standard event processing
            // return true;
            return QObject::eventFilter(obj, event);
        }
    }
};

#endif // EVENTEATER_H
