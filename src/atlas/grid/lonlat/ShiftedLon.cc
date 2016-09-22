/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "atlas/grid/lonlat/ShiftedLon.h"


namespace atlas {
namespace grid {
namespace lonlat {


register_BuilderT1(Grid,ShiftedLon,ShiftedLon::grid_type_str());


std::string ShiftedLon::grid_type_str() {
    return "shifted_lon";
}


std::string ShiftedLon::className() {
    return "atlas.grid.lonlat.ShiftedLon";
}


void ShiftedLon::set_typeinfo() {
    std::stringstream s;
    if( N() ) {
        s << "Slon" << N();
    } else {
        s << "Slon" << nlon() << "x" << nlat();
    }
    shortName_ = s.str();
    grid_type_ = grid_type_str();
}


ShiftedLon::ShiftedLon(const eckit::Parametrisation& p) :
    LonLat(Shift::LON,domain::Domain::makeGlobal()) {
    setup(p);
}


ShiftedLon::ShiftedLon(const size_t N, const domain::Domain& dom) :
    LonLat(Shift::LON, dom) {
    LonLat::setup(N, dom);
}


ShiftedLon::ShiftedLon(const size_t nlon, const size_t nlat, const domain::Domain& dom) :
    LonLat(Shift::LON, dom) {
    LonLat::setup(nlon, nlat, dom);
}


void ShiftedLon::setup(const eckit::Parametrisation& p) {
    size_t nlon, nlat, N(0);

    //std::vector<double> p_domain(4);
    //if( p.get("domain", p_domain) )
    //{
    //  domain_ = domain::Domain(p_domain[0],p_domain[1],p_domain[2],p_domain[3]);
    //}
    
    std::string domainType;
    if( p.get("domainType",domainType) )
    {
      domain_ = *domain::Domain::create(p);
    }
    else
    {
      domain_ = domain::Domain::makeGlobal();
    }

    if (p.get("N",N)) {
        LonLat::setup(N, domain_);
    }
    else if (p.get("nlon",nlon) && p.get("nlat",nlat)) {
        LonLat::setup(nlon, nlat, domain_);
    }
    else {
        throw eckit::BadParameter("Params (nlon,nlat) or N missing",Here());
    }
}


eckit::Properties ShiftedLon::spec() const {
    eckit::Properties grid_spec;
    grid_spec.set("grid_type",  gridType());
    grid_spec.set("short_name", shortName());
    grid_spec.set("N",    N());
    grid_spec.set("nlon", nlon());
    grid_spec.set("nlat", nlat());
    grid_spec.set("domain", domain_spec(domain_) );
    return grid_spec;
}


extern "C" {


    Structured* atlas__grid__lonlat__ShiftedLon(size_t nlon, size_t nlat) {
        return new ShiftedLon(nlon,nlat);
    }


}


}  // namespace lonlat
}  // namespace grid
}  // namespace atlas

