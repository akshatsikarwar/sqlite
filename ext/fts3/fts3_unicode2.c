/*
** 2012 May 25
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
******************************************************************************
*/

/*
** DO NOT EDIT THIS MACHINE GENERATED FILE.
*/

#include <assert.h>

/*
** Return true if the argument corresponds to a unicode codepoint
** classified as either a letter or a number. Otherwise false.
**
** The results are undefined if the value passed to this function
** is less than zero.
*/
int sqlite3FtsUnicodeIsalnum(int c){
  /* Each unsigned integer in the following array corresponds to a contiguous
  ** range of unicode codepoints that are not either letters or numbers (i.e.
  ** codepoints for which this function should return 0).
  **
  ** The most significant 22 bits in each 32-bit value contain the first 
  ** codepoint in the range. The least significant 10 bits are used to store
  ** the size of the range (always at least 1). In other words, the value 
  ** ((C<<22) + N) represents a range of N codepoints starting with codepoint 
  ** C. It is not possible to represent a range larger than 1023 codepoints 
  ** using this format.
  */
  const static unsigned int aEntry[] = {
    0x00000030, 0x0000E807, 0x00016C06, 0x0001EC2F, 0x0002AC07,
    0x0002D001, 0x0002D803, 0x0002EC01, 0x0002FC01, 0x00035C01,
    0x0003DC01, 0x000B0804, 0x000B480E, 0x000B9407, 0x000BB401,
    0x000BBC81, 0x000DD401, 0x000DF801, 0x000E1002, 0x000E1C01,
    0x000FD801, 0x00120808, 0x00156806, 0x00162402, 0x00163C01,
    0x00164437, 0x0017CC02, 0x00180005, 0x00181816, 0x00187802,
    0x00192C15, 0x0019A804, 0x0019C001, 0x001B5001, 0x001B580F,
    0x001B9C07, 0x001BF402, 0x001C000E, 0x001C3C01, 0x001C4401,
    0x001CC01B, 0x001E980B, 0x001FAC09, 0x001FD804, 0x00205804,
    0x00206C09, 0x00209403, 0x0020A405, 0x0020C00F, 0x00216403,
    0x00217801, 0x0023901B, 0x00240004, 0x0024E803, 0x0024F812,
    0x00254407, 0x00258804, 0x0025C001, 0x00260403, 0x0026F001,
    0x0026F807, 0x00271C02, 0x00272C03, 0x00275C01, 0x00278802,
    0x0027C802, 0x0027E802, 0x00280403, 0x0028F001, 0x0028F805,
    0x00291C02, 0x00292C03, 0x00294401, 0x0029C002, 0x0029D401,
    0x002A0403, 0x002AF001, 0x002AF808, 0x002B1C03, 0x002B2C03,
    0x002B8802, 0x002BC002, 0x002C0403, 0x002CF001, 0x002CF807,
    0x002D1C02, 0x002D2C03, 0x002D5802, 0x002D8802, 0x002DC001,
    0x002E0801, 0x002EF805, 0x002F1803, 0x002F2804, 0x002F5C01,
    0x002FCC08, 0x00300403, 0x0030F807, 0x00311803, 0x00312804,
    0x00315402, 0x00318802, 0x0031FC01, 0x00320802, 0x0032F001,
    0x0032F807, 0x00331803, 0x00332804, 0x00335402, 0x00338802,
    0x00340802, 0x0034F807, 0x00351803, 0x00352804, 0x00355C01,
    0x00358802, 0x0035E401, 0x00360802, 0x00372801, 0x00373C06,
    0x00375801, 0x00376008, 0x0037C803, 0x0038C401, 0x0038D007,
    0x0038FC01, 0x00391C09, 0x00396802, 0x003AC401, 0x003AD006,
    0x003AEC02, 0x003B2006, 0x003C041F, 0x003CD00C, 0x003DC417,
    0x003E340B, 0x003E6424, 0x003EF80F, 0x003F380D, 0x0040AC14,
    0x00412806, 0x00415804, 0x00417803, 0x00418803, 0x00419C07,
    0x0041C404, 0x0042080C, 0x00423C01, 0x00426806, 0x0043EC01,
    0x004D740C, 0x004E400A, 0x00500001, 0x0059B402, 0x005A0001,
    0x005A6C02, 0x005BAC03, 0x005C4803, 0x005CC805, 0x005D4802,
    0x005DC802, 0x005ED023, 0x005F6004, 0x005F7401, 0x0060000F,
    0x0062A401, 0x0064800C, 0x0064C00C, 0x00650001, 0x00651002,
    0x0066C011, 0x00672002, 0x00677822, 0x00685C05, 0x00687802,
    0x0069540A, 0x0069801D, 0x0069FC01, 0x006A8007, 0x006AA006,
    0x006C0005, 0x006CD011, 0x006D6823, 0x006E0003, 0x006E840D,
    0x006F980E, 0x006FF004, 0x00709014, 0x0070EC05, 0x0071F802,
    0x00730008, 0x00734019, 0x0073B401, 0x0073C803, 0x00770027,
    0x0077F004, 0x007EF401, 0x007EFC03, 0x007F3403, 0x007F7403,
    0x007FB403, 0x007FF402, 0x00800065, 0x0081A806, 0x0081E805,
    0x00822805, 0x0082801A, 0x00834021, 0x00840002, 0x00840C04,
    0x00842002, 0x00845001, 0x00845803, 0x00847806, 0x00849401,
    0x00849C01, 0x0084A401, 0x0084B801, 0x0084E802, 0x00850005,
    0x00852804, 0x00853C01, 0x00864264, 0x00900027, 0x0091000B,
    0x0092704E, 0x00940200, 0x009C0475, 0x009E53B9, 0x00AD400A,
    0x00B39406, 0x00B3BC03, 0x00B3E404, 0x00B3F802, 0x00B5C001,
    0x00B5FC01, 0x00B7804F, 0x00B8C00C, 0x00BA001A, 0x00BA6C59,
    0x00BC00D6, 0x00BFC00C, 0x00C00005, 0x00C02019, 0x00C0A807,
    0x00C0D802, 0x00C0F403, 0x00C26404, 0x00C28001, 0x00C3EC01,
    0x00C64002, 0x00C6580A, 0x00C70024, 0x00C8001F, 0x00C8A81E,
    0x00C94001, 0x00C98020, 0x00CA2827, 0x00CB003F, 0x00CC0100,
    0x01370040, 0x02924037, 0x0293F802, 0x02983403, 0x0299BC10,
    0x029A7C01, 0x029BC008, 0x029C0017, 0x029C8002, 0x029E2402,
    0x02A00801, 0x02A01801, 0x02A02C01, 0x02A08C09, 0x02A0D804,
    0x02A1D004, 0x02A20002, 0x02A2D011, 0x02A33802, 0x02A38012,
    0x02A3E003, 0x02A4980A, 0x02A51C0D, 0x02A57C01, 0x02A60004,
    0x02A6CC1B, 0x02A77802, 0x02A8A40E, 0x02A90C01, 0x02A93002,
    0x02A97004, 0x02A9DC03, 0x02A9EC01, 0x02AAC001, 0x02AAC803,
    0x02AADC02, 0x02AAF802, 0x02AB0401, 0x02AB7802, 0x02ABAC07,
    0x02ABD402, 0x02AF8C0B, 0x03600001, 0x036DFC02, 0x036FFC02,
    0x037FFC02, 0x03E3FC01, 0x03EC7801, 0x03ECA401, 0x03EEC810,
    0x03F4F802, 0x03F7F002, 0x03F8001A, 0x03F88007, 0x03F8C023,
    0x03F95013, 0x03F9A004, 0x03FBFC01, 0x03FC040F, 0x03FC6807,
    0x03FCEC06, 0x03FD6C0B, 0x03FF8007, 0x03FFA007, 0x03FFE405,
    0x04040003, 0x0404DC09, 0x0405E411, 0x0406400C, 0x0407402E,
    0x040E7C01, 0x040F4001, 0x04215C01, 0x04247C01, 0x0424FC01,
    0x04280403, 0x04281402, 0x04283004, 0x0428E003, 0x0428FC01,
    0x04294009, 0x0429FC01, 0x042CE407, 0x04400003, 0x0440E016,
    0x04420003, 0x0442C012, 0x04440003, 0x04449C0E, 0x04450004,
    0x04460003, 0x0446CC0E, 0x04471404, 0x045AAC0D, 0x0491C004,
    0x05BD442E, 0x05BE3C04, 0x074000F6, 0x07440027, 0x0744A4B5,
    0x07480046, 0x074C0057, 0x075B0401, 0x075B6C01, 0x075BEC01,
    0x075C5401, 0x075CD401, 0x075D3C01, 0x075DBC01, 0x075E2401,
    0x075EA401, 0x075F0C01, 0x07BBC002, 0x07C0002C, 0x07C0C064,
    0x07C2800F, 0x07C2C40E, 0x07C3040F, 0x07C3440F, 0x07C4401F,
    0x07C4C03C, 0x07C5C02B, 0x07C7981D, 0x07C8402B, 0x07C90009,
    0x07C94002, 0x07CC0021, 0x07CCC006, 0x07CCDC46, 0x07CE0014,
    0x07CE8025, 0x07CF1805, 0x07CF8011, 0x07D0003F, 0x07D10001,
    0x07D108B6, 0x07D3E404, 0x07D4003E, 0x07D50004, 0x07D54018,
    0x07D7EC46, 0x07D9140B, 0x07DA0046, 0x07DC0074, 0x38000401,
    0x38008060, 0x380400F0, 0x3C000001, 0x3FFFF401, 0x40000001,
    0x43FFF401,
  };
  static const unsigned int aAscii[4] = {
    0xFFFFFFFF, 0xFC00FFFF, 0xF8000001, 0xF8000001,
  };

  if( c<128 ){
    return ( (aAscii[c >> 5] & (1 << (c & 0x001F)))==0 );
  }else if( c<(1<<22) ){
    unsigned int key = (((unsigned int)c)<<10) | 0x000003FF;
    int iRes;
    int iHi = sizeof(aEntry)/sizeof(aEntry[0]) - 1;
    int iLo = 0;
    while( iHi>=iLo ){
      int iTest = (iHi + iLo) / 2;
      if( key >= aEntry[iTest] ){
        iRes = iTest;
        iLo = iTest+1;
      }else{
        iHi = iTest-1;
      }
    }
    assert( aEntry[0]<key );
    assert( key>=aEntry[iRes] );
    return (c >= ((aEntry[iRes]>>10) + (aEntry[iRes]&0x3FF)));
  }
  return 1;
}


/*
** Interpret the argument as a unicode codepoint. If the codepoint
** is an upper case character that has a lower case equivalent,
** return the codepoint corresponding to the lower case version.
** Otherwise, return a copy of the argument.
**
** The results are undefined if the value passed to this function
** is less than zero.
*/
int sqlite3FtsUnicodeTolower(int c){
  /* Each entry in the following array defines a rule for folding a range
  ** of codepoints to lower case. The rule applies to a range of nRange
  ** codepoints starting at codepoint iCode.
  **
  ** If bFlag is clear, then all the codepoints in the range are upper
  ** case and require folding. Or, if bFlag is set, then only every second
  ** codepoint in the range, starting with iCode, requires folding. If a
  ** specific codepoint C does require folding, then the lower-case version
  ** is ((C + iOff)&0xFFFF).
  **
  ** The contents of this array are generated by parsing the CaseFolding.txt
  ** file distributed as part of the "Unicode Character Database". See
  ** http://www.unicode.org for details.
  */
  static const struct TableEntry {
    unsigned short iCode;
    unsigned char bFlag;
    unsigned char nRange;
    unsigned short iOff;
  } aEntry[] = {
    {65, 0, 26, 32},       {181, 0, 1, 775},      {192, 0, 23, 32},
    {216, 0, 7, 32},       {256, 1, 48, 1},       {306, 1, 6, 1},
    {313, 1, 16, 1},       {330, 1, 46, 1},       {376, 0, 1, 65415},
    {377, 1, 6, 1},        {383, 0, 1, 65268},    {385, 0, 1, 210},
    {386, 1, 4, 1},        {390, 0, 1, 206},      {391, 0, 1, 1},
    {393, 0, 2, 205},      {395, 0, 1, 1},        {398, 0, 1, 79},
    {399, 0, 1, 202},      {400, 0, 1, 203},      {401, 0, 1, 1},
    {403, 0, 1, 205},      {404, 0, 1, 207},      {406, 0, 1, 211},
    {407, 0, 1, 209},      {408, 0, 1, 1},        {412, 0, 1, 211},
    {413, 0, 1, 213},      {415, 0, 1, 214},      {416, 1, 6, 1},
    {422, 0, 1, 218},      {423, 0, 1, 1},        {425, 0, 1, 218},
    {428, 0, 1, 1},        {430, 0, 1, 218},      {431, 0, 1, 1},
    {433, 0, 2, 217},      {435, 1, 4, 1},        {439, 0, 1, 219},
    {440, 0, 1, 1},        {444, 0, 1, 1},        {452, 0, 1, 2},
    {453, 0, 1, 1},        {455, 0, 1, 2},        {456, 0, 1, 1},
    {458, 0, 1, 2},        {459, 1, 18, 1},       {478, 1, 18, 1},
    {497, 0, 1, 2},        {498, 1, 4, 1},        {502, 0, 1, 65439},
    {503, 0, 1, 65480},    {504, 1, 40, 1},       {544, 0, 1, 65406},
    {546, 1, 18, 1},       {570, 0, 1, 10795},    {571, 0, 1, 1},
    {573, 0, 1, 65373},    {574, 0, 1, 10792},    {577, 0, 1, 1},
    {579, 0, 1, 65341},    {580, 0, 1, 69},       {581, 0, 1, 71},
    {582, 1, 10, 1},       {837, 0, 1, 116},      {880, 1, 4, 1},
    {886, 0, 1, 1},        {902, 0, 1, 38},       {904, 0, 3, 37},
    {908, 0, 1, 64},       {910, 0, 2, 63},       {913, 0, 17, 32},
    {931, 0, 9, 32},       {962, 0, 1, 1},        {975, 0, 1, 8},
    {976, 0, 1, 65506},    {977, 0, 1, 65511},    {981, 0, 1, 65521},
    {982, 0, 1, 65514},    {984, 1, 24, 1},       {1008, 0, 1, 65482},
    {1009, 0, 1, 65488},   {1012, 0, 1, 65476},   {1013, 0, 1, 65472},
    {1015, 0, 1, 1},       {1017, 0, 1, 65529},   {1018, 0, 1, 1},
    {1021, 0, 3, 65406},   {1024, 0, 16, 80},     {1040, 0, 32, 32},
    {1120, 1, 34, 1},      {1162, 1, 54, 1},      {1216, 0, 1, 15},
    {1217, 1, 14, 1},      {1232, 1, 88, 1},      {1329, 0, 38, 48},
    {4256, 0, 38, 7264},   {4295, 0, 1, 7264},    {4301, 0, 1, 7264},
    {7680, 1, 150, 1},     {7835, 0, 1, 65478},   {7838, 0, 1, 57921},
    {7840, 1, 96, 1},      {7944, 0, 8, 65528},   {7960, 0, 6, 65528},
    {7976, 0, 8, 65528},   {7992, 0, 8, 65528},   {8008, 0, 6, 65528},
    {8025, 1, 8, 65528},   {8040, 0, 8, 65528},   {8072, 0, 8, 65528},
    {8088, 0, 8, 65528},   {8104, 0, 8, 65528},   {8120, 0, 2, 65528},
    {8122, 0, 2, 65462},   {8124, 0, 1, 65527},   {8126, 0, 1, 58363},
    {8136, 0, 4, 65450},   {8140, 0, 1, 65527},   {8152, 0, 2, 65528},
    {8154, 0, 2, 65436},   {8168, 0, 2, 65528},   {8170, 0, 2, 65424},
    {8172, 0, 1, 65529},   {8184, 0, 2, 65408},   {8186, 0, 2, 65410},
    {8188, 0, 1, 65527},   {8486, 0, 1, 58019},   {8490, 0, 1, 57153},
    {8491, 0, 1, 57274},   {8498, 0, 1, 28},      {8544, 0, 16, 16},
    {8579, 0, 1, 1},       {9398, 0, 26, 26},     {11264, 0, 47, 48},
    {11360, 0, 1, 1},      {11362, 0, 1, 54793},  {11363, 0, 1, 61722},
    {11364, 0, 1, 54809},  {11367, 1, 6, 1},      {11373, 0, 1, 54756},
    {11374, 0, 1, 54787},  {11375, 0, 1, 54753},  {11376, 0, 1, 54754},
    {11378, 0, 1, 1},      {11381, 0, 1, 1},      {11390, 0, 2, 54721},
    {11392, 1, 100, 1},    {11499, 1, 4, 1},      {11506, 0, 1, 1},
    {42560, 1, 46, 1},     {42624, 1, 24, 1},     {42786, 1, 14, 1},
    {42802, 1, 62, 1},     {42873, 1, 4, 1},      {42877, 0, 1, 30204},
    {42878, 1, 10, 1},     {42891, 0, 1, 1},      {42893, 0, 1, 23256},
    {42896, 1, 4, 1},      {42912, 1, 10, 1},     {42922, 0, 1, 23228},
    {65313, 0, 26, 32},    
  };

  int ret = c;

  assert( c>=0 );
  assert( sizeof(unsigned short)==2 && sizeof(unsigned char)==1 );

  if( c<128 ){
    if( c>='A' && c<='Z' ) ret = c + ('a' - 'A');
  }else if( c<65536 ){
    int iHi = sizeof(aEntry)/sizeof(aEntry[0]) - 1;
    int iLo = 0;
    int iRes = -1;

    while( iHi>=iLo ){
      int iTest = (iHi + iLo) / 2;
      int cmp = (c - aEntry[iTest].iCode);
      if( cmp>=0 ){
        iRes = iTest;
        iLo = iTest+1;
      }else{
        iHi = iTest-1;
      }
    }
    assert( iRes<0 || c>=aEntry[iRes].iCode );

    if( iRes>=0 ){
      const struct TableEntry *p = &aEntry[iRes];
      if( c<(p->iCode + p->nRange) && 0==(p->bFlag & (p->iCode ^ c)) ){
        ret = (c + p->iOff) & 0x0000FFFF;
        assert( ret>0 );
      }
    }
  }
  
  else if( c>=66560 && c<66600 ){
    ret = c + 40;
  }

  return ret;
}
