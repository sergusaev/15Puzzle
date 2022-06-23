QT += core quick sql qml
CONFIG += c++11

QML_IMPORT_NAME = AuthorizationManager
QML_IMPORT_MAJOR_VERSION = 1



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/nicknamehint.cpp \
        src/signalshandler.cpp \
        src/authorizationmanager.cpp \
        src/cachehandler.cpp \
        src/clientmanager.cpp \
        src/recordsmodel.cpp \
        src/record.cpp \
        src/gameboard.cpp \
        main.cpp \
        src/requestshandlerclient.cpp \
        src/usersettings.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
#QML2_IMPORT_PATH += $$PWD/qml
QML_ROOT_PATH = $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/authorizationmanager.h \
    include/cachehandler.h \
    include/clientmanager.h \
    include/gameboard.h \
    include/record.h \
    include/recordsmodel.h \
    include/requestshandlerclient.h \
    include/usersettings.h \
    include/signalshandler.h \
    include/nicknamehint.h

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../shared/include

win32 {
LIBS += -L$$PWD/../shared/lib/win32 -lDBManager
LIBS += -L$$PWD/../shared/lib/win32 -lNetworkLib
}
android {
LIBS += -L$$PWD/../shared/lib/android -lDBManager_$${ANDROID_TARGET_ARCH}
LIBS += -L$$PWD/../shared/lib/android -lNetworkLib_$${ANDROID_TARGET_ARCH}

for (abi, ANDROID_ABIS) {
    ANDROID_EXTRA_LIBS += $$PWD/../shared/lib/android/libDBManager_$${abi}.so
    ANDROID_EXTRA_LIBS += $$PWD/../shared/lib/android/libNetworkLib_$${abi}.so
}
}

#ITEM += \
#        logo.ico

DEFINES += DEBUG_OUTPUT

win32:RC_FILE = ico_rec.rc

android {
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

#QT_BINS = $$shell_path($${QT.core.bins})
#QMAKE_POST_LINK += "$$QMAKE_COPY release\\$${TARGET}.exe $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../../Dist/15Puzzle/))" & \
#    "$${QT_BINS}\\windeployqt.exe --release --qmldir $${QT_BINS}\\..\\qml $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../../Dist/15Puzzle/$${TARGET}.exe))"

DISTFILES += \
    AutorizationWindow.qml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
    }
