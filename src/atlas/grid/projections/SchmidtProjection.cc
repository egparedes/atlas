#include "atlas/grid/projections/SchmidtProjection.h"
#include <cmath>

namespace atlas {
namespace grid {

// constructor
SchmidtProjection::SchmidtProjection(const eckit::Parametrisation& params) {
	if( ! params.get("stretching_factor",c_) )
    throw eckit::BadParameter("stretching_factor missing in Params",Here());
}

eckit::geometry::LLPoint2 SchmidtProjection::coords2lonlat(eckit::geometry::Point2 xy) {
	double lat=asin(cos(2*atan(1/c_*tan(acos(sin(xy[eckit::geometry::YY]))/2))));
	
	return eckit::geometry::LLPoint2(xy[eckit::geometry::XX],lat);
}

eckit::geometry::Point2 SchmidtProjection::lonlat2coords(eckit::geometry::LLPoint2 ll) {

	double lat2=asin(cos(2*atan(c_*tan(acos(sin(ll.lat()))/2))));

	return eckit::geometry::Point2(ll.lon(),lat2);
}

register_BuilderT1(Projection,SchmidtProjection,SchmidtProjection::className());

}  // namespace grid
}  // namespace atlas

