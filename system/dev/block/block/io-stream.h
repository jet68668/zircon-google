// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <stdint.h>

#include <fbl/condition_variable.h>
#include <fbl/intrusive_double_list.h>
#include <fbl/intrusive_wavl_tree.h>
#include <fbl/mutex.h>
#include <fbl/ref_counted.h>
#include <fbl/ref_ptr.h>
#include <zircon/listnode.h>
#include <zircon/types.h>

#define IO_STREAM_FLAG_CLOSED      (1u << 0)
#define IO_STREAM_FLAG_SCHEDULED   (1u << 1)

namespace ioqueue {

class Stream;
using StreamRef = fbl::RefPtr<Stream>;

class Stream : public fbl::RefCounted<Stream> {
public:
    Stream(uint32_t pri);
    ~Stream();

    // WAVL Tree support.
    using WAVLTreeNodeState = fbl::WAVLTreeNodeState<StreamRef>;
    struct WAVLTreeNodeTraitsSortById {
        static WAVLTreeNodeState& node_state(Stream& s) { return s.map_node_; }
    };

    struct KeyTraitsSortById {
        static const uint32_t& GetKey(const Stream& s) { return s.id_; }

        static bool LessThan(const uint32_t s1, const uint32_t s2) {
            return (s1 < s2);
        }

        static bool EqualTo(const uint32_t s1, const uint32_t s2) {
            return (s1 == s2);
        }
    };

    using WAVLTreeSortById = fbl::WAVLTree<uint32_t, StreamRef, KeyTraitsSortById,
                                           WAVLTreeNodeTraitsSortById>;


    // List support.
    using ListNodeState = fbl::DoublyLinkedListNodeState<StreamRef>;
    struct ListTraitsByPriority {
        static ListNodeState& node_state(Stream& s) { return s.pri_node_; }
    };

    using ListSortByPriority = fbl::DoublyLinkedList<StreamRef, ListTraitsByPriority>;

    // friend struct KeyTraitsSortById;
    // friend struct WAVLTreeNodeTraitsSortById;
    // friend struct ListNodeState;

    // These fields are protected by the scheduler lock.
    WAVLTreeNodeState map_node_;
    ListNodeState pri_node_;
    uint32_t id_;
    uint32_t priority_;

    fbl::Mutex lock_;
    // These fields are protected by the above stream lock.
    uint32_t flags_ = 0;         // TODO: move flags to the sched lock domain.
    fbl::ConditionVariable event_unscheduled_;
    list_node_t ready_op_list_;
    list_node_t issued_op_list_;
};

} // namespace