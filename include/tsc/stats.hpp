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

#include "global.hpp"

enum EStatus
{
  STATUS_DEAD,
  STATUS_DYING,
  STATUS_CRITICAL,
  STATUS_WOUNDED,
  STATUS_HEALTHY,
  STATUS_BURDENED,
  STATUS_POISONED,
  STATUS_WEAKENED,
  STATUS_SLUGGISH,
  STATUS_FEEBLE,
  STATUS_CONFUSED,
  NSTATUS
};

// The class that holds information about player/creature and equipment stats
class Stats
{
  public:
  int hpmax;        // Max. Health Points
  int ap, dp;        // Physical Attack and Defense Power
  int str, spd;        // Strength and Speed
  int mpmax;        // Max. Magic Points
  int map, mdp;        // Magic Attack and Defense Power
  int wil, acu;        // Willpower and Acuity

  Stats();        // The Stats Constructor
  Stats &operator+= (const Stats &rhs);  // The Compound Assignment Operator
  Stats &operator-= (const Stats &rhs);  // The Compound Assignment Operator
};

// The class that holds information about player/creature health status
struct Health
{
  bool status[NSTATUS];      // The health status flags
  char name[NSTATUS][CHARMAX];    // The health status name

  bool burdenedfirst;      // Burdened flag
  bool unburdenedfirst;      // Unburdened flag

  Health();        // The Health Status Constructor
};
