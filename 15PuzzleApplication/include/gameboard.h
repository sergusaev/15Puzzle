#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <utility>
#include <QTimer>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int hiddenElementValue READ hiddenElementValue CONSTANT)
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int currentElement READ currentElement WRITE setCurrentElement NOTIFY currentElementChanged)
    Q_PROPERTY(int timePoint READ timePoint NOTIFY timePointChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
    Q_PROPERTY(QString getTime READ getTime NOTIFY getTimeChanged)
    Q_PROPERTY(bool winStatus READ winStatus WRITE setWinStatus NOTIFY winStatusChanged)

public:
    using Position = std::pair<size_t, size_t>;
    static constexpr size_t DEFAULT_DIMENSION  {4};

    GameBoard(QObject *parent = nullptr, size_t board_dimension = DEFAULT_DIMENSION);

    struct Tile {
        size_t value {};
        Tile& operator= (const size_t new_value){
            value = new_value;
            return *this;
        }
        bool operator==(const size_t other) const{
            return other == value;
        }
        bool operator==(const Tile& other) const{
            return other.value == value;
        }
    };



    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

    int hiddenElementIndex() const;



    void shuffle();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setCurrentElement(int value);
    void setTimePoint(int value);
    Q_INVOKABLE void setCounter(int value);
    Q_INVOKABLE void setWinStatus(bool value);
    Q_INVOKABLE QString getTime();
    Q_INVOKABLE bool move (int index);
    Q_INVOKABLE bool checkWin();
    Q_INVOKABLE void restart();
    int currentElement() const;
    int timePoint() const;
    int counter() const;
    bool winStatus() const;
    size_t dimension() const;
    size_t hiddenElementValue() const;


private slots:
    void onTimeout();

private:
    std::vector<Tile> m_raw_board;
    const size_t m_dimension;
    const size_t m_boardsize;
    const size_t m_hiddenElementValue;
    int m_currentElement = 0;
    int m_seconds = 0;
    int m_counter = 0;
    QString nickname;
    bool m_currWinStatus = false;
    QString m_bestTime;
    int m_bestTurns;
    QTimer m_timer;


    bool isBoardValid() const;
    bool isPositionValid(const size_t position) const;
    bool isSolved() const;
    Position getRowCol(size_t index) const;

signals:
    void currentElementChanged();
    void timePointChanged();
    void counterChanged();
    void getTimeChanged();
    void winStatusChanged();

};

#endif // GAMEBOARD_H
