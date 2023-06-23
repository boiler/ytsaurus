#pragma once

#include <library/cpp/yson/node/node.h>
#include <yt/cpp/mapreduce/interface/client.h>
#include <yt/systest/operation.h>
#include <yt/systest/table.h>

namespace NYT::NTest {

class IDatasetIterator {
public:
    virtual ~IDatasetIterator();
    virtual TRange<TNode> Values() const = 0;
    virtual bool Done() const = 0;
    virtual void Next() = 0;
};

////////////////////////////////////////////////////////////////////////////////

class IDataset {
public:
    virtual ~IDataset();
    virtual const TTable& table_schema() const = 0;
    virtual std::unique_ptr<IDatasetIterator> NewIterator() const = 0;
};

////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<IDataset> Map(const IDataset& source, const IMultiMapper& operation);

void MaterializeIntoTable(IClientPtr client, const TString& tablePath, const IDataset& dataset);
void VerifyTable(IClientPtr client,  const TString& tablePath, const IDataset& dataset);

}  // namespace NYT::NTest