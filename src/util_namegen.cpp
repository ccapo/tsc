// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2009 Jice
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Jice may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY Jice ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL Jice BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.hpp"

const char *region_pre[] = {
  "Act",  "Afr",  "Ag", "Agr", "Alb",  "Am", "An", "Angl",  "Ant", "As", "Asys", "Asis",  
  "At", "Atl", "Brund", "Cath",  "Cor", "Dan", "Eb","Eg", "Er",
  "Esc", "Esp", "Est", "Eth",  "Eur", "Flor", "It", "Lyr", "Mal", "Mir", "Myr", "Nor", 
  "Pel", "Rom", "Seg", "Sib", "Sylv", "Terr", "Tir", "Tr", "Tyr", "Xan",
  NULL
};

const char *region_mid[] = {
  "ad",
  "ag",
  "al",
  "an",
  "and",
  "ant",
  "anth",
  "ar",
  "ard",
  "as",
  "at",
  "atr",
  "eg",
  "en",
  "ent",
  "ern",
  "et",
  "ian",
  "in",
  "itr",
  "on",
  "op",
  "ov",
  "ur",
  "ymn",
  "yr",
  NULL
};

const char *region_post[] = {
  "a",
  "aia",
  "ana",
  "as",
  "ea",
  "ene",
  "eos",
  "esia",
  "ia",
  "iad",
  "ias",
  "is",
  "ium",
  "ius",
  "on",
  "ona",
  "or",
  "ova",
  "um",
  "us",
  "ya",
  NULL
};  

const char *city_pre[] = {
  "Ael",
  "Ash",
  "Barrow",
  "Bel",
  "Black",
  "Clear",
  "Cold",
  "Crystal",
  "Deep",
  "Edge",
  "Falcon",
  "Fair",
  "Fall",
  "Glass",
  "Gold",
  "Ice",
  "Iron",
  "Mill",
  "Moon",
  "Mor",
  "Ray",
  "Red",
  "Rock",
  "Rose",
  "Shadow",
  "Silver",
  "Spell",
  "Spring",
  "Stone",
  "Strong",
  "Summer",
  "Swyn",
  "Wester",
  "Winter",
  NULL
};

const char *city_post[] = {
  "ash",
  "burn",
  "barrow",
  "bridge",
  "castle",
  "cliff",
  "coast",
  "crest",
  "dale",
  "dell",
  "dor",
  "fall",
  "field",
  "ford",
  "fort",
  "gate",
  "haven",
  "hill",
  "hold",
  "hollow",
  "iron",
  "lake",
  "marsh",
  "mill",
  "mist",
  "mount",
  "moor",
  "pond",
  "shade",
  "shore",
  "summer",
  "town",
  "wick",
  NULL
};

// celtic names
const char *char_celt_pre[] = {
  "Aen","Agno", "All","Ba", "Beo", "Brig", "Ci", "Cre","Dan", "Del", "Ela", "Eo", "En","Er", "Et", "In", "Io", "Morr","Nem","Nu","Og","Or","Ta",
  NULL
};

const char *char_celt_mid[] = {
  "a","ar","ba","bo","ch","d","ig",
  NULL
};

const char *char_celt_post_f[] = {
  "ai", "an", "da","id","iu","ma","me","na","ne","tha",
  NULL
};

const char *char_celt_post_m[] = {
  "aid", "ain", "an", "and", "th", "ed", "eth", "gus", "lam", "lor", "man", "od", "t", "thach",
  NULL
};

// norse names
const char *char_norse_pre[] = {
  "Al","Ae","As","Bi","Fen","Ha","Hag","Ho","Hu","Iv","Jot","Ma","Mio","Mu","Nid","Ors",
  "Ra","Sta","Svar","Tys","Vae","Van","Vol","Y","Ygg",
  NULL
};

const char *char_norse_mid[] = {
  "an","ar","ba","da","dra","gar","na","tal",
  NULL
};

const char *char_norse_post_f[] = {
  "a","la","li","va",
  NULL
};

const char *char_norse_post_m[] = {
  "ad","ald","agr","ar","ard","eyr","far","frost","heim","hogg","in","mir","nar","nir","or","osk","rir","sil","sir","ttir","urd",
  NULL
};

// mesopotamian names
const char *char_meso_pre[] = {
  "A","Ann","Ash","E'","En","Er","Gil","In","Ir","Ish","Mar","Ni","Nin","Re","Ti","Ur",
  NULL
};

const char *char_meso_mid[] = {
  "am","an","du","esh","gam","gir","ka","ki","li","un","ur","ta",
  NULL
};

const char *char_meso_post_f[] = {
  "ag","il","la","na","sag","su","ta",
  NULL
};

const char *char_meso_post_m[] = {
  "aki","al","ar","at","du","eph","esh","il","im","ki","nu","uk","ur","uz",
  NULL
};

// fantasy names
const char *char_fantasy_pre[] = {
  "Aer", "An", "Ar", 
  "Ban", "Bar", "Ber", "Beth", "Bett", 
  "Cut", 
  "Dan", "Dar", "Dell", "Der",
  "Edr", "Er", "Eth", "Ett",
  "Fin", 
  "Ian", "Iarr", "Ill", 
  "Jed", 
  "Kan", "Kar", "Ker", "Kurr", "Kyr",
  "Man", "Mar", "Mer", "Mir", 
  "Tsal", "Tser", "Tsir",
  "Van", "Var", "Yur", "Yyr",
  NULL
};

const char *char_fantasy_mid[] = {
  "al","an","ar","el","en","ess","ian","onn","or",
  NULL
};

const char *char_fantasy_post_f[] = {
  "a", "ae", "aelle", "ai", "ea", "i", "ia", "u", "wen", "wyn",
  NULL
};

const char *char_fantasy_post_m[] = {
  "ai", "an", "ar", "ath", "en", "eo", "ian", "is", "u", "or",
  NULL
};

void NameGenerator::concatSyllable(char *dest, const char *syl1, const char *syl2)
{
  char tmp1[CHARMAX];
  int len1 = strlen(syl1);
  int len2 = strlen(syl2);
  sprintf(tmp1, "%s", syl1);
  if(len1 > 2 && len2 > 2 && toupper(syl1[len1 - 1]) == toupper(syl2[2]) 
    && toupper(syl1[len1 - 2]) == toupper(syl2[1]) && toupper(syl1[len1 - 3]) == toupper(syl2[0]))
  {
    // redundant 3 letters syllable as in "Gameshesh" => "Gamesh"
    tmp1[len1 - 3] = 0;
  }
  else if(len1 > 1 && len2 > 1 && toupper(syl1[len1 - 1]) == toupper(syl2[1]) 
    && toupper(syl1[len1 - 2]) == toupper(syl2[0]))
  {
    // redundant 2 letters syllable as in "Babaeth" => "Baeth"
    tmp1[len1 - 2] = 0;
  }
  else if(toupper(syl1[len1 - 1]) == toupper(syl2[0]))
  {
    // redundant letter as in "Baain" => "Bain"
    tmp1[len1 - 1] = 0;
  }
  sprintf(dest,"%s%s",tmp1,syl2);
}

int NameGenerator::count(const char **list)
{
  int ret = 0;
  while(*list)
  {
    list++;
    ret++;
  }
  return ret;
}

const char *NameGenerator::generateName(TCODRandom *ngRng, const char *pre[], const char *mid[], const char *post[])
{
  static char name[CHARMAX];
  int ipre, imid = -1, ipost;
  int nbpre, nbmid, nbpost;
  nbpre = count(&pre[0]);
  if(mid)
  {
    nbmid=count(&mid[0]);
    imid=ngRng->getInt(0, nbmid - 1);
  }
  nbpost = count(&post[0]);
  ipre = ngRng->getInt(0, nbpre - 1);
  ipost = ngRng->getInt(0, nbpost - 1);
  const char *spre = pre[ipre];
  const char *smid = mid ? mid[imid] : NULL;
  const char *spost = post[ipost];
  if(smid) 
  {
    concatSyllable(name, spre, smid);
    concatSyllable(name, name, spost);
  }
  else
  {
    concatSyllable(name, spre, spost);
  }
  name[0] = toupper(name[0]);
  return name;
}

const char *NameGenerator::generateRegionName(TCODRandom *ngRng)
{
  const char **mid = ngRng->getInt(0, 1) ? region_mid : NULL;
  return generateName(ngRng, region_pre, mid, region_post);
}

const char *NameGenerator::generateCityName(TCODRandom *ngRng)
{
  return generateName(ngRng, city_pre, NULL, city_post);
}

const char *NameGenerator::generateCelticName(TCODRandom *ngRng, bool male)
{
  const char **mid = ngRng->getInt(0, 1) ? char_celt_mid : NULL;
  return generateName(ngRng, char_celt_pre, mid, male ? char_celt_post_m : char_celt_post_f);
}

const char *NameGenerator::generateNorseName(TCODRandom *ngRng, bool male)
{
  const char **mid = ngRng->getInt(0, 1) ? char_norse_mid : NULL;
  return generateName(ngRng, char_norse_pre, mid, male ? char_norse_post_m : char_norse_post_f);
}

const char *NameGenerator::generateMesopotamianName(TCODRandom *ngRng, bool male)
{
  const char **mid = ngRng->getInt(0, 1) ? char_meso_mid : NULL;
  return generateName(ngRng, char_meso_pre, mid, male ? char_meso_post_m : char_meso_post_f);
}

const char *NameGenerator::generateFantasyName(TCODRandom *ngRng, bool male)
{
  const char **mid = ngRng->getInt(0, 1) ? char_fantasy_mid : NULL;
  return generateName(ngRng, char_fantasy_pre, mid, male ? char_fantasy_post_m : char_fantasy_post_f);
}

const char *NameGenerator::generateRandomName(TCODRandom *ngRng)
{
  int typ = ngRng->getInt(0, 4);
  switch(typ)
  {
    case 0: return generateRegionName(ngRng); break;
    case 1: return generateCelticName(ngRng, ngRng->getInt(0, 1) == 0); break;
    case 2: return generateNorseName(ngRng, ngRng->getInt(0, 1) == 0); break;
    case 3: return generateMesopotamianName(ngRng, ngRng->getInt(0, 1) == 0); break;
    default: return generateFantasyName(ngRng, ngRng->getInt(0, 1) == 0); break;
  }
}
