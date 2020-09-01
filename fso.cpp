#include "fso.h"

FSO::FSO() : QFileSystemModel() {
    //первый запуск приложения
#ifdef Q_OS_ANDROID
    requestAndroidPermissions();
#endif
    //проверяем существование файла ChannelsList.xml
    if(!QDir(STORAGE_PATH).exists()?
            QDir(STORAGE_PATH).mkdir(".") : true)
        (!QFile(STORAGE_FILE).exists()?
                QFile::copy(":/ChannelsList.xml",STORAGE_FILE) : true);

    //каталог download
    setRootPath(DOWNLOAD_PATH);
    setResolveSymlinks(true);
    setFilter( QDir::NoDot | QDir::Dirs | QDir::Files);
}

QVariant FSO::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role >= SizeRole) {
        switch (role) {
        case SizeRole:
            return QVariant(size(fileInfo(index)));
        case DisplayableFilePermissionsRole:
            return QVariant(permission(fileInfo(index)));
        case LastModifiedRole:
            return QVariant(fileInfo(index)
                            .lastModified()
                            .toString(Qt::ISODate)
                            .replace("T"," "));
        case UrlStringRole:
            return QVariant(QUrl::fromLocalFile(filePath(index)).toString());
        default:
            break;
        }
    }
    return QFileSystemModel::data(index, role);
}

QHash<int, QByteArray> FSO::roleNames() const {
    QHash<int, QByteArray> result = QFileSystemModel::roleNames();
    result.insert(SizeRole,
                  QByteArrayLiteral("size"));
    result.insert(DisplayableFilePermissionsRole,
                  QByteArrayLiteral("displayableFilePermissions"));
    result.insert(LastModifiedRole,
                  QByteArrayLiteral("lastModified"));
    return result;
}

#ifdef Q_OS_ANDROID
bool FSO::requestAndroidPermissions(){
    const QVector<QString> permissions({"android.permission.WRITE_EXTERNAL_STORAGE",
                                        "android.permission.READ_EXTERNAL_STORAGE"});
    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return false;
        }
    }
    return true;
}
#endif

void FSO::addItems(QModelIndexList indexes) {
    selected.clear(); //выделяем только 1 файл
    foreach(QModelIndex index, indexes) //но возможно несколько
        selected.append(QFileSelected(this->data(index).toString(),
                                      fileInfo(index).absoluteFilePath()));}

void FSO::upToDir() {
    QDir dir = rootDirectory();
    if (dir.cdUp())
        setRootPath(dir.absolutePath());}

void FSO::replaceXml() {
    if(!selected.isEmpty()){
        if (validate(selected.first().full_path,"*.xml")){
            QFile fileFrom(selected.first().full_path);
            if (fileFrom.exists()){
                savedXml = WSLASH(selected.first().full_path);
                removeXml(STORAGE_FILE);
                QFile::copy(WSLASH(selected.first().full_path),
                            STORAGE_FILE);
                emit dataUpdated();
            }
        }
        else if(validate(selected.first().full_path,"*.m3u")){
            QPlayList playlist = readXml2QMap();
            if (importM3U(selected.first().full_path,playlist)){
                savedXml = WSLASH(selected.first().full_path);
                removeXml(STORAGE_FILE);
                saveQMap2Xml(playlist);
                emit dataUpdated();
            }
        }
    }
}

void FSO::saveXml() {
    if(!selected.isEmpty()){
        savedXml = WSLASH(selected.first().full_path);
        if (QFileInfo(savedXml).isDir())
            savedXml = WSLASH(savedXml.append("/ChannelsList.xml"));
        removeXml(savedXml);
        QFile::copy(STORAGE_FILE, savedXml);
    }
}

void FSO::removeChannel(QString v_id, QString v_caption){
    QPlayList playlist = readXml2QMap();
    foreach (int ii, playlist.keys()){
        QTVChannel channel = playlist.value(ii);
        if (channel.id.compare(v_id) == 0 &&
                channel.caption.compare(v_caption) == 0){
            channel.src = "";
            playlist[ii] = channel;
        }
    }
    removeXml(STORAGE_FILE);
    saveQMap2Xml(playlist);
    emit dataUpdated();
}

QString FSO::permission(const QFileInfo& info) const {
    const QFile::Permissions permissions = info.permissions();
    QString result = QLatin1String("----------");
    if (info.isSymLink())
        result[0] = QLatin1Char('l');
    else if (info.isDir())
        result[0] = QLatin1Char('d');
    if (permissions & QFileDevice::ReadUser)
        result[1] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteUser)
        result[2] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeUser)
        result[3] = QLatin1Char('x');
    if (permissions & QFileDevice::ReadGroup)
        result[4] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteGroup)
        result[5] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeGroup)
        result[6] = QLatin1Char('x');
    if (permissions & QFileDevice::ReadOther)
        result[7] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteOther)
        result[8] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeOther)
        result[9] = QLatin1Char('x');
    return result;
}

QString FSO::size(const QFileInfo& info) const {
    if (!info.isFile())
        return QString();
    const qint64 size = info.size();
    if (size > 1024 * 1024 * 10)
        return QString::number(size / (1024 * 1024)) + QLatin1Char('M');
    if (size > 1024 * 10)
        return QString::number(size / 1024) + QLatin1Char('K');
    return QString::number(size);
}

bool FSO::validate(QString str, QString pattern){
    return QRegExp(pattern,Qt::CaseInsensitive,QRegExp::Wildcard)
            .exactMatch(str); }

void FSO::removeXml(QString src){
    QFile file(WSLASH(src));
    if (file.exists()){
        file.setPermissions(QFile::ReadOther | QFile::WriteOther);
        file.remove();
    }
}

QPlayList FSO::readXml2QMap(){
    QPlayList playlist;
    QString v_id,v_caption,v_src;
    QFile file(STORAGE_FILE);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        int ii = 0;
        while(!xmlReader.atEnd()){
            if(xmlReader.isStartElement()){
                if(xmlReader.name() == "ListElement")
                    v_src.clear();
                if(xmlReader.name() == "channel_id")
                    v_id = xmlReader.readElementText();
                if(xmlReader.name() == "caption")
                    v_caption = xmlReader.readElementText();
                if(xmlReader.name() == "source")
                    v_src = xmlReader.readElementText();
            }
            if(xmlReader.isEndElement())
                if(xmlReader.name() == "ListElement")
                    playlist[ii++] = QTVChannel(v_id,v_caption,v_src);
            xmlReader.readNext();
        }
    }
    file.close();
    return playlist;
}

bool FSO::importM3U(QString fname, QPlayList &playlist){
    QFile file(WSLASH(fname));
    if (file.open(QFile::ReadOnly | QFile::Text)){
        //пользовательский диапазон каналов
        int counter = LAST_CHANNEL_ID;
        foreach (int ii, playlist.keys())
            counter = (playlist.value(ii).id.toInt() > counter?
                           playlist.value(ii).id.toInt() : counter);

        QString v_id,v_caption,v_src,v_sign;
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        QString line;
        while (stream.readLineInto(&line)) {
            if(validate(line,"#EXTINF:*")){
                v_caption = line.replace("#EXTINF:-1","").SYMB_ONLY;
                v_sign = line.TO_SIGN;
            }
            if(validate(line,"http*")){
                v_src = line;
                bool defined = false;
                foreach (int ii, playlist.keys()){
                    if(v_sign.compare(playlist.value(ii).sign) == 0){
                        if(playlist.value(ii).src.isEmpty() ||
                                playlist.value(ii).src.isNull()){
                            QTVChannel channel = playlist.value(ii);
                            channel.src = v_src;
                            playlist[ii] = channel;
                        }
                        defined = true;
                    }
                }
                /* ----------------------------------------------------------------
                    if (!defined)
                        playlist[playlist.count()] =
                                QTVChannel(QString::number(++counter),v_caption,v_src);
                     --------------------------------------------------------------- */
            }
        }
        file.close();
        return true;
    }
    return false;
}

void FSO::saveQMap2Xml(QPlayList &playlist){
    QFile file(STORAGE_FILE);
    if (file.open(QFile::WriteOnly | QFile::Text)){
        QXmlStreamWriter xml;
        xml.setDevice(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("ListModel");
        for (int ii = 0; ii < playlist.count(); ii++) {
            xml.writeStartElement("ListElement");
            xml.writeTextElement("channel_id",playlist[ii].id);
            xml.writeTextElement("caption",playlist[ii].caption);
            xml.writeTextElement("source",playlist[ii].src);
            xml.writeTextElement("cover",
                                 QString("qrc:/covers/")
                                 .append(playlist[ii].id.toInt() > LAST_CHANNEL_ID?
                                             "9999" : playlist[ii].id)
                                 .append(".png"));
            xml.writeEndElement();
        }
        xml.writeEndElement();
        xml.writeEndDocument();
    }
    file.flush();
    file.close();
}
