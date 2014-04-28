// (C) Copyright 1996-2014 ECMWF.

#include "atlas/meshgen/RGG.hpp"

namespace atlas {
namespace meshgen {
  
T255::T255()
{
  int nlat=128;
  int lon[] = {
     18,
     25,
     36,
     40,
     45,
     50,
     60,
     64,
     72,
     72,
     80,
     90,
     90,
    100,
    108,
    120,
    120,
    125,
    128,
    144,
    144,
    150,
    160,
    160,
    180,
    180,
    180,
    192,
    192,
    200,
    216,
    216,
    216,
    225,
    240,
    240,
    240,
    250,
    250,
    256,
    270,
    270,
    288,
    288,
    288,
    300,
    300,
    320,
    320,
    320,
    320,
    324,
    360,
    360,
    360,
    360,
    360,
    360,
    360,
    375,
    375,
    375,
    375,
    384,
    384,
    400,
    400,
    400,
    400,
    405,
    432,
    432,
    432,
    432,
    432,
    432,
    432,
    450,
    450,
    450,
    450,
    450,
    480,
    480,
    480,
    480,
    480,
    480,
    480,
    480,
    480,
    480,
    486,
    486,
    486,
    500,
    500,
    500,
    500,
    500,
    500,
    500,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512
  };
  double colat[] = {
    9.375532299023255E-003,
    2.152075873016308E-002,
    3.373770928673819E-002,
    4.597086538139387E-002,
    5.821016861805220E-002,
    7.045244647030013E-002,
    8.269638670690518E-002,
    9.494134931359999E-002,
    0.107186985212239,    
    0.119433087910006,    
    0.131679527479220,    
    0.143926218095675,    
    0.156173100795680,    
    0.168420133733602,    
    0.180667286391840,    
    0.192914535991425,    
    0.205161865185808,    
    0.217409260532824,    
    0.229656711454872,    
    0.241904209514547,    
    0.254151747899464,    
    0.266399321049043,    
    0.278646924379620,    
    0.290894554078942,    
    0.303142206950432,    
    0.315389880293725,    
    0.327637571811968,    
    0.339885279539157,    
    0.352133001782630,    
    0.364380737077142,    
    0.376628484147911,    
    0.388876241880626,    
    0.401124009296968,    
    0.413371785534457,    
    0.425619569829802,    
    0.437867361505021,    
    0.450115159955845,    
    0.462362964641954,    
    0.474610775078726,    
    0.486858590830231,    
    0.499106411503263,    
    0.511354236742215,    
    0.523602066224690,    
    0.535849899657697,    
    0.548097736774374,    
    0.560345577331124,    
    0.572593421105132,    
    0.584841267892186,    
    0.597089117504766,    
    0.609336969770370,    
    0.621584824530031,    
    0.633832681637010,    
    0.646080540955634,    
    0.658328402360266,    
    0.670576265734389,    
    0.682824130969786,    
    0.695071997965809,    
    0.707319866628720,    
    0.719567736871102,    
    0.731815608611334,    
    0.744063481773106,    
    0.756311356284991,    
    0.768559232080054,    
    0.780807109095501,    
    0.793054987272354,    
    0.805302866555161,    
    0.817550746891731,    
    0.829798628232892,    
    0.842046510532271,    
    0.854294393746088,    
    0.866542277832977,    
    0.878790162753810,    
    0.891038048471547,    
    0.903285934951092,    
    0.915533822159157,    
    0.927781710064146,    
    0.940029598636042,    
    0.952277487846303,    
    0.964525377667764,    
    0.976773268074556,    
    0.989021159042016,    
    1.00126905054662,    
    1.01351694256589,    
    1.02576483507838,    
    1.03801272806355,    
    1.05026062150175,    
    1.06250851537416,    
    1.07475640966274,    
    1.08700430435017,    
    1.09925219941985,    
    1.11150009485579,    
    1.12374799064263,    
    1.13599588676559,    
    1.14824378321043,    
    1.16049167996341,    
    1.17273957701129,    
    1.18498747434127,    
    1.19723537194099,    
    1.20948326979848,    
    1.22173116790217,    
    1.23397906624083,    
    1.24622696480358,    
    1.25847486357984,    
    1.27072276255937,    
    1.28297066173217,    
    1.29521856108853,    
    1.30746646061897,    
    1.31971436031426,    
    1.33196226016539,    
    1.34421016016355,    
    1.35645806030012,    
    1.36870596056666,    
    1.38095386095490,    
    1.39320176145672,    
    1.40544966206416,    
    1.41769756276937,    
    1.42994546356464,    
    1.44219336444236,    
    1.45444126539504,    
    1.46668916641525,    
    1.47893706749568,    
    1.49118496862906,    
    1.50343286980821,    
    1.51568077102600,    
    1.52792867227534,    
    1.54017657354917,    
    1.55242447484047,    
    1.56467237614226 
  }; 
  lat_.resize(2*nlat);
  lon_.resize(2*nlat);
  std::copy( lon, lon+nlat, lon_.begin() );
  std::reverse_copy( lon, lon+nlat, lon_.begin()+nlat );
  std::copy( colat, colat+nlat, lat_.begin() );
  std::reverse_copy( colat, colat+nlat, lat_.begin()+nlat );
  for (int i=0; i<nlat; ++i)
    lat_[i]=M_PI/2.-lat_[i];
  for (int i=nlat; i<2*nlat; ++i)
    lat_[i]=-M_PI/2.+lat_[i];
}

} // namespace meshgen
} // namespace atlas

