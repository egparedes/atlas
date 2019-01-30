/*
 * (C) Copyright 2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation
 * nor does it submit to any jurisdiction.
 */

#include <algorithm>

#include "eckit/exception/Exceptions.h"
#include "eckit/types/FloatCompare.h"

#include "atlas/grid/Grid.h"
#include "atlas/mesh/Elements.h"
#include "atlas/mesh/HybridElements.h"
#include "atlas/mesh/Mesh.h"
#include "atlas/mesh/Nodes.h"
#include "atlas/mesh/detail/MeshImpl.h"
#include "atlas/parallel/mpi/mpi.h"

using atlas::Grid;
using atlas::Projection;

namespace atlas {
namespace mesh {
namespace detail {

//----------------------------------------------------------------------------------------------------------------------

MeshImpl::MeshImpl( eckit::Stream& ) {
    NOTIMP;
}

void MeshImpl::encode( eckit::Stream& ) const {
    NOTIMP;
}

MeshImpl::MeshImpl() : nodes_( new mesh::Nodes() ), dimensionality_( 2 ) {
    createElements();
}

MeshImpl::~MeshImpl() {
    for ( MeshObserver* o : mesh_observers_ ) {
        o->onMeshDestruction( *this );
    }
}

void MeshImpl::print( std::ostream& ) const {}

size_t MeshImpl::footprint() const {
    size_t size = sizeof( *this );

    size += metadata_.footprint();
    if ( nodes_ ) size += nodes_->footprint();
    if ( cells_ ) size += cells_->footprint();
    if ( facets_ ) size += facets_->footprint();
    if ( ridges_ ) size += ridges_->footprint();
    if ( peaks_ ) size += peaks_->footprint();
    if ( partition_graph_ ) size += partition_graph_->footprint();
    for ( const auto& polygon : polygons_ ) {
        if ( polygon ) size += polygon->footprint();
    }

    return size;
}

void MeshImpl::createElements() {
    cells_.reset( new HybridElements() );
    facets_.reset( new HybridElements() );
    ridges_.reset( new HybridElements() );
    peaks_.reset( new HybridElements() );
    if ( dimensionality_ == 2 )
        edges_ = facets_;
    else if ( dimensionality_ == 3 )
        edges_ = ridges_;
    else
        throw eckit::Exception( "Invalid Mesh dimensionality", Here() );

    ASSERT( edges_.owners() == 2 );
}

bool MeshImpl::generated() const {
    return !( cells_->size() == 0 && facets_->size() == 0 && ridges_->size() == 0 && peaks_->size() == 0 );
}

void MeshImpl::setProjection( const Projection& projection ) {
    projection_ = projection;
}

void MeshImpl::setGrid( const Grid& grid ) {
    grid_.reset( new Grid( grid ) );
    if ( not projection_ ) projection_ = grid_->projection();
}

idx_t MeshImpl::nb_partitions() const {
    return mpi::comm().size();
}

idx_t MeshImpl::partition() const {
    return mpi::comm().rank();
}

void MeshImpl::cloneToDevice() const {
    if ( nodes_ ) nodes_->cloneToDevice();
    if ( cells_ ) cells_->cloneToDevice();
    if ( facets_ ) facets_->cloneToDevice();
    if ( ridges_ ) ridges_->cloneToDevice();
    if ( peaks_ ) peaks_->cloneToDevice();
}

void MeshImpl::cloneFromDevice() const {
    if ( nodes_ ) nodes_->cloneFromDevice();
    if ( cells_ ) cells_->cloneFromDevice();
    if ( facets_ ) facets_->cloneFromDevice();
    if ( ridges_ ) ridges_->cloneFromDevice();
    if ( peaks_ ) peaks_->cloneFromDevice();
}

void MeshImpl::syncHostDevice() const {
    if ( nodes_ ) nodes_->syncHostDevice();
    if ( cells_ ) cells_->syncHostDevice();
    if ( facets_ ) facets_->syncHostDevice();
    if ( ridges_ ) ridges_->syncHostDevice();
    if ( peaks_ ) peaks_->syncHostDevice();
}

const PartitionGraph& MeshImpl::partitionGraph() const {
    if ( not partition_graph_ ) { partition_graph_.reset( build_partition_graph( *this ) ); }
    return *partition_graph_;
}

PartitionGraph::Neighbours MeshImpl::nearestNeighbourPartitions() const {
    return partitionGraph().nearestNeighbours( partition() );
}

const PartitionPolygon& MeshImpl::polygon( idx_t halo ) const {
    if ( halo >= static_cast<idx_t>( polygons_.size() ) ) { polygons_.resize( halo + 1 ); }
    if ( not polygons_[halo] ) {
        int mesh_halo = 0;
        metadata().get( "halo", mesh_halo );
        if ( halo > mesh_halo ) {
            throw eckit::Exception( "Mesh does not contain a halo of size " + std::to_string( halo ) + ".", Here() );
        }

        polygons_[halo].reset( new PartitionPolygon( *this, halo ) );
    }
    return *polygons_[halo];
}

void MeshImpl::attachObserver( MeshObserver& observer ) const {
    if ( std::find( mesh_observers_.begin(), mesh_observers_.end(), &observer ) == mesh_observers_.end() ) {
        mesh_observers_.push_back( &observer );
    }
}

void MeshImpl::detachObserver( MeshObserver& observer ) const {
    mesh_observers_.erase( std::remove( mesh_observers_.begin(), mesh_observers_.end(), &observer ),
                           mesh_observers_.end() );
}

//----------------------------------------------------------------------------------------------------------------------

}  // namespace detail
}  // namespace mesh
}  // namespace atlas
