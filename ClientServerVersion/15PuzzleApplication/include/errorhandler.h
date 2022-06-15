#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include <QtQml>
#include <QObject>

class ErrorHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool noServerConnection READ noServerConnection WRITE setNoServerConnection NOTIFY noServerConnectionChanged)
    Q_PROPERTY(bool internalServerError READ internalServerError WRITE setInternalServerError NOTIFY internalServerErrorChanged)
    Q_PROPERTY(bool cacheAddingTextVisible READ cacheAddingTextVisible WRITE setCacheAddingTextVisible NOTIFY cacheAddingTextVisibleChanged)

public:
     ErrorHandler();
    ~ErrorHandler();

    bool noServerConnection() const;
    void setNoServerConnection(bool newNoServerConnection);

    bool internalServerError() const;
    void setInternalServerError(bool newInternalServerError);

    bool cacheAddingTextVisible() const;
    void setCacheAddingTextVisible(bool newCacheAddingTextVisible);

signals:
    void noServerConnectionChanged();
    void internalServerErrorChanged();
    void cacheAddingTextVisibleChanged();

private slots:
    void onNoServerConnection();
    void onInternalServerErrorOccured(const QVariant &data);



private:


    bool m_noServerConnection;
    bool m_internalServerError;
    bool m_cacheAddingTextVisible;

};

#endif // ERRORHANDLER_H
