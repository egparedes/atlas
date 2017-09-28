/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
#pragma once

#include "atlas/array/gridtools/GridToolsTraits.h"

//------------------------------------------------------------------------------------------------------

namespace atlas {
namespace array {

//------------------------------------------------------------------------------------------------------

template< typename Value >
class StorageView
{
public:

    using storage_view_t = gridtools::data_view_tt<Value, 1>;

public:

    StorageView(storage_view_t storage_view, size_t size, bool contiguous = true) :
        gt_storage_view_(storage_view),
        size_(size),
        contiguous_(contiguous)
    {}

    Value* data() { return gt_storage_view_.data(); }

    size_t size() { return size_; }

    bool contiguous() const { return contiguous_; }

    void assign(const Value& value) {
        ASSERT( contiguous() );
        Value* raw_data = data();
        for( size_t j=0; j<size_; ++j ) {
            raw_data[j] = value;
        }
    }


private:
    storage_view_t gt_storage_view_;
    size_t size_;
    bool contiguous_;
};

//------------------------------------------------------------------------------------------------------

} // namespace array
} // namespace atlas