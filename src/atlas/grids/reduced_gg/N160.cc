// TL319

#include "atlas/grids/reduced_gg/Grids.h"

namespace atlas {
namespace grids {
namespace reduced_gg {

N160::regist N160_builders;

void N160::construct()
{
  int N=160;
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
     96,
    108,
    120,
    120,
    125,
    128,
    135,
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
    225,
    225,
    240,
    240,
    243,
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
    375,
    375,
    375,
    384,
    384,
    400,
    400,
    400,
    405,
    432,
    432,
    432,
    432,
    432,
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
    500,
    500,
    500,
    500,
    500,
    512,
    512,
    540,
    540,
    540,
    540,
    540,
    540,
    540,
    540,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640
  };
  double lat[] = {
    89.5700895506066530,
    89.0131761310220639,
    88.4529738367130705,
    87.8920284453444225,
    87.3308011797376338,
    86.7694375145276240,
    86.2079976214231181,
    85.6465108479528823,
    85.0849932009119101,
    84.5234541489144391,
    83.9618996497181058,
    83.4003336387369956,
    82.8387588197095397,
    82.2771771114337724,
    81.7155899132664700,
    81.1539982697129716,
    80.5924029761777518,
    80.0308046490315235,
    79.4692037732916674,
    78.9076007358380025,
    78.3459958490356172,
    77.7843893678486609,
    77.2227815024451729,
    76.6611724276204853,
    76.0995622899381203,
    75.5379512132081317,
    74.9763393027374576,
    74.4147266486620396,
    73.8531133285838308,
    73.2914994096763337,
    72.7298849503795424,
    72.1682700017747720,
    71.6066546087075864,
    71.0450388107113611,
    70.4834226427713162,
    69.9218061359604803,
    69.3601893179717308,
    68.7985722135654356,
    68.2369548449477605,
    67.6753372320917208,
    67.1137193930113654,
    66.5521013439961706,
    65.9904830998127636,
    65.4288646738789339,
    64.8672460784143112,
    64.3056273245713186,
    63.7440084225492356,
    63.1823893816941080,
    62.6207702105861514,
    62.0591509171167885,
    61.4975315085564702,
    60.9359119916146383,
    60.3742923724930307,
    59.8126726569327829,
    59.2510528502565776,
    58.6894329574061189,
    58.1278129829758115,
    57.5661929312427247,
    57.0045728061936146,
    56.4429526115493161,
    55.8813323507866215,
    55.3197120271579337,
    54.7580916437093066,
    54.1964712032965608,
    53.6348507085999913,
    53.0732301621377403,
    52.5116095662779685,
    51.9499889232498901,
    51.3883682351539619,
    50.8267475039710490,
    50.2651267315709518,
    49.7035059197201008,
    49.1418850700887262,
    48.5802641842574445,
    48.0186432637230496,
    47.4570223099043460,
    46.8954013241470520,
    46.3337803077285528,
    45.7721592618623276,
    45.2105381877018360,
    44.6489170863444329,
    44.0872959588346163,
    43.5256748061674017,
    42.9640536292912003,
    42.4024324291106112,
    41.8408112064890005,
    41.2791899622508893,
    40.7175686971841699,
    40.1559474120422166,
    39.5943261075458111,
    39.0327047843849400,
    38.4710834432205573,
    37.9094620846860337,
    37.3478407093888478,
    36.7862193179117796,
    36.2245979108143032,
    35.6629764886338734,
    35.1013550518868982,
    34.5397336010700613,
    33.9781121366611174,
    33.4164906591199866,
    32.8548691688896213,
    32.2932476663967805,
    31.7316261520529608,
    31.1700046262550750,
    30.6083830893861624,
    30.0467615418160641,
    29.4851399839021155,
    28.9235184159897010,
    28.3618968384127648,
    27.8002752514945080,
    27.2386536555477434,
    26.6770320508754857,
    26.1154104377713452,
    25.5537888165200364,
    24.9921671873976941,
    24.4305455506723703,
    23.8689239066043370,
    23.3073022554465155,
    22.7456805974447356,
    22.1840589328381022,
    21.6224372618593002,
    21.0608155847349607,
    20.4991939016857643,
    19.9375722129269057,
    19.3759505186682652,
    18.8143288191146176,
    18.2527071144659168,
    17.6910854049175512,
    17.1294636906605113,
    16.5678419718816130,
    16.0062202487637038,
    15.4445985214858421,
    14.8829767902235091,
    14.3213550551487625,
    13.7597333164304203,
    13.1981115742342219,
    12.6364898287229899,
    12.0748680800568149,
    11.5132463283931212,
    10.9516245738869387,
    10.3900028166909522,
     9.8283810569556174,
     9.2667592948293880,
     8.7051375304587904,
     8.1435157639885709,
     7.5818939955617637,
     7.0202722253198635,
     6.4586504534029681,
     5.8970286799498162,
     5.3354069050979689,
     4.7737851289838753,
     4.2121633517430244,
     3.6505415735100075,
     3.0889197944186586,
     2.5272980146021449,
     1.9656762341930802,
     1.4040544533236243,
     0.8424326721255532,
     0.2808108907304023
  };
  setup_lat_hemisphere(N,lon,lat,DEG);
}

}
}
}
