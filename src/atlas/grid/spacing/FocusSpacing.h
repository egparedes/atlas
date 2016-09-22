#ifndef atlas_FocusSpacing_H
#define atlas_FocusSpacing_H

#include "atlas/grid/spacing/Spacing.h"

namespace atlas {
namespace grid {
namespace spacing {

class FocusSpacing: public Spacing {


	public:
		
		// constructor
		FocusSpacing(const eckit::Parametrisation& p);
		
		// class name
		static std::string className() { return "atlas.FocusSpacing"; } 
		static std::string spacing_type_str() {return "focus";}

		
		void generate(double xmin, double xmax, size_t N, std::vector<double> &x) const;
	
	private:
		double focus_factor_;
};

}  // namespace spacing
}  // namespace grid
}  // namespace atlas


#endif
