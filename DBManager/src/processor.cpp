#include "processor.h"
#include "manipulator.h"
#include "selector.h"
#include "dbmapper.h"
#include <mutex>

namespace db
{
struct Processor::ProcessorPrivate
{
    Selector selector;
    Manipulator manipulator;

#ifdef BUILD_TESTS
    void insertMockData();
    std::once_flag initialized;
#endif

};

#ifdef BUILD_TESTS
void Processor::ProcessorPrivate::insertMockData()
{
    manipulator.insertRow("Records", {{"S1ayer", 346, 464}});
    manipulator.insertRow("Records", {{"CUCUMBER", 396, 521}});
    manipulator.insertRow("Records", {{"Longfellow",  269, 354}});
    manipulator.insertRow("Records", {{"iPussyHunter",  411, 581}});
}
#endif


db::Processor::Processor()
    : m_d {new ProcessorPrivate {}}
{
#ifdef BUILD_TESTS
    auto inserter = [this] {
        m_d->insertMockData();
    };
    std::call_once(m_d->initialized, inserter);
#endif
}

Processor::~Processor()
{
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> Processor::requestTableData(DBTypes::DBTables table)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selector.selectAll(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}

std::pair<DBTypes::DBResult, DBTypes::DBIndex> Processor::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->manipulator.insertRow(tableMapper.at(table), recordData);
}

DBTypes::DBResult Processor::removeDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index)
{
    return m_d->manipulator.removeRow(tableMapper.at(table), index);
}

DBTypes::DBResult Processor::updateDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index, const DBTypes::DBEntry &updatedRecordData)
{
    return m_d->manipulator.updateRow(tableMapper.at(table), index, updatedRecordData);
}

}
