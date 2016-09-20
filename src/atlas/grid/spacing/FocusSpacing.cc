#include "atlas/grid/spacing/FocusSpacing.h"
#include <cmath>

namespace atlas {
namespace grid {

FocusSpacing::FocusSpacing(const eckit::Parametrisation& params) {
	// no parameters for uniform spacing!
	if( ! params.get("focus_factor",focus_factor_) )
    throw eckit::BadParameter("focus_factor missing in Params",Here());
};

std::vector<double> FocusSpacing::generate(double xmin, double xmax, size_t N) {
	// create vector of points, unevenly spaced between xmin and xmax
	std::vector<double> x(N);
	double xx;
	for (int i=1;i<N-1;i++) {
		xx=(2*i-int(N-1))/double(N-1);		// between -1 and 1;
		x[i]=(xmin+xmax)/2+(xmax-xmin)/2*atan(tan(M_PI*xx/2)/focus_factor_)*2*M_1_PI;
		
	}
	x[0]=xmin;
	x[N-1]=xmax;
	
	return x;
};

register_BuilderT1(Spacing,FocusSpacing,FocusSpacing::className());

}  // namespace grid
}  // namespace atlas

