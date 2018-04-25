/****************************************************************************
**
**   ITU-T G.722.1 (2005-05) - Fixed point implementation for main body and Annex C
**   > Software Release 2.1 (2008-06)
**     (Simple repackaging; no change from 2005-05 Release 2.0 code)
**
**   ?2004 Polycom, Inc.
**
**	 All rights reserved.
**
****************************************************************************/

/****************************************************************************
  Filename:    dct4_a.h    

  Purpose:     Contains tables used by dct4_a.c
		
  Design Notes:

****************************************************************************/

/***************************************************************************
 Include files                                                           
***************************************************************************/
#include <stdio.h>
#include <math.h>

typedef struct 
{
    Word16	cosine;
    Word16	minus_sine;
} cos_msin_t;

cos_msin_t	a_cos_msin_2[10] = {
    {  29805   ,   -1171   } , 
    {  29621   ,   -3506   } , 
    {  29255   ,   -5819   } , 
    {  28708   ,   -8097   } , 
    {  27984   ,   -10324   } , 
    {  27088   ,   -12488   } , 
    {  26025   ,   -14575   } , 
    {  24801   ,   -16572   } , 
    {  23425   ,   -18466   } , 
    {  21903   ,   -20247   }  
    }; 
cos_msin_t	a_cos_msin_4[20] = {
    {  29822   ,   -586   } , 
    {  29776   ,   -1756   } , 
    {  29684   ,   -2924   } , 
    {  29547   ,   -4087   } , 
    {  29364   ,   -5244   } , 
    {  29135   ,   -6392   } , 
    {  28862   ,   -7531   } , 
    {  28544   ,   -8659   } , 
    {  28182   ,   -9773   } , 
    {  27776   ,   -10871   } , 
    {  27328   ,   -11954   } , 
    {  26838   ,   -13017   } , 
    {  26306   ,   -14061   } , 
    {  25734   ,   -15083   } , 
    {  25122   ,   -16081   } , 
    {  24471   ,   -17055   } , 
    {  23783   ,   -18003   } , 
    {  23057   ,   -18923   } , 
    {  22297   ,   -19813   } , 
    {  21502   ,   -20673   } 
    };
cos_msin_t	a_cos_msin_8[40] = {
    {  29827   ,   -293   } , 
    {  29815   ,   -878   } , 
    {  29792   ,   -1464   } , 
    {  29758   ,   -2048   } , 
    {  29712   ,   -2632   } , 
    {  29654   ,   -3215   } , 
    {  29586   ,   -3797   } , 
    {  29505   ,   -4377   } , 
    {  29414   ,   -4955   } , 
    {  29311   ,   -5532   } , 
    {  29196   ,   -6106   } , 
    {  29071   ,   -6678   } , 
    {  28934   ,   -7248   } , 
    {  28786   ,   -7814   } , 
    {  28627   ,   -8378   } , 
    {  28457   ,   -8938   } , 
    {  28276   ,   -9495   } , 
    {  28084   ,   -10049   } , 
    {  27882   ,   -10598   } , 
    {  27668   ,   -11144   } , 
    {  27444   ,   -11685   } , 
    {  27209   ,   -12221   } , 
    {  26964   ,   -12753   } , 
    {  26709   ,   -13280   } , 
    {  26443   ,   -13802   } , 
    {  26167   ,   -14318   } , 
    {  25881   ,   -14829   } , 
    {  25584   ,   -15335   } , 
    {  25278   ,   -15834   } , 
    {  24963   ,   -16327   } , 
    {  24637   ,   -16814   } , 
    {  24302   ,   -17295   } , 
    {  23958   ,   -17769   } , 
    {  23605   ,   -18236   } , 
    {  23242   ,   -18695   } , 
    {  22871   ,   -19148   } , 
    {  22490   ,   -19594   } , 
    {  22101   ,   -20031   } , 
    {  21704   ,   -20461   } , 
    {  21298   ,   -20884   } 
    };
cos_msin_t	a_cos_msin_16[80] = {
    {  29828   ,   -146   } , 
    {  29825   ,   -439   } , 
    {  29819   ,   -732   } , 
    {  29811   ,   -1025   } , 
    {  29799   ,   -1317   } , 
    {  29785   ,   -1610   } , 
    {  29767   ,   -1902   } , 
    {  29747   ,   -2194   } , 
    {  29724   ,   -2486   } , 
    {  29698   ,   -2778   } , 
    {  29670   ,   -3069   } , 
    {  29638   ,   -3360   } , 
    {  29604   ,   -3651   } , 
    {  29567   ,   -3942   } , 
    {  29526   ,   -4232   } , 
    {  29483   ,   -4521   } , 
    {  29438   ,   -4811   } , 
    {  29389   ,   -5099   } , 
    {  29338   ,   -5388   } , 
    {  29283   ,   -5676   } , 
    {  29226   ,   -5963   } , 
    {  29166   ,   -6249   } , 
    {  29103   ,   -6535   } , 
    {  29038   ,   -6821   } , 
    {  28969   ,   -7106   } , 
    {  28898   ,   -7390   } , 
    {  28824   ,   -7673   } , 
    {  28748   ,   -7956   } , 
    {  28668   ,   -8237   } , 
    {  28586   ,   -8518   } , 
    {  28501   ,   -8799   } , 
    {  28413   ,   -9078   } , 
    {  28323   ,   -9357   } , 
    {  28229   ,   -9634   } , 
    {  28133   ,   -9911   } , 
    {  28035   ,   -10187   } , 
    {  27933   ,   -10461   } , 
    {  27829   ,   -10735   } , 
    {  27723   ,   -11008   } , 
    {  27613   ,   -11279   } , 
    {  27501   ,   -11550   } , 
    {  27387   ,   -11819   } , 
    {  27269   ,   -12088   } , 
    {  27149   ,   -12355   } , 
    {  27027   ,   -12621   } , 
    {  26901   ,   -12885   } , 
    {  26774   ,   -13149   } , 
    {  26643   ,   -13411   } , 
    {  26510   ,   -13672   } , 
    {  26375   ,   -13932   } , 
    {  26237   ,   -14190   } , 
    {  26096   ,   -14447   } , 
    {  25953   ,   -14702   } , 
    {  25807   ,   -14956   } , 
    {  25659   ,   -15209   } , 
    {  25509   ,   -15460   } , 
    {  25356   ,   -15710   } , 
    {  25200   ,   -15958   } , 
    {  25043   ,   -16205   } , 
    {  24882   ,   -16450   } , 
    {  24720   ,   -16693   } , 
    {  24554   ,   -16935   } , 
    {  24387   ,   -17175   } , 
    {  24217   ,   -17414   } , 
    {  24045   ,   -17651   } , 
    {  23871   ,   -17886   } , 
    {  23694   ,   -18119   } , 
    {  23515   ,   -18351   } , 
    {  23334   ,   -18581   } , 
    {  23150   ,   -18809   } , 
    {  22964   ,   -19036   } , 
    {  22776   ,   -19260   } , 
    {  22586   ,   -19483   } , 
    {  22394   ,   -19704   } , 
    {  22199   ,   -19923   } , 
    {  22003   ,   -20140   } , 
    {  21804   ,   -20355   } , 
    {  21603   ,   -20568   } , 
    {  21400   ,   -20779   } , 
    {  21195   ,   -20988   } 
    };
cos_msin_t	a_cos_msin_32[160]= {
    {  29828   ,   -73   } , 
    {  29827   ,   -220   } , 
    {  29826   ,   -366   } , 
    {  29824   ,   -512   } , 
    {  29821   ,   -659   } , 
    {  29817   ,   -805   } , 
    {  29813   ,   -952   } , 
    {  29808   ,   -1098   } , 
    {  29802   ,   -1244   } , 
    {  29796   ,   -1390   } , 
    {  29789   ,   -1537   } , 
    {  29781   ,   -1683   } , 
    {  29772   ,   -1829   } , 
    {  29763   ,   -1975   } , 
    {  29753   ,   -2121   } , 
    {  29742   ,   -2267   } , 
    {  29730   ,   -2413   } , 
    {  29718   ,   -2559   } , 
    {  29705   ,   -2705   } , 
    {  29692   ,   -2851   } , 
    {  29677   ,   -2997   } , 
    {  29662   ,   -3142   } , 
    {  29646   ,   -3288   } , 
    {  29630   ,   -3433   } , 
    {  29613   ,   -3579   } , 
    {  29595   ,   -3724   } , 
    {  29576   ,   -3869   } , 
    {  29557   ,   -4014   } , 
    {  29537   ,   -4159   } , 
    {  29516   ,   -4304   } , 
    {  29494   ,   -4449   } , 
    {  29472   ,   -4594   } , 
    {  29449   ,   -4738   } , 
    {  29426   ,   -4883   } , 
    {  29401   ,   -5027   } , 
    {  29376   ,   -5172   } , 
    {  29351   ,   -5316   } , 
    {  29324   ,   -5460   } , 
    {  29297   ,   -5604   } , 
    {  29269   ,   -5747   } , 
    {  29241   ,   -5891   } , 
    {  29211   ,   -6034   } , 
    {  29181   ,   -6178   } , 
    {  29151   ,   -6321   } , 
    {  29119   ,   -6464   } , 
    {  29087   ,   -6607   } , 
    {  29054   ,   -6749   } , 
    {  29021   ,   -6892   } , 
    {  28987   ,   -7034   } , 
    {  28952   ,   -7177   } , 
    {  28916   ,   -7319   } , 
    {  28880   ,   -7460   } , 
    {  28843   ,   -7602   } , 
    {  28805   ,   -7744   } , 
    {  28767   ,   -7885   } , 
    {  28728   ,   -8026   } , 
    {  28688   ,   -8167   } , 
    {  28648   ,   -8308   } , 
    {  28607   ,   -8448   } , 
    {  28565   ,   -8589   } , 
    {  28522   ,   -8729   } , 
    {  28479   ,   -8869   } , 
    {  28435   ,   -9008   } , 
    {  28391   ,   -9148   } , 
    {  28346   ,   -9287   } , 
    {  28300   ,   -9426   } , 
    {  28253   ,   -9565   } , 
    {  28206   ,   -9703   } , 
    {  28158   ,   -9842   } , 
    {  28109   ,   -9980   } , 
    {  28060   ,   -10118   } , 
    {  28010   ,   -10255   } , 
    {  27959   ,   -10393   } , 
    {  27908   ,   -10530   } , 
    {  27856   ,   -10667   } , 
    {  27803   ,   -10803   } , 
    {  27750   ,   -10940   } , 
    {  27696   ,   -11076   } , 
    {  27641   ,   -11212   } , 
    {  27586   ,   -11347   } , 
    {  27529   ,   -11482   } , 
    {  27473   ,   -11617   } , 
    {  27415   ,   -11752   } , 
    {  27357   ,   -11886   } , 
    {  27299   ,   -12021   } , 
    {  27239   ,   -12154   } , 
    {  27179   ,   -12288   } , 
    {  27119   ,   -12421   } , 
    {  27057   ,   -12554   } , 
    {  26996   ,   -12687   } , 
    {  26933   ,   -12819   } , 
    {  26870   ,   -12951   } , 
    {  26806   ,   -13083   } , 
    {  26741   ,   -13215   } , 
    {  26676   ,   -13346   } , 
    {  26610   ,   -13476   } , 
    {  26544   ,   -13607   } , 
    {  26477   ,   -13737   } , 
    {  26409   ,   -13867   } , 
    {  26340   ,   -13996   } , 
    {  26271   ,   -14125   } , 
    {  26202   ,   -14254   } , 
    {  26132   ,   -14383   } , 
    {  26061   ,   -14511   } , 
    {  25989   ,   -14638   } , 
    {  25917   ,   -14766   } , 
    {  25844   ,   -14893   } , 
    {  25771   ,   -15020   } , 
    {  25697   ,   -15146   } , 
    {  25622   ,   -15272   } , 
    {  25547   ,   -15397   } , 
    {  25471   ,   -15523   } , 
    {  25394   ,   -15648   } , 
    {  25317   ,   -15772   } , 
    {  25239   ,   -15896   } , 
    {  25161   ,   -16020   } , 
    {  25082   ,   -16143   } , 
    {  25003   ,   -16266   } , 
    {  24923   ,   -16389   } , 
    {  24842   ,   -16511   } , 
    {  24760   ,   -16632   } , 
    {  24678   ,   -16754   } , 
    {  24596   ,   -16875   } , 
    {  24513   ,   -16995   } , 
    {  24429   ,   -17115   } , 
    {  24345   ,   -17235   } , 
    {  24260   ,   -17354   } , 
    {  24174   ,   -17473   } , 
    {  24088   ,   -17592   } , 
    {  24002   ,   -17710   } , 
    {  23914   ,   -17827   } , 
    {  23827   ,   -17945   } , 
    {  23738   ,   -18061   } , 
    {  23649   ,   -18178   } , 
    {  23560   ,   -18293   } , 
    {  23470   ,   -18409   } , 
    {  23379   ,   -18524   } , 
    {  23288   ,   -18638   } , 
    {  23196   ,   -18752   } , 
    {  23104   ,   -18866   } , 
    {  23011   ,   -18979   } , 
    {  22917   ,   -19092   } , 
    {  22824   ,   -19204   } , 
    {  22729   ,   -19316   } , 
    {  22634   ,   -19427   } , 
    {  22538   ,   -19538   } , 
    {  22442   ,   -19649   } , 
    {  22345   ,   -19759   } , 
    {  22248   ,   -19868   } , 
    {  22150   ,   -19977   } , 
    {  22052   ,   -20086   } , 
    {  21953   ,   -20194   } , 
    {  21854   ,   -20301   } , 
    {  21754   ,   -20408   } , 
    {  21653   ,   -20515   } , 
    {  21552   ,   -20621   } , 
    {  21451   ,   -20726   } , 
    {  21349   ,   -20831   } , 
    {  21246   ,   -20936   } , 
    {  21143   ,   -21040   } 
    };
cos_msin_t	a_cos_msin_64[320] = {
{29827,	-34},
{29827,	-106},
{29827,	-177},
{29827,	-249},
{29826,	-320},
{29825,	-392},
{29824,	-463},
{29823,	-535},
{29821,	-606},
{29819,	-678},
{29818,	-750},
{29816,	-821},
{29814,	-893},
{29812,	-964},
{29809,	-1035},
{29807,	-1106},
{29804,	-1177},
{29801,	-1249},
{29797,	-1320},
{29795,	-1392},
{29791,	-1463},
{29787,	-1535},
{29784,	-1606},
{29780,	-1678},
{29776,	-1749},
{29771,	-1820},
{29767,	-1892},
{29763,	-1963},
{29758,	-2035},
{29753,	-2106},
{29748,	-2177},
{29742,	-2249},
{29737,	-2320},
{29731,	-2391},
{29726,	-2462},
{29719,	-2534},
{29713,	-2605},
{29707,	-2676},
{29701,	-2747},
{29694,	-2819},
{29686,	-2890},
{29680,	-2961},
{29673,	-3032},
{29665,	-3103},
{29658,	-3174},
{29650,	-3245},
{29643,	-3316},
{29635,	-3387},
{29626,	-3459},
{29618,	-3529},
{29610,	-3600},
{29601,	-3671},
{29592,	-3742},
{29583,	-3813},
{29574,	-3884},
{29564,	-3955},
{29554,	-4026},
{29544,	-4097},
{29535,	-4167},
{29525,	-4238},
{29514,	-4309},
{29504,	-4380},
{29493,	-4450},
{29483,	-4521},
{29472,	-4591},
{29461,	-4662},
{29450,	-4733},
{29439,	-4803},
{29427,	-4874},
{29415,	-4944},
{29403,	-5015},
{29391,	-5085},
{29379,	-5155},
{29366,	-5226},
{29353,	-5296},
{29341,	-5367},
{29328,	-5438},
{29314,	-5508},
{29301,	-5578},
{29289,	-5648},
{29274,	-5718},
{29260,	-5788},
{29247,	-5858},
{29232,	-5928},
{29218,	-5998},
{29204,	-6068},
{29188,	-6139},
{29175,	-6209},
{29159,	-6279},
{29145,	-6348},
{29128,	-6418},
{29114,	-6488},
{29097,	-6557},
{29082,	-6627},
{29066,	-6697},
{29050,	-6767},
{29034,	-6837},
{29017,	-6906},
{29001,	-6975},
{28984,	-7045},
{28966,	-7114},
{28950,	-7184},
{28933,	-7254},
{28915,	-7323},
{28897,	-7392},
{28880,	-7461},
{28862,	-7530},
{28843,	-7600},
{28825,	-7669},
{28807,	-7738},
{28788,	-7806},
{28769,	-7875},
{28751,	-7944},
{28732,	-8014},
{28712,	-8082},
{28692,	-8151},
{28672,	-8219},
{28653,	-8289},
{28633,	-8357},
{28613,	-8425},
{28593,	-8494},
{28572,	-8563},
{28551,	-8632},
{28531,	-8700},
{28510,	-8768},
{28488,	-8837},
{28468,	-8905},
{28447,	-8973},
{28425,	-9041},
{28403,	-9109},
{28381,	-9177},
{28359,	-9245},
{28336,	-9313},
{28315,	-9381},
{28292,	-9448},
{28269,	-9517},
{28246,	-9584},
{28223,	-9652},
{28200,	-9720},
{28176,	-9787},
{28153,	-9854},
{28129,	-9922},
{28105,	-9990},
{28082,	-10056},
{28057,	-10124},
{28032,	-10191},
{28009,	-10258},
{27984,	-10326},
{27959,	-10392},
{27934,	-10460},
{27909,	-10526},
{27883,	-10593},
{27858,	-10661},
{27832,	-10727},
{27807,	-10794},
{27780,	-10860},
{27754,	-10927},
{27728,	-10993},
{27701,	-11059},
{27676,	-11126},
{27648,	-11192},
{27622,	-11259},
{27595,	-11324},
{27567,	-11391},
{27540,	-11456},
{27512,	-11523},
{27484,	-11588},
{27456,	-11655},
{27429,	-11720},
{27401,	-11786},
{27372,	-11852},
{27344,	-11917},
{27315,	-11982},
{27286,	-12049},
{27257,	-12114},
{27229,	-12179},
{27199,	-12244},
{27169,	-12309},
{27140,	-12375},
{27110,	-12439},
{27080,	-12505},
{27050,	-12570},
{27019,	-12634},
{26990,	-12699},
{26958,	-12764},
{26928,	-12828},
{26897,	-12892},
{26866,	-12956},
{26835,	-13021},
{26804,	-13086},
{26773,	-13149},
{26741,	-13214},
{26709,	-13278},
{26677,	-13342},
{26645,	-13406},
{26613,	-13470},
{26581,	-13534},
{26549,	-13597},
{26515,	-13661},
{26483,	-13725},
{26450,	-13788},
{26417,	-13851},
{26384,	-13915},
{26350,	-13978},
{26316,	-14041},
{26283,	-14103},
{26248,	-14166},
{26215,	-14229},
{26180,	-14292},
{26146,	-14355},
{26112,	-14417},
{26077,	-14480},
{26042,	-14543},
{26008,	-14605},
{25972,	-14667},
{25937,	-14730},
{25901,	-14792},
{25866,	-14854},
{25830,	-14916},
{25794,	-14977},
{25759,	-15039},
{25723,	-15101},
{25687,	-15162},
{25650,	-15224},
{25613,	-15286},
{25577,	-15347},
{25540,	-15408},
{25503,	-15470},
{25465,	-15531},
{25428,	-15592},
{25391,	-15653},
{25353,	-15714},
{25315,	-15774},
{25277,	-15834},
{25240,	-15895},
{25201,	-15956},
{25162,	-16016},
{25124,	-16076},
{25086,	-16136},
{25047,	-16196},
{25008,	-16256},
{24969,	-16316},
{24930,	-16375},
{24891,	-16436},
{24851,	-16496},
{24811,	-16555},
{24772,	-16615},
{24732,	-16674},
{24692,	-16732},
{24652,	-16791},
{24612,	-16852},
{24572,	-16911},
{24531,	-16969},
{24490,	-17027},
{24449,	-17086},
{24408,	-17145},
{24367,	-17203},
{24325,	-17261},
{24284,	-17320},
{24242,	-17379},
{24200,	-17436},
{24158,	-17494},
{24116,	-17552},
{24075,	-17610},
{24032,	-17668},
{23990,	-17725},
{23947,	-17782},
{23904,	-17840},
{23862,	-17897},
{23819,	-17954},
{23775,	-18011},
{23732,	-18068},
{23689,	-18125},
{23645,	-18181},
{23602,	-18238},
{23558,	-18294},
{23514,	-18351},
{23470,	-18407},
{23426,	-18464},
{23381,	-18520},
{23337,	-18576},
{23293,	-18632},
{23248,	-18688},
{23202,	-18743},
{23158,	-18799},
{23112,	-18854},
{23068,	-18910},
{23022,	-18964},
{22977,	-19020},
{22931,	-19074},
{22885,	-19129},
{22839,	-19185},
{22793,	-19239},
{22747,	-19294},
{22700,	-19348},
{22655,	-19403},
{22607,	-19457},
{22561,	-19511},
{22514,	-19565},
{22467,	-19619},
{22421,	-19673},
{22373,	-19726},
{22326,	-19780},
{22279,	-19834},
{22230,	-19887},
{22183,	-19940},
{22135,	-19993},
{22087,	-20047},
{22039,	-20099},
{21991,	-20152},
{21942,	-20205},
{21894,	-20257},
{21845,	-20309},
{21797,	-20362},
{21748,	-20413},
{21699,	-20466},
{21650,	-20518},
{21601,	-20570},
{21551,	-20621},
{21502,	-20674}
};

cos_msin_t	*a_cos_msin_table[] = {a_cos_msin_2, a_cos_msin_4,
                                   a_cos_msin_8, a_cos_msin_16,
                                   a_cos_msin_32,a_cos_msin_64
			                      };

Word16 dct_core_a[10][10] = {

{ 10453,  10196,   9688,   8941,   7973,   6810,   5479,   4013,   2448,    823 },
{ 10196,   7973,   4013,   -823,  -5479,  -8941, -10453,  -9688,  -6810,  -2448 },
{ 9688 ,   4013,  -4013,  -9688,  -9688,  -4013,   4013,   9688,   9688,   4013 },
{ 8941 ,   -823,  -9688,  -7973,   2448,  10196,   6810,  -4013, -10453,  -5479 },
{ 7973 ,  -5479,  -9688,   2448,  10453,    823, -10196,  -4013,   8941,   6810 },
{ 6810 ,  -8941,  -4013,  10196,    823, -10453,   2448,   9688,  -5479,  -7973 },
{ 5479 , -10453,   4013,   6810, -10196,   2448,   7973,  -9688,    823,   8941 },
{ 4013 ,  -9688,   9688,  -4013,  -4013,   9688,  -9688,   4013,   4013,  -9688 },
{ 2448 ,  -6810,   9688, -10453,   8941,  -5479,    823,   4013,  -7973,  10196 },
{ 823  ,  -2448,   4013,  -5479,   6810,  -7973,   8941,  -9688,  10196, -10453 }};

Word16 anal_bias[320] = {
  1,  1,  3,  1,  4,  1,  3, -2,  4,  3,
  4,  1,  3,  0,  2, -3,  0,  0,  2,  2,
  4,  1,  1, -5,  4,  1,  2, -1,  0, -1,
  1, -2,  0,  2,  2,  2,  4,  1,  3,  0,
  5,  3,  2,  0,  3,  0,  1, -4,  1,  1,
  2,  0,  4,  0,  1, -4,  6,  1,  3, -1,
  1,  0,  0, -4,  1,  1,  3,  1,  3,  2,
  4, -2,  4,  3,  5,  1,  3,  0,  1, -3,
  1,  1,  2,  0,  4,  1,  2, -4,  4,  2,
  2, -1,  1, -1,  1, -4,  0,  0,  3,  0,
  5,  2,  3, -1,  6,  2,  5,  0,  4,  0,
  1, -3,  1,  0,  3,  0,  4,  0,  1, -3,
  4,  1,  3, -1,  1, -2,  1, -4,  0,  1,
  2,  1,  3,  2,  2, -2,  4,  3,  3,  0,
  3,  0,  0, -2,  1,  0,  2,  0,  5, -1,
  1, -3,  4,  2,  2,  0,  2, -3,  1, -4,
 -1,  1,  2,  2,  4,  1,  3, -1,  5,  2,
  2,  0,  3, -1,  2, -3,  0,  1,  2,  2,
  4,  0,  1, -5,  5,  1,  3,  0,  2, -1,
  0, -2,  1,  2,  2,  2,  4,  1,  0,  0,
  4,  2,  4,  1,  4, -1,  1, -4,  0,  1,
  3,  1,  5,  1,  1, -2,  4,  0,  2,  0,
  2, -1,  0, -2,  0,  1,  1,  1,  4,  2,
  3, -2,  5,  4,  4,  0,  3,  0,  3, -4,
  1,  2,  2,  0,  4,  1,  0, -3,  4,  2,
  3, -1,  1, -1,  1, -4,  0,  2,  3,  1,
  4,  1,  3,  0,  3,  3,  4,  1,  2,  0,
  1, -3,  2,  2,  2,  1,  5,  0,  1, -4,
  4,  1,  3, -2,  3, -1,  0, -2,  0,  2,
  2,  0,  5,  1,  4, -1,  4,  3,  4,  1,
  3,  0,  1, -4,  2,  0,  3,  1,  5,  0,
  1, -5,  5,  2,  2,  0,  0,  0,  0, -4};

