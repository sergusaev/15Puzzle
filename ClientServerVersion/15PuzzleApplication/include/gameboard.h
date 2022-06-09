#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <vector>
#include <utility>
#include <QTimer>
#include "cachehandler.h"
#include "recordshandlerclient.h"

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int hiddenElementValue READ hiddenElementValue CONSTANT)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(int currentElement READ currentElement WRITE setCurrentElement NOTIFY currentElementChanged)
    Q_PROPERTY(int timePoint READ timePoint NOTIFY timePointChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
    Q_PROPERTY(QString getTime READ getTime NOTIFY getTimeChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)


public:
    using Position = std::pair<int, int>;
    static constexpr int DEFAULT_DIMENSION {2};

    GameBoard(QObject *parent = nullptr, int dimension = DEFAULT_DIMENSION);

    struct Tile {
        int value {};
        Tile& operator= (const int new_value){
            value = new_value;
            return *this;
        }
        bool operator==(const int other) const{
            return other == value;
        }
        bool operator==(const Tile& other) const{
            return other.value == value;
        }
    };



    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

    int hiddenElementIndex() const;

    int hiddenElementValue() const;
    void  setHiddenElementValue(int value);

    void shuffle();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool move (int index);
    Q_INVOKABLE bool checkWin();
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString getTime();
    Q_INVOKABLE QString getUserPassword(const QString& nickname);

    int currentElement() const;
    void setCurrentElement(int value);

    int timePoint() const;
    void setTimePoint(int value);

    int counter() const;
    Q_INVOKABLE void setCounter(int value);

    const QString &nickname() const;
    Q_INVOKABLE void setNickname(const QString &newNickname);

    int dimension() const;
    Q_INVOKABLE void setDimension(int dimension);

    int boardsize() const;
    void setBoardsize(int newBoardsize);

    const QString &password() const;
    Q_INVOKABLE void setPassword(const QString &newPassword);

    Q_INVOKABLE void addUser(const QString &nickname, const QString &password);

private slots:
    void onTimeout();

private:
    std::vector<Tile> m_raw_board;
    int m_dimension;
    int m_boardsize;
    int m_hiddenElementValue;
    int m_currentElement = 0;
    int m_seconds = 0;
    int m_counter = 0;
    QString m_nickname;
    QString m_password;
    QTimer m_timer;
    CacheHandler m_cacheHandler;
    RecordsHandlerClient m_recordsHandler;
    bool isBoardValid() const;
    bool isPositionValid(const int position) const;
    bool isSolved() const;
    Position getRowCol(int index) const;





signals:
    void currentElementChanged();
    void timePointChanged();
    void counterChanged();
    void getTimeChanged();
    void nicknameChanged();
    void dimensionChanged();
    void puzzleSolved(QString nickname, int time, int turns);
    void passwordChanged();
    void passwordFromDBChanged();
};

#endif // GAMEBOARD_H
