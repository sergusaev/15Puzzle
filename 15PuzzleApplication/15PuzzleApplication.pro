QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/recordshandler.cpp \
        src/recordsmodel.cpp \
        src/record.cpp \
        src/gameboard.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/gameboard.h \
    include/record.h \
    include/recordsmodel.h \
    include/recordshandler.h

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../shared/include

LIBS += -L$$PWD/../shared/lib/ -lDBManager

ITEM += \
        logo.ico

win32:RC_FILE = ico_rec.rc


ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

#QT_BINS = $$shell_path($${QT.core.bins})
#QMAKE_POST_LINK += "$$QMAKE_COPY release\\$${TARGET}.exe $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../../Dist/15Puzzle/))" & \
#    "$${QT_BINS}\\windeployqt.exe --release --qmldir $${QT_BINS}\\..\\qml $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../../Dist/15Puzzle/$${TARGET}.exe))"

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
