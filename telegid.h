#ifndef TELEGID_H
#define TELEGID_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QtNetwork>

class TELEGID : public QObject
{
    Q_OBJECT

public:
    explicit TELEGID(QObject * = nullptr){}
    ~TELEGID() {}

private:
    struct TV_SHOW{
        TV_SHOW(QString v_start,QString v_event):start(v_start),event(v_event){}
        QString start = "";
        QString event = "";
    };
    struct TV_SHOW_LIST {
        TV_SHOW_LIST(QString v_ch_id,QString v_ch_name):ch_id(v_ch_id),ch_name(v_ch_name){}
        QString ch_id = "";
        QString ch_name = "";
        QVector<TV_SHOW> ch_show;
    };

private:
    QJsonObject toJson(QByteArray str){ return QJsonDocument::fromJson(str).object(); }
    void setModel(QVector<TV_SHOW_LIST> data, QString id);

signals:
    void dataUpdated(QStringList model);

public slots:
    void setChannel(QString id);
};

#endif // TELEGID_H
