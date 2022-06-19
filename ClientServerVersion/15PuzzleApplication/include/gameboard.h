#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <vector>
#include <utility>
#include <QTimer>
#include "cachehandler.h"
#include "errorhandler.h"
#include "requestshandlerclient.h"
#include "authorizationmanager.h"

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(int hiddenElementValue READ hiddenElementValue CONSTANT)
    Q_PROPERTY(int currentElement READ currentElement WRITE setCurrentElement NOTIFY currentElementChanged)
    Q_PROPERTY(int timePoint READ timePoint NOTIFY timePointChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
    Q_PROPERTY(QString getTime READ getTime NOTIFY getTimeChanged)

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

    int currentElement() const;
    void setCurrentElement(int value);

    int timePoint() const;
    void setTimePoint(int value);

    int counter() const;
    Q_INVOKABLE void setCounter(int value);

    int dimension() const;
    void setDimension(int dimension);

    int boardsize() const;
    void setBoardsize(int newBoardsize);



private slots:
    void onTimeout();
    void onDimensionChanged(int dimension);


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
    QString m_ethalonPassword;
    QTimer m_timer;

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
    void passwordChanged();
    void passwordFromDBChanged();
    void ethalonPasswordChanged();
};

#endif // GAMEBOARD_H
