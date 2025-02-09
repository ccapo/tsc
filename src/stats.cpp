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
// Copyright (c) 2009 J.C.Wilk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of J.C.Wilk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY J.C.WILK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL J.C.WILK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.hpp"

const char *statusName[NSTATUS] = {
  "Dead",
  "Dying",
  "Critical",
  "Wounded",
  "Healthy",
  "Burdened",
  "Poisoned",
  "Weakened",
  "Sluggish",
  "Feeble",
  "Confused"
};

// The Stats Constructor
Stats::Stats(): hpmax(HPMIN), ap(APMIN), dp(DPMIN), str(STRMIN), spd((SPDMAX - SPDMIN)/2), mpmax(MPMIN), map(MAPMIN), mdp(MDPMIN), wil(WILMIN), acu(ACUMIN) {}

// The Compound Assignment Operator
Stats &Stats::operator+= (const Stats &rhs)
{
  // Do the compound assignment work
  //this->hpmax += rhs.hpmax;
  this->ap    += rhs.ap;
  this->dp    += rhs.dp;
  this->str   += rhs.str;
  this->spd   += rhs.spd;
  //this->mpmax += rhs.mpmax;
  this->map   += rhs.map;
  this->mdp   += rhs.mdp;
  this->wil   += rhs.wil;
  this->acu   += rhs.acu;

  return *this;
}

// The Compound Assignment Operator
Stats &Stats::operator-= (const Stats &rhs)
{
  // Do the compound assignment work
  this->ap    -= rhs.ap;
  this->dp    -= rhs.dp;
  this->str   -= rhs.str;
  this->spd   -= rhs.spd;
  this->map   -= rhs.map;
  this->mdp   -= rhs.mdp;
  this->wil   -= rhs.wil;
  this->acu   -= rhs.acu;

  return *this;
}

// The Health Status Constructor
Health::Health(): burdenedfirst(true), unburdenedfirst(false)
{
  for(int i = 0; i < NSTATUS; i++)
  {
    status[i] = false;
    sprintf(name[i], "%s", statusName[i]);
  }
  status[STATUS_HEALTHY] = true;
}
