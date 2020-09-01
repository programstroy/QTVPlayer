TEMPLATE = app
QT += quick qml quickcontrols2 widgets

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
QT += androidextras
}

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        fso.cpp \
        main.cpp \
        telegid.cpp
RESOURCES += qml.qrc
QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew \
    android/gradlew.bat \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/values/libs.xml
RC_FILE = QTVPlayer.rc

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
    ANDROID_EXTRA_LIBS += \
                $$PWD/android/libs/libcrypto_1_1.so \
                $$PWD/android/libs/libssl_1_1.so
}

HEADERS += \
    fso.h \
    telegid.h
