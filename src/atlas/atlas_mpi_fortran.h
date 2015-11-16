! (C) Copyright 1996-2014 ECMWF.
!
! This software is licensed under the terms of the Apache Licence Version 2.0
! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
! In applying this licence, ECMWF does not waive the privileges and immunities
! granted to it by virtue of its status as an intergovernmental organisation nor
! does it submit to any jurisdiction.

#ifndef atlas_mpi_fortran_h
#define atlas_mpi_fortran_h

#include "atlas/atlas_defines_fortran.h"

#ifdef ATLAS_HAVE_MPI
use mpi
#else
use mpistubs
#endif

#endif