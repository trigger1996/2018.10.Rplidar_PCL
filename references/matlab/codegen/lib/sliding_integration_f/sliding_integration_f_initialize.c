/*
 * File: sliding_integration_f_initialize.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "sliding_integration_f_initialize.h"
#include "sliding_integration_f_data.h"

/* Named Constants */
#define b_arr_len                      (512.0)

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void sliding_integration_f_initialize(void)
{
  static const double dv1[512] = { 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
    0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2,
    0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.33,
    0.34, 0.35000000000000003, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41000000000000003,
    0.42, 0.43, 0.44, 0.45, 0.46, 0.47000000000000003, 0.48, 0.49, 0.5, 0.51,
    0.52, 0.53, 0.54, 0.55, 0.56, 0.57000000000000006, 0.58, 0.59, 0.6, 0.61,
    0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69000000000000006,
    0.70000000000000007, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79,
    0.8, 0.81, 0.82000000000000006, 0.83000000000000007, 0.84, 0.85, 0.86, 0.87,
    0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94000000000000006, 0.95000000000000007,
    0.96, 0.97, 0.98, 0.99, 1.0, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08,
    1.09, 1.1, 1.11, 1.12, 1.1300000000000001, 1.1400000000000001,
    1.1500000000000001, 1.16, 1.17, 1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24,
    1.25, 1.26, 1.27, 1.28, 1.29, 1.3, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37,
    1.3800000000000001, 1.3900000000000001, 1.4000000000000001, 1.41, 1.42, 1.43,
    1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56,
    1.57, 1.58, 1.59, 1.6, 1.61, 1.62, 1.6300000000000001, 1.6400000000000001,
    1.6500000000000001, 1.6600000000000001, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72,
    1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84, 1.85,
    1.86, 1.87, 1.8800000000000001, 1.8900000000000001, 1.9000000000000001,
    1.9100000000000001, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2.0,
    2.0100000000000002, 2.02, 2.0300000000000002, 2.04, 2.05, 2.06, 2.07, 2.08,
    2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19, 2.2, 2.21,
    2.22, 2.23, 2.24, 2.25, 2.2600000000000002, 2.27, 2.2800000000000002, 2.29,
    2.3000000000000003, 2.31, 2.32, 2.33, 2.34, 2.35, 2.36, 2.37, 2.38, 2.39,
    2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47, 2.48, 2.49, 2.5,
    2.5100000000000002, 2.52, 2.5300000000000002, 2.54, 2.5500000000000003, 2.56,
    2.5700000000000003, 2.58, 2.5900000000000003, 2.6, 2.6100000000000003, 2.62,
    2.6300000000000003, 2.64, 2.6500000000000004, 2.66, 2.6700000000000004, 2.68,
    2.6900000000000004, 2.7, 2.7100000000000004, 2.72, 2.7300000000000004, 2.74,
    2.7500000000000004, 2.7600000000000002, 2.7700000000000005,
    2.7800000000000002, 2.7900000000000005, 2.8000000000000003, 2.81,
    2.8200000000000003, 2.83, 2.8400000000000003, 2.85, 2.8600000000000003, 2.87,
    2.8800000000000003, 2.89, 2.9000000000000004, 2.91, 2.9200000000000004, 2.93,
    2.9400000000000004, 2.95, 2.9600000000000004, 2.97, 2.9800000000000004, 2.99,
    3.0000000000000004, 3.0100000000000002, 3.0200000000000005,
    3.0300000000000002, 3.0400000000000005, 3.0500000000000003,
    3.0600000000000005, 3.0700000000000003, 3.08, 3.0900000000000003, 3.1,
    3.1100000000000003, 3.12, 3.1300000000000003, 3.1400000000000006,
    3.1500000000000004, 3.16, 3.1700000000000004, 3.1800000000000006,
    3.1900000000000004, 3.2, 3.21, 3.22, 3.2300000000000004, 3.24, 3.25,
    3.2600000000000002, 3.2700000000000005, 3.2800000000000002, 3.29,
    3.3000000000000003, 3.3100000000000005, 3.3200000000000003, 3.33,
    3.3400000000000003, 3.3500000000000005, 3.3600000000000003, 3.37,
    3.3800000000000003, 3.3900000000000006, 3.4000000000000004, 3.41,
    3.4200000000000004, 3.4300000000000006, 3.4400000000000004, 3.45, 3.46, 3.47,
    3.4800000000000004, 3.49, 3.5, 3.5100000000000002, 3.5200000000000005,
    3.5300000000000002, 3.54, 3.5500000000000003, 3.5600000000000005,
    3.5700000000000003, 3.58, 3.5900000000000003, 3.6000000000000005,
    3.6100000000000003, 3.62, 3.6300000000000003, 3.6400000000000006,
    3.6500000000000004, 3.66, 3.6700000000000004, 3.6800000000000006,
    3.6900000000000004, 3.7, 3.71, 3.72, 3.7300000000000004, 3.74, 3.75,
    3.7600000000000002, 3.7700000000000005, 3.7800000000000002, 3.79,
    3.8000000000000003, 3.8100000000000005, 3.8200000000000003, 3.83,
    3.8400000000000003, 3.8500000000000005, 3.8600000000000003, 3.87,
    3.8800000000000003, 3.8900000000000006, 3.9000000000000004, 3.91,
    3.9200000000000004, 3.9300000000000006, 3.9400000000000004, 3.95, 3.96, 3.97,
    3.9800000000000004, 3.99, 4.0, 4.01, 4.0200000000000005, 4.03, 4.04,
    4.0500000000000007, 4.0600000000000005, 4.07, 4.08, 4.09, 4.1000000000000005,
    4.11, 4.12, 4.1300000000000008, 4.1400000000000006, 4.15, 4.16, 4.17,
    4.1800000000000006, 4.19, 4.2, 4.21, 4.2200000000000006, 4.23, 4.24, 4.25,
    4.2600000000000007, 4.2700000000000005, 4.28, 4.29, 4.3000000000000007,
    4.3100000000000005, 4.32, 4.33, 4.34, 4.3500000000000005, 4.36, 4.37,
    4.3800000000000008, 4.3900000000000006, 4.4, 4.41, 4.42, 4.4300000000000006,
    4.44, 4.45, 4.46, 4.4700000000000006, 4.48, 4.49, 4.5, 4.5100000000000007,
    4.5200000000000005, 4.53, 4.54, 4.5500000000000007, 4.5600000000000005, 4.57,
    4.58, 4.59, 4.6000000000000005, 4.61, 4.62, 4.6300000000000008,
    4.6400000000000006, 4.65, 4.66, 4.67, 4.6800000000000006, 4.69, 4.7, 4.71,
    4.7200000000000006, 4.73, 4.74, 4.75, 4.7600000000000007, 4.7700000000000005,
    4.78, 4.79, 4.8000000000000007, 4.8100000000000005, 4.82, 4.83, 4.84,
    4.8500000000000005, 4.86, 4.87, 4.88, 4.8900000000000006, 4.9, 4.91, 4.92,
    4.9300000000000006, 4.94, 4.95, 4.96, 4.9700000000000006, 4.98, 4.99, 5.0,
    5.0100000000000007, 5.0200000000000005, 5.03, 5.04, 5.0500000000000007,
    5.0600000000000005, 5.07, 5.08, 5.0900000000000007, 5.1000000000000005, 5.11
  };

  static const double dv2[512] = { -0.046914667250777073, -0.048313396043756826,
    -0.048995613765373369, -0.048844629651512372, -0.047989015814280028,
    -0.046309665336190728, -0.043983425829341824, -0.040877418163637713,
    -0.037238754390591322, -0.032889235426662944, -0.028199293278794141,
    -0.022846874032430076, -0.017561079728340756, -0.011798976673589784,
    -0.0059431291881354639, -0.00012358905280557275, 0.0055199042855778521,
    0.010838232690876137, 0.015680572396922443, 0.019889874559996946,
    0.02332282520323338, 0.025830907417605485, 0.027291684570065672,
    0.027585446781869749, 0.026635060602237436, 0.02437166160948856,
    0.020776586020568193, 0.015848543861031239, 0.0096197807128385934,
    0.00215964055015635, -0.0064319737920837394, -0.016021227173213606,
    -0.026476300314285172, -0.037612113665550541, -0.049259624407152126,
    -0.061202197548411934, -0.073249641178423017, -0.085170993484109753,
    -0.096762691993002831, -0.1077954123827676, -0.11805661548335947,
    -0.12733181526208118, -0.13540887570727916, -0.14209902067299676,
    -0.14720469046239493, -0.15057280644438625, -0.15204167949533728,
    -0.15150279033898773, -0.14884968519296463, -0.14402580934358919,
    -0.13698790221751958, -0.12773613640190612, -0.11629032219890302,
    -0.102708823115071, -0.087070760671961664, -0.069487905846815579,
    -0.05008904751544202, -0.029028438761189268, -0.0064668458149661351,
    0.017414258266928884, 0.042436150012238313, 0.068405652942160652,
    0.095143079395562408, 0.12245810092931052, 0.15017882793256263,
    0.17813010153260841, 0.20615522448666154, 0.23410272069095306,
    0.26182938129456268, 0.289211782453099, 0.316133644734394,
    0.34249958453804297, 0.36821753533591695, 0.39321863999508916,
    0.41743700240492176, 0.4408263029368793, 0.46334396521839516,
    0.4849622755157672, 0.505658354428879, 0.52542034054542719,
    0.54424177137474439, 0.56212402321140709, 0.57907252912178,
    0.59509799113255246, 0.6102135281429879, 0.62443637665327367,
    0.63778534814909971, 0.65028359313104955, 0.66195580034500767,
    0.67283107184069446, 0.682940157942898, 0.692317881966624,
    0.70100082025626043, 0.70902849178759664, 0.71644147529263724,
    0.72328166457858545, 0.72959115693588861, 0.73541228043259244,
    0.74078701409265846, 0.745756200817846, 0.75035910086410107,
    0.75463162301729092, 0.758606361560095, 0.76231060163409126,
    0.76576741338385634, 0.76899430788875, 0.77200530623065911,
    0.77481004376791407, 0.77741533280383712, 0.77982570744535917,
    0.78204347518445783, 0.78406836338812513, 0.78589744597375688,
    0.78752490129800834, 0.78894295915995194, 0.7901409428026317,
    0.79110882058545817, 0.79183398402091254, 0.79230844127811517,
    0.792520622330436, 0.79246434905976881, 0.79212993761175321,
    0.79151404053799435, 0.79060899907159365, 0.789402987173462,
    0.78789165330773492, 0.786066282149041, 0.78393056788187165,
    0.78147956439439226, 0.77873401383882379, 0.775687296031063,
    0.77238241681314723, 0.768833471091159, 0.765107536053941,
    0.76124583044536642, 0.75734298212537932, 0.75347829477950945,
    0.749771762669988, 0.7463427615738405, 0.74332561098367089,
    0.74086942359682029, 0.73910759963501182, 0.73819761464987077,
    0.73825764611088229, 0.73942496795557489, 0.74178865441395836,
    0.74544089746226971, 0.7504299492035601, 0.7567907298035923,
    0.76452228236766606, 0.773598056639414, 0.7839619971080759,
    0.79554247328767125, 0.80822855897707235, 0.82190667303617659,
    0.83641557672247335, 0.85161290187319261, 0.86729899608642846,
    0.88329707788767053, 0.8993853593287614, 0.91539168594689613,
    0.93108809621650734, 0.94628919771744013, 0.9607777338871788,
    0.97436532422157318, 0.98685536467149859, 0.99806944321544921,
    1.0078391041940944, 1.0160028687139413, 1.0224276507874785,
    1.026980597627642, 1.0295697410415974, 1.0301003058687896,
    1.0285255005833616, 1.0247954381776476, 1.0189099580411614,
    1.0108695030345738, 1.0007204681928665, 0.98851507622392565,
    0.97434440577130954, 0.9583096580640561, 0.94054100810063268,
    0.92118183501371054, 0.90039254255951484, 0.87834891815350635,
    0.85523082227181, 0.8312338858213284, 0.80654631867512439,
    0.78137040277782133, 0.75589118679466261, 0.73030674006171847,
    0.70478841620780708, 0.67952088670071109, 0.654653521089309,
    0.63034817896063144, 0.60672757960360035, 0.58392406212897674,
    0.56203246191797629, 0.541150534362606, 0.52134604210890445,
    0.50267898303976033, 0.48519037860302416, 0.46890459602502554,
    0.45383507677836105, 0.43997760048767542, 0.42731999455227787,
    0.41583664420561117, 0.40549519195678974, 0.3962539089753816,
    0.3880660337692915, 0.38087784270459546, 0.37463291831535533,
    0.36927037562072995, 0.36472848586640283, 0.36094435588701856,
    0.35785487564265483, 0.35539922685594394, 0.3535155317062264,
    0.35214706682925506, 0.35123502486747687, 0.35072769592260361,
    0.35057116730092, 0.35071952239413307, 0.35112562397059593,
    0.35174957191423056, 0.35255216056050809, 0.35349938007325987,
    0.35455972673830688, 0.35570455857465449, 0.35690851994570211,
    0.3581478052178379, 0.35940164309606093, 0.3606504647851303,
    0.36187665639534011, 0.36306349456775633, 0.3641951378592222,
    0.36525636127267913, 0.36623206326656887, 0.36710768945780259,
    0.36786849287540863, 0.36850006555221643, 0.36898771053380625,
    0.36931669814243667, 0.36947184329644, 0.36943770337447146,
    0.36919844086957671, 0.36873814201969762, 0.36804096750035753,
    0.36709146752262684, 0.365874727777249, 0.36437681471551653,
    0.36258428355220773, 0.36048514845456864, 0.35806808213162417,
    0.35532360701176746, 0.35224312799543178, 0.34882031327902968,
    0.34505018022801603, 0.34093127559666947, 0.33646359880007692,
    0.33165156005586549, 0.32650105062968282, 0.32102348128435187,
    0.31523084748157254, 0.30914004971578357, 0.30276848809330265,
    0.29613706064726764, 0.28926651021574, 0.28218022046039648,
    0.27489968179950774, 0.26744853750010794, 0.259846964301094,
    0.25211722444295392, 0.24427657711337702, 0.23634502866718443,
    0.2283365892681134, 0.22026932113154996, 0.21215487810134392,
    0.20401037380335285, 0.19584709003397249, 0.18768116771171545,
    0.17952510476343908, 0.17139382483154453, 0.16330132995930136,
    0.15526186035974088, 0.14729009724768632, 0.13940113197902726,
    0.13160853747808987, 0.1239293853356635, 0.11637417210224799,
    0.10896204998972669, 0.10169865568220765, 0.094603872767519581,
    0.087677152494542554, 0.0809363927743863, 0.074375202015528386,
    0.068006086034719582, 0.061818264457458416, 0.055815379518863006,
    0.049983820707328985, 0.044316717960905749, 0.038799540880981809,
    0.03341638296303967, 0.028153872874112862, 0.022989268698046961,
    0.017911693778989712, 0.012894689631032352, 0.0079306978394864669,
    0.0029940136125503058, -0.0019183203865184018, -0.00682879321355484,
    -0.011734351817837108, -0.016655922377742327, -0.021583749428828958,
    -0.026532237918011292, -0.031484375314423718, -0.036446819010869991,
    -0.041395042185356057, -0.046322695256959479, -0.0511985869839614,
    -0.055999834783641178, -0.060689463409271116, -0.065231077839351115,
    -0.0695828204290157, -0.073697738789453737, -0.07753063318560488,
    -0.081030814009638741, -0.084152418069592561, -0.086846177374564626,
    -0.089070191627056039, -0.0907818835479074, -0.091947384313362912,
    -0.092535079239755347, -0.092521740186249035, -0.091889286709748386,
    -0.0906276297798651, -0.088734551858812849, -0.086215144029398533,
    -0.083084186900757473, -0.07936355922492655, -0.075083668084751365,
    -0.070283087487866075, -0.065006608052009113, -0.0593078411959308,
    -0.053243118500389486, -0.04687852644397271, -0.040279677587016713,
    -0.033522897090375259, -0.026679987364992677, -0.019834533107405697,
    -0.013063809546540198, -0.0064549540331337862, -8.7849610824856927E-5,
    0.0059498007443517451, 0.011576985560877294, 0.016708676482069876,
    0.021266750846518887, 0.025172756014101842, 0.028355447585862753,
    0.030746957803136594, 0.032289942765921377, 0.03293100058141802,
    0.032629875033384111, 0.031350864117911305, 0.029074583713566776,
    0.025785985536520714, 0.021490045693744648, 0.016194762864393808,
    0.0099282691061416441, 0.0027221532951227229, -0.00536992212137059,
    -0.01429416278270974, -0.023974752024175212, -0.034338390073470428,
    -0.045292590905791713, -0.056749007207213806, -0.068604685965222165,
    -0.080762452945122631, -0.093116063387151, -0.10556655842643746,
    -0.11801169302633314, -0.13035746995231534, -0.14250974167982178,
    -0.15438498322050975, -0.16590097554943062, -0.17698900610242516,
    -0.18758372515877841, -0.19763480414688714, -0.20709645422210779,
    -0.21593826779635694, -0.2241344421943538, -0.2316737263624824,
    -0.23854972017717752, -0.24476873483580877, -0.25034124670316327,
    -0.25528848801280635, -0.25963415639856424, -0.26341059489514723,
    -0.26665061832547543, -0.26939370870428148, -0.27167789592797048,
    -0.2735457990943409, -0.27503682525540885, -0.27619320293109434,
    -0.27705263821301646, -0.27765415646906738, -0.2780314210850619,
    -0.27821826370819797, -0.27824238532226442, -0.2781312316829711,
    -0.27790590883149563, -0.27758682188442524, -0.27718834109557211,
    -0.276723958072413, -0.276201864727773, -0.27562962337823338,
    -0.27501080131344691, -0.27434880964509495, -0.27364414011337451,
    -0.27289761178672284, -0.27210742964063334, -0.27127268864861642,
    -0.27038989448868489, -0.26945700432920017, -0.26846941840483751,
    -0.267424378330278, -0.26631665185924647, -0.26514323654214178,
    -0.2638984503048431, -0.26257932955595853, -0.26118014010022617,
    -0.25969866174929934, -0.25813031029952993, -0.25647523651532766,
    -0.25473148285965685, -0.25290276679529267, -0.2509905023855587,
    -0.24900175606149152, -0.24694080066697852, -0.24481631725396633,
    -0.24263353872391435, -0.24040025294487694, -0.23812025155046365,
    -0.2357984904352384, -0.2334357131983209, -0.23103309670820002,
    -0.22858778235202795, -0.22609742082110854, -0.22355533049935911,
    -0.22095701004183108, -0.21829298139812392, -0.21555945360825662,
    -0.2127470465481987, -0.20985650528929872, -0.20688151845603908,
    -0.20382967930274107, -0.20070033434899981, -0.19750942268196742,
    -0.19426390561535728, -0.19098683275634182, -0.18769450392568052,
    -0.18441592134411255, -0.18117431920861246, -0.1780020582669076,
    -0.17492666632821655, -0.17198056295107247, -0.16919088775873728,
    -0.16658719382299481, -0.16419193717031352, -0.16202907066946881,
    -0.16011317275349385, -0.15846038001912835, -0.15707582024043587,
    -0.15596576115697802, -0.155126542622616, -0.15455356575891768,
    -0.15423487353414389, -0.1541549467463908, -0.15429444159418015,
    -0.15462831995269258, -0.15513090881520206, -0.15577020897028251,
    -0.15651566479025966, -0.15733074203881808, -0.15818187618341667,
    -0.15902990692874139, -0.15984068308906671, -0.16057337386808096,
    -0.16119643507185077, -0.16166778394987019, -0.16196104603974765,
    -0.16203429086675991, -0.16186775058955805, -0.16142310714193173,
    -0.16068715106191456, -0.15962986101955651, -0.15824349782933045,
    -0.15651014480034015, -0.15442713952579179, -0.15199030594337862,
    -0.1492026516098004, -0.14607379262408163, -0.14261300613008038,
    -0.13884227606147578, -0.13477749108370163, -0.13045038084313246,
    -0.12588328425234224, -0.12111456786029877, -0.11617268422430976,
    -0.11109978253320593, -0.10593016974723987, -0.10070740777438968 };

  static const double dv3[512] = { -1.5079864932108995, -1.4314528129480231,
    -1.3526122156851832, -1.2734953273250054, -1.1944748151582059,
    -1.1168194109324305, -1.0416996455206564, -0.97009979217321352,
    -0.90337771478045426, -0.84250673286953248, -0.788927149503538,
    -0.74350872674366608, -0.70799999865798835, -0.6831010705730165,
    -0.67097508296989972, -0.67171559512301116, -0.68793987225060327,
    -0.71842915695206289, -0.76616500520512987, -0.82821717557258867,
    -0.90705999006339455, -0.99923571875270134, -1.1058534608567405,
    -1.2228636823531074, -1.3487893409176082, -1.4811431953227605,
    -1.6145202277624824, -1.7498181700863444, -1.8794013542982824,
    -2.0046019305779152, -2.1158643121145788, -2.2188140794302647,
    -2.3036218941548459, -2.3745807618349031, -2.4246001408269642,
    -2.4566075919636936, -2.4671479733867163, -2.4560655603513308,
    -2.4245721255370345, -2.3687811749999383, -2.2940810655326436,
    -2.1942681613859909, -2.0770830748263363, -1.9363215292139173,
    -1.7797648600990854, -1.6037843467706583, -1.414492229571402,
    -1.2116721563990802, -0.99963655084300151, -0.78042361759311629,
    -0.55733041161132824, -0.33328162670414962, -0.11123212297350538,
    0.10581072880375278, 0.31507754448155828, 0.51420032194226106,
    0.70049780697336517, 0.87294000513254955, 1.029273150613367,
    1.1692697326107582, 1.2913880045867849, 1.3961344649316461,
    1.4831804427569379, 1.5526128242589254, 1.6057939187456829,
    1.6420002753151228, 1.6643220363183306, 1.6708947675586052,
    1.6652718661845742, 1.6467714621933296, 1.6184249187690594,
    1.5798583832641786, 1.5334199321344091, 1.47969423677729, 1.4200202361485861,
    1.3555336944942415, 1.2868848560965369, 1.2153620223034818,
    1.1413081522602542, 1.0659331306093154, 0.98948983711893712,
    0.91288363100100056, 0.83631295011423024, 0.76032693841960786,
    0.68510818197153278, 0.61102166670620273, 0.53830349111976883,
    0.46729378356000612, 0.39826256813223826, 0.33157455389715185,
    0.26748709891925454, 0.20638087849896228, 0.14847677672598844,
    0.0940592406109708, 0.043262445927721618, -0.0037836085841569615,
    -0.047008801775769778, -0.086371909197573871, -0.12187343695759444,
    -0.15360747748252976, -0.18172937953419238, -0.20657529666394042,
    -0.22845484188647736, -0.24792727878686696, -0.26530635771483752,
    -0.28121146065840336, -0.29577505441221685, -0.30960345660559718,
    -0.32270061797367477, -0.33543550867388106, -0.34793301333846882,
    -0.36045318800854925, -0.37342667818034742, -0.38677080143255477,
    -0.40128027684624118, -0.4163891212891121, -0.43302879422901791,
    -0.45030479751101871, -0.46879766244298959, -0.48812297163963597,
    -0.50809446331405272, -0.52934260022264457, -0.55004249814422412,
    -0.57332165534807722, -0.59583215432651737, -0.621257779569515,
    -0.64449006567920375, -0.67122660099978282, -0.693655514479387,
    -0.71938289018646873, -0.74034517685441792, -0.76138663058571587,
    -0.77659978717403733, -0.78789854415957294, -0.79230526780321586,
    -0.78745482694898628, -0.77434441146389044, -0.74661461405943386,
    -0.7091841698857706, -0.6536226324272697, -0.587011485321894,
    -0.50190920437881414, -0.404888685859138, -0.2921841945706824,
    -0.16833647633170531, -0.033635977366857139, 0.10898621417910863,
    0.25716463642921139, 0.40795527622941485, 0.55944081447204974,
    0.70625034387265451, 0.850179320473993, 0.98301000147215922,
    1.109034073374487, 1.2181436950336091, 1.3166766029392896,
    1.3948272382251543, 1.4581344925719373, 1.4975607628866947,
    1.5205573847231715, 1.5211171398084042, 1.5015319696484997,
    1.4609363984890911, 1.3986684220150898, 1.3170391614826351,
    1.2140142695831422, 1.0939237983168142, 0.95388687924015858,
    0.79917425041285761, 0.62767227091958555, 0.44423154579786417,
    0.2484401548259646, 0.04389685754226446, -0.16780312136585823,
    -0.38452112021661566, -0.60290340218663718, -0.82200291638028311,
    -1.0373842453354283, -1.2487998542157615, -1.4515222475705589,
    -1.6457166029455823, -1.8269446788361909, -1.9956368597053815,
    -2.1480684539633752, -2.2848091227955161, -2.4031717743679484,
    -2.50387555016215, -2.5852466686881193, -2.6482560480980433,
    -2.6919901061654317, -2.7178679482021311, -2.7254383731268086,
    -2.7165311816176159, -2.6912674423244844, -2.6517028257390529,
    -2.5983331434577197, -2.5332895126940511, -2.4574151150018348,
    -2.3726170766638006, -2.2802615095028518, -2.1818302953903763,
    -2.0790704570782936, -1.9731456324262604, -1.8657541341964177,
    -1.7578943326734673, -1.65088861027225, -1.5455901908453635,
    -1.4429381109481438, -1.3436181121942568, -1.2482985732200824,
    -1.1574908464376568, -1.0716088161469868, -0.99096314894230231,
    -0.91572209859739273, -0.84597835885101658, -0.78171432973588084,
    -0.72287658525061627, -0.6693515453412604, -0.62098602184487317,
    -0.57762663593872265, -0.53902692263322638, -0.50497909603296165,
    -0.47516480974737252, -0.44933085688903679, -0.42710002401321828,
    -0.40822222549343029, -0.39232172152614286, -0.37917965583607133,
    -0.36845114981441623, -0.36000090198527962, -0.35351103181056848,
    -0.34890040905574171, -0.34589330359627, -0.34450858297703385,
    -0.34450950783759193, -0.34601085654260394, -0.34879944875114283,
    -0.35306882133164474, -0.3585776432626645, -0.36559654142529063,
    -0.37385881205948268, -0.38368358760433924, -0.39482876061991856,
    -0.4076238050898, -0.42186359488277986, -0.43783361872980203,
    -0.45534547574978951, -0.4745785806874076, -0.49536061555477512,
    -0.5177479210534276, -0.54159075405376411, -0.56689309678359279,
    -0.59349586379827357, -0.62134110706260959, -0.65028250159108869,
    -0.68016219926773192, -0.71088350132071554, -0.74209742584757121,
    -0.77370660765195853, -0.80527220165048019, -0.83666697503280885,
    -0.86740569433920045, -0.897234992326777, -0.92591411560290959,
    -0.9530619828751562, -0.978594977269748, -1.0022444601444485,
    -1.023907678571718, -1.0435901693217422, -1.0611110082932049,
    -1.0768495282321111, -1.0903745610801752, -1.1025134852542522,
    -1.1125101015651102, -1.1215581205787246, -1.1285884038102372,
    -1.1349500090158078, -1.1394339904836452, -1.1432734389733439,
    -1.1453841078352378, -1.1466805702978273, -1.1463887207952055,
    -1.1450739396952687, -1.1422701089728591, -1.1382401437225111,
    -1.1327659001750316, -1.1258839755707259, -1.1176122814216825,
    -1.1077957152904452, -1.0967110341125492, -1.0840307968122858,
    -1.0703279555754759, -1.0551536525154463, -1.0393703173002327,
    -1.0224305302332706, -1.0054128834446372, -0.98770039816751509,
    -0.97054731294871888, -0.95330145234161012, -0.93726211381048907,
    -0.92179085288739593, -0.90796294973619507, -0.89526093523869443,
    -0.88436335913313491, -0.8750808822415902, -0.86748205707529691,
    -0.86189417128308532, -0.85762701223042226, -0.8553765745484827,
    -0.85406768857705517, -0.85438617171329334, -0.85536999926361035,
    -0.85779036308440026, -0.86021630872654808, -0.86349015503927429,
    -0.86616628367330106, -0.86900256149929012, -0.87029984081420919,
    -0.87078574092266825, -0.86870623540979419, -0.86452198334120722,
    -0.85700891956582714, -0.846296908259438, -0.83161129090162411,
    -0.81274603029553361, -0.78965751105956961, -0.76198464240141217,
    -0.73001168720625864, -0.6936662845131909, -0.65332955075453281,
    -0.6093562039666891, -0.56210028190630945, -0.51222601231283693,
    -0.46009909594991333, -0.40651329806406927, -0.352064174923422,
    -0.29747299692461282, -0.24365070655445834, -0.19112784692880569,
    -0.14099972384899662, -0.09369199698185969, -0.050232911207993551,
    -0.011087638344860193, 0.023018451631133609, 0.051524538378626958,
    0.074033287066013753, 0.089828038588680589, 0.098858183430861529,
    0.10046495151454683, 0.094585271919271269, 0.0807634504145989,
    0.059051201200046387, 0.029196639410922636, -0.008817345945693892,
    -0.054990547362065129, -0.10917775556238012, -0.17124876403736214,
    -0.24066154005717028, -0.31748579303120761, -0.40030572255849145,
    -0.48944530001264674, -0.582955840790247, -0.68134901137073467,
    -0.78213894894941327, -0.88594701750183247, -0.989931862533661,
    -1.0945903175413685, -1.1971705987171872, -1.2981888000523278,
    -1.3946049538534333, -1.4869881555366438, -1.5726558255062033,
    -1.651919352716394, -1.7228272395162925, -1.785398751927703,
    -1.8384414900284112, -1.8818474462985106, -1.9151408483685739,
    -1.9382766481941898, -1.9513128897451939, -1.9545509139903412,
    -1.9481117103284025, -1.9327501141064847, -1.9086401314114669,
    -1.8768004361374842, -1.8376910543149445, -1.7924738385486261,
    -1.7418195424478868, -1.6869207427294546, -1.6285749343120866,
    -1.567840580298117, -1.5055989611893354, -1.4427940764165228,
    -1.3801923325819172, -1.3186523154767373, -1.2587297581217911,
    -1.2011417392802213, -1.1462166106068872, -1.0944969682153967,
    -1.0461221096544058, -1.0014297502301592, -0.96038741169247466,
    -0.92313935158661808, -0.88952896743777277, -0.85953514081234517,
    -0.83290108415589048, -0.80950059120616047, -0.7889774830641525,
    -0.771121386992763, -0.75558449843157283, -0.74206356545405561,
    -0.73024917490599517, -0.71980086743546445, -0.71045785674785988,
    -0.701912962542336, -0.69397137514078366, -0.68644322304902339,
    -0.6791617301935543, -0.672059145370413, -0.66496445635212964,
    -0.65786616427972111, -0.65062550990876433, -0.64323189781563483,
    -0.63562438019419243, -0.62775823271552467, -0.61964179382275042,
    -0.61122126562835566, -0.60251521140452258, -0.59349126432045229,
    -0.58416282878541237, -0.57455604084437517, -0.5647171270016409,
    -0.55478177767570336, -0.54484730588369945, -0.53512628267547224,
    -0.52574158069643251, -0.51691046709479127, -0.50872063673701651,
    -0.5013173596892192, -0.49468402122784805, -0.48883855214015648,
    -0.48364015973390229, -0.479006107167819, -0.47471874638459349,
    -0.4706296780642012, -0.46649815998613514, -0.462155025388771,
    -0.4573686071321128, -0.45199893737929625, -0.44590582741834522,
    -0.43905060192676509, -0.43147430249122604, -0.42328849495325355,
    -0.41473203062937891, -0.40603469693569127, -0.39757248750347063,
    -0.38963847119494588, -0.38273520317765847, -0.37718719317373645,
    -0.37347828723593307, -0.37191095018742576, -0.37289787995338014,
    -0.37662130723713955, -0.38334777503920975, -0.39310162289261619,
    -0.40593910741037925, -0.42170144372869095, -0.44027439255738743,
    -0.46131316258028571, -0.484576587618624, -0.50957406552916629,
    -0.53600046330100859, -0.56326740270877362, -0.59105375435376806,
    -0.61875486981838723, -0.64600857365958875, -0.67226845511388289,
    -0.69714241735002469, -0.72019100087247978, -0.74103840929030429,
    -0.75937579739331884, -0.7748843187949459, -0.787385609358795,
    -0.79661102088573632, -0.80254343278303908, -0.80493036925292949,
    -0.80390573256331221, -0.79927927288919787, -0.79126723205700511,
    -0.77977973076009621, -0.765071924454206, -0.74719455728484174,
    -0.72644506089822547, -0.70304025454606667, -0.677324539541751,
    -0.64965831722190681, -0.62041421519994144, -0.59007853189388348,
    -0.55902212381602168, -0.5278164422533721, -0.49680834971007271,
    -0.46661670490589896, -0.43754836772458033, -0.41020557048144807,
    -0.38482571557728718, -0.36194621503421, -0.34172732163649105,
    -0.32461675074365531, -0.31071416237362526, -0.30039659651106854,
    -0.29370903421423888, -0.29094871793119886 };

  rt_InitInfAndNaN(8U);
  memcpy(&t[0], &dv1[0], sizeof(double) << 9);
  memcpy(&vel_arr[0], &dv2[0], sizeof(double) << 9);
  memcpy(&acc_arr[0], &dv3[0], sizeof(double) << 9);
  arr_len = b_arr_len;
}

/*
 * File trailer for sliding_integration_f_initialize.c
 *
 * [EOF]
 */
