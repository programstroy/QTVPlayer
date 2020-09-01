#ifndef FSO_H
#define FSO_H

#include <QObject>
#include <QFileSystemModel>
#include <QDateTime>
#include <QUrl>
#include <QSharedPointer>
#include <QStandardPaths>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QVector>

#define LAST_CHANNEL_ID 9004
#define WSLASH QDir::toNativeSeparators

#ifdef Q_OS_ANDROID
  #include <QtAndroidExtras/QtAndroid>
  #define STORAGE_PATH QStandardPaths::standardLocations(QStandardPaths::DataLocation)[1]
#else
  #define STORAGE_PATH QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
#endif

#define STORAGE_FILE WSLASH(STORAGE_PATH + "/ChannelsList.xml")
#define DOWNLOAD_PATH QStandardPaths::standardLocations(QStandardPaths::DownloadLocation)[0]
#define SYMB_ONLY replace(",","").replace("-","").replace("_","").replace(".","").replace("!","")
#define TO_SIGN  replace(" ","").toUpper().trimmed()

struct QFileSelected {
    QFileSelected(QString v_name, QString v_path): name(v_name),full_path(v_path){}
    QString name,full_path;
};
struct QTVChannel {
    QTVChannel(QString v_id = "", QString v_caption = "", QString v_src = ""):
        id(v_id),src(v_src),caption(v_caption),sign(v_caption.SYMB_ONLY.TO_SIGN){}
    void empty(){id = ""; src = ""; caption = ""; sign = "";}
    QString id, src, caption, sign, imp;
};
using QFileList = QList<QFileSelected>;
using QPlayList = QMap<int, QTVChannel>;

class FSO: public QFileSystemModel
{
    Q_OBJECT

public:
    explicit FSO();

    enum Roles {
        SizeRole = Qt::UserRole + 4,
        DisplayableFilePermissionsRole = Qt::UserRole + 5,
        LastModifiedRole = Qt::UserRole + 6,
        UrlStringRole = Qt::UserRole + 7
    };
    Q_ENUM(Roles)

    QVariant data(const QModelIndex&,int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;

#ifdef Q_OS_ANDROID
    bool requestAndroidPermissions();
#endif

public slots:
    QModelIndex getRootIndex() { return index(rootPath()); }
    QUrl getPath() { return QUrl::fromLocalFile(STORAGE_FILE); }
    QString getDir() { return getPath().path(); }
    QString getXMLName() { return savedXml; }
    void addItems(QModelIndexList indexes);
    void upToDir();
    void replaceXml();
    void saveXml();
    void removeChannel(QString v_id, QString v_caption);

signals:
    void dataUpdated();

private:
    QFileList selected;
    QString permission(const QFileInfo&) const;
    QString size(const QFileInfo&) const;
    QString savedXml;

private:
    bool validate(QString str,QString pattern);
    void removeXml(QString src);
    QPlayList readXml2QMap();
    bool importM3U(QString fname,QPlayList& playlist);
    void saveQMap2Xml(QPlayList& playlist);
};

#endif // FSO_H
