/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#pragma once

#include <vector>
#include <string>

//-----------------------------------------------------------------------------------------------------------

namespace eckit { class Configuration; }
namespace eckit { class CodeLocation; }

namespace atlas {
namespace runtime {
namespace timer {

class CallStack;

class Timings {
public:
    using Configuration = eckit::Configuration;
    using CodeLocation = eckit::CodeLocation;
    using Identifier = size_t;
    using Labels = std::vector<std::string>;

public: // static methods

    static Identifier add( const CodeLocation&, const CallStack&, const std::string& title, const Labels& );

    static void update( const Identifier& id, double seconds );

    static std::string report();

    static std::string report( const Configuration& );

};


} // namespace timer
} // namespace runtime
} // namespace atlas

