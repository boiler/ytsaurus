#include "helpers.h"

#include <yt/yt/core/rpc/helpers.h>

namespace NYT::NTransactionServer {

////////////////////////////////////////////////////////////////////////////////

#define COPY_TRIVIAL_FIELD(dst, src, field) (dst).set_##field((src).field())
#define COPY_FIELD(dst, src, field) (dst).mutable_##field()->Swap((src).mutable_##field())
#define MAYBE_COPY_FIELD_IMPL(dst, src, field, COPY) \
    do { \
        if ((src).has_##field()) {\
            COPY(dst, src, field); \
        } \
    } while (false)
#define MAYBE_COPY_TRIVIAL_FIELD(dst, src, field) MAYBE_COPY_FIELD_IMPL(dst, src, field, COPY_TRIVIAL_FIELD)
#define MAYBE_COPY_FIELD(dst, src, field) MAYBE_COPY_FIELD_IMPL(dst, src, field, COPY_FIELD)

NProto::TReqStartCypressTransaction BuildReqStartCypressTransaction(
    NCypressTransactionClient::NProto::TReqStartTransaction rpcRequest,
    const NRpc::TAuthenticationIdentity& authenticationIdentity)
{
    NProto::TReqStartCypressTransaction request;
    COPY_TRIVIAL_FIELD(request, rpcRequest, timeout);
    MAYBE_COPY_TRIVIAL_FIELD(request, rpcRequest, deadline);
    MAYBE_COPY_FIELD(request, rpcRequest, attributes);
    MAYBE_COPY_TRIVIAL_FIELD(request, rpcRequest, title);
    MAYBE_COPY_FIELD(request, rpcRequest, parent_id);
    COPY_FIELD(request, rpcRequest, prerequisite_transaction_ids);
    COPY_FIELD(request, rpcRequest, replicate_to_cell_tags);
    WriteAuthenticationIdentityToProto(&request, authenticationIdentity);
    return request;
}

#undef COPY_TRIVIAL_FIELD
#undef COPY_FIELD
#undef MAYBE_COPY_FIELD_IMPL
#undef MAYBE_COPY_TRIVIAL_FIELD
#undef MAYBE_COPY_FIELD


NProto::TReqCommitCypressTransaction BuildReqCommitCypressTransaction(
    TTransactionId transactionId,
    TTimestamp commitTimestamp,
    TRange<TTransactionId> prerequisiteTransactionIds,
    const NRpc::TAuthenticationIdentity& authenticationIdentity)
{
    NProto::TReqCommitCypressTransaction request;
    ToProto(request.mutable_transaction_id(), transactionId);
    request.set_commit_timestamp(commitTimestamp);
    ToProto(request.mutable_prerequisite_transaction_ids(), prerequisiteTransactionIds);
    WriteAuthenticationIdentityToProto(&request, authenticationIdentity);
    return request;
}

NProto::TReqAbortCypressTransaction BuildReqAbortCypressTransaction(
    TTransactionId transactionId,
    bool force,
    bool replicateViaHive,
    const NRpc::TAuthenticationIdentity& authenticationIdentity)
{
    NProto::TReqAbortCypressTransaction request;
    ToProto(request.mutable_transaction_id(), transactionId);
    request.set_force(force);
    request.set_replicate_via_hive(replicateViaHive);
    WriteAuthenticationIdentityToProto(&request, authenticationIdentity);
    return request;
}

////////////////////////////////////////////////////////////////////////////////


} // namespace NYT::NTransactionServer
