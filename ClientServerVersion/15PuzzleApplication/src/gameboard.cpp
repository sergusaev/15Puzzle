#include "gameboard.h"
#include "recordsmodel.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>


GameBoard::GameBoard(QObject *parent, int dimension):
    QAbstractListModel {parent},
    m_dimension {dimension},
    m_currentElement {-1},
    m_seconds {0},
    m_counter {0}
{

    connect(&m_timer, &QTimer::timeout, this, &GameBoard::onTimeout);

}


void GameBoard::onTimeout()
{
    setTimePoint(timePoint() + 1);
}



const QString &GameBoard::password() const
{
    return m_password;
}

void GameBoard::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

void GameBoard::addUser(const QString &nickname, const QString &password)
{
    m_recordsHandler.addUserLogPass(nickname, password);
}

int GameBoard::boardsize() const
{
    return m_boardsize;
}

void GameBoard::setBoardsize(int newBoardsize)
{
    if (m_boardsize == newBoardsize)
        return;
    m_boardsize = newBoardsize;
}

const QString &GameBoard::nickname() const
{
    return m_nickname;
}

void GameBoard::setNickname(const QString &newNickname)
{
    if (m_nickname == newNickname)
        return;
    m_nickname = newNickname;
    emit nicknameChanged();
}

bool GameBoard::moveRows(const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild)
{
    const int sourceEndRow = sourceRow + count;
    const bool nice_input = (sourceEndRow > 0) &&
            (sourceEndRow <= static_cast<int>(m_boardsize)) &&
            !(sourceRow <= destinationChild && destinationChild < sourceEndRow);
    if (!nice_input) {
        return false;
    }
    beginMoveRows(sourceParent, sourceRow, sourceEndRow - 1, destinationParent, destinationChild);
    const std::vector<Tile> movingRowsCopy = {m_raw_board.cbegin() + sourceRow,
                                              m_raw_board.cbegin() + sourceEndRow};
    m_raw_board.erase(m_raw_board.cbegin() + sourceRow,
                      m_raw_board.cbegin() + sourceEndRow);
    m_raw_board.insert(m_raw_board.cbegin() + destinationChild - (destinationChild > sourceRow ? count : 0),
                       movingRowsCopy.begin(), movingRowsCopy.end());

    endMoveRows();
    return true;
}


int GameBoard::hiddenElementIndex() const
{
    const auto hiddenElementIterator =
            std::find(m_raw_board.begin(), m_raw_board.end(),
                      m_hiddenElementValue);

    return static_cast<int>(std::distance(m_raw_board.begin(), hiddenElementIterator));
}



void GameBoard::shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 g(seed);
    std::vector<Tile> solved_ethalon(m_boardsize);
    std::iota(solved_ethalon.begin(), solved_ethalon.end(), 1);
    do {
        std::shuffle(m_raw_board.begin(), m_raw_board.end(), g);
    }
    while (!isBoardValid() || m_raw_board == solved_ethalon);
    emit dataChanged(createIndex(0, 0), createIndex(m_boardsize, 0));
}

bool GameBoard::isBoardValid() const
{
    int inv {0};
    for (int i {0}; i < m_boardsize; ++i) {
        for (int j = i; j < m_boardsize; ++j) {
            if (m_raw_board[j].value < m_raw_board[i].value && m_raw_board[i].value!=m_boardsize){
                ++inv;
            }
        }
    }
    const int start_point = 1;

    for (int i = 0; i < m_boardsize; ++i) {
        if (m_raw_board[i].value == m_boardsize){
            inv += start_point + i / m_dimension;
        }
    }

    return (inv % 2) == 0;
}

bool GameBoard::isPositionValid(const int position) const
{
    return position < m_boardsize;
}

int GameBoard::rowCount(const QModelIndex &/*parent*/) const
{
    return static_cast<int>(m_boardsize);
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const auto index_row {static_cast<int>(index.row())};

    if (!isPositionValid(index_row)) {
        return {};
    }

    return QVariant(static_cast<int>(m_raw_board[index_row].value));
}

int GameBoard::hiddenElementValue() const
{
    return m_hiddenElementValue;
}

void GameBoard::setHiddenElementValue(int value)
{
    if(m_hiddenElementValue == value) {
        return;
    }
    m_hiddenElementValue = value;
}


int GameBoard::currentElement() const
{
    return m_currentElement;
}

int GameBoard::timePoint() const
{
    return m_seconds;
}

int GameBoard::counter() const
{
    return m_counter;
}


void GameBoard::setCurrentElement(int value)
{
    if(!m_timer.isActive()) {
        m_timer.start(1000);
    }
    if(m_currentElement == value) {
        return;
    }
    m_currentElement = value;
    emit currentElementChanged();
}

void GameBoard::setTimePoint(int value)
{
    if(m_seconds==value) {
        return;
    }
    m_seconds = value;
    emit timePointChanged();
    emit getTimeChanged();

}

void GameBoard::setCounter(int value)
{
    if(m_counter == value) {
        return;
    }
    m_counter = value;
    emit  counterChanged();
}


QString GameBoard::getTime()
{
    QString min = ((timePoint() / 60) < 10) ? QString("0%1").arg(timePoint() / 60) : QString("%1").arg(timePoint() / 60);
    QString sec = ((timePoint() % 60) < 10) ? QString("0%1").arg(timePoint() % 60) : QString("%1").arg(timePoint() % 60);
    return min + ":" + sec;
}

QString GameBoard::getUserPassword(const QString& nickname)
{
    QString ret {m_recordsHandler.getPassword(nickname)};
    return ret;
}


GameBoard::Position GameBoard::getRowCol(int index) const
{
    int row = index / m_dimension;
    int col = index % m_dimension;
    return std::make_pair(row, col);
}

namespace  {
bool is_adjacent (GameBoard::Position first, GameBoard::Position second)
{
    if (first == second){
        return false;
    }

    const auto calc_distance = [](int pos1, int pos2){
        int distance = static_cast<int>(pos1);
        distance -= static_cast<int>(pos2);
        distance = std::abs(distance);
        return distance;
    };

    bool result {false};

    if (first.first == second.first) {
        int distance = calc_distance (first.second, second.second);
        if (distance == 1) {
            result = true;
        }
    } else if (first.second == second.second) {
        int distance = calc_distance (first.first, second.first);
        if (distance == 1) {
            result = true;
        }
    }

    return result;
}
}

bool GameBoard::move(int index)
{
    if (!isPositionValid(static_cast<int>(index))) {
        return false;
    }
    Position positionOfIndex {getRowCol(index)};
    const int oldHiddenIndex = hiddenElementIndex();
    Position hiddenElementPosition {getRowCol(oldHiddenIndex)};
    if (!is_adjacent(positionOfIndex, hiddenElementPosition)) {
        return false;
    }
    moveRow(QModelIndex(), index, QModelIndex(), index > oldHiddenIndex ? oldHiddenIndex : oldHiddenIndex + 1);
    const int newHiddenIndex = hiddenElementIndex();
    if (newHiddenIndex != index) {
        moveRow(QModelIndex(), newHiddenIndex, QModelIndex(), newHiddenIndex > index ? index : index + 1);
    }
    return true;
}

bool GameBoard::checkWin()
{
    if(isSolved()) {
        m_timer.stop();
        m_recordsHandler.addRecord({m_nickname, m_seconds, m_counter, m_dimension});
        return true;
    }
    else {
        return false;
    }
}

void GameBoard::restart()
{
    m_timer.stop();
    setTimePoint(0);
    setCounter(0);
    shuffle();
}

int GameBoard::dimension() const
{
    return m_dimension;
}

void GameBoard::setDimension(int dimension)
{
    m_dimension = static_cast<int>(dimension);
    setBoardsize(m_dimension * m_dimension);
    setHiddenElementValue(m_boardsize);
    m_raw_board.resize(m_boardsize);
    std::iota(m_raw_board.begin(), m_raw_board.end(), 1);
    shuffle();

}

bool GameBoard::isSolved() const
{
    std::vector<Tile> solved_ethalon(m_boardsize);
    std::iota(solved_ethalon.begin(), solved_ethalon.end(), 1);
    return solved_ethalon == m_raw_board;
}
