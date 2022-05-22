#include "gameboard.h"
#include "recordsmodel.h"

#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>


GameBoard::GameBoard(QObject *parent, size_t board_dimension):
    QAbstractListModel {parent},
    m_dimension {board_dimension},
    m_boardsize {board_dimension * board_dimension},
    m_hiddenElementValue {m_boardsize},
    m_currentElement {-1},
    m_seconds {0},
    m_counter {0},
    m_nickname {"Longfellow"}

{
    m_raw_board.resize(m_boardsize);
    std::iota(m_raw_board.begin(), m_raw_board.end(), 1);
    shuffle();
    connect(&m_timer, &QTimer::timeout, this, &GameBoard::onTimeout);

}


void GameBoard::onTimeout()
{
    setTimePoint(timePoint() + 1);
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
    for (size_t i {0}; i < m_boardsize; ++i) {
        for (size_t j = i; j < m_boardsize; ++j) {
            if (m_raw_board[j].value < m_raw_board[i].value && m_raw_board[i].value!=m_boardsize){
                ++inv;
            }
        }
    }
    const size_t start_point = 1;

    for (size_t i = 0; i < m_boardsize; ++i) {
        if (m_raw_board[i].value == m_boardsize){
            inv += start_point + i / m_dimension;
        }
    }

    return (inv % 2) == 0;
}

bool GameBoard::isPositionValid(const size_t position) const
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

    const auto index_row {static_cast<size_t>(index.row())};

    if (!isPositionValid(index_row)) {
        return {};
    }

    return QVariant(static_cast<int>(m_raw_board[index_row].value));
}

size_t GameBoard::hiddenElementValue() const
{
    return m_hiddenElementValue;
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
    return  QString("%1 : %2").arg(timePoint() / 60).arg(timePoint() % 60);
}


GameBoard::Position GameBoard::getRowCol(size_t index) const
{
    size_t row = index / m_dimension;
    size_t col = index % m_dimension;
    return std::make_pair(row, col);
}

namespace  {
    bool is_adjacent (GameBoard::Position first, GameBoard::Position second)
    {
        if (first == second){
            return false;
        }

        const auto calc_distance = [](size_t pos1, size_t pos2){
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
    if (!isPositionValid(static_cast<size_t>(index))) {
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
        m_recordsHandler.addRecord({m_nickname, m_seconds, m_counter});
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

size_t GameBoard::dimension() const
{
    return m_dimension;
}

bool GameBoard::isSolved() const
{
    std::vector<Tile> solved_ethalon(m_boardsize);
    std::iota(solved_ethalon.begin(), solved_ethalon.end(), 1);
    return solved_ethalon == m_raw_board;
}
