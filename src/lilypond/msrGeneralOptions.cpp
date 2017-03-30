/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>      // setw, set::precision, ...

#include "msr.h"

using namespace std;

namespace MusicXML2 
{

//_______________________________________________________________________________
S_msrGeneralOptions msrGeneralOptions::create ()
{
  msrGeneralOptions* o = new msrGeneralOptions();
  assert(o!=0);
  return o;
}

msrGeneralOptions::msrGeneralOptions ()
{
  initializeGeneralOptions ();
}

msrGeneralOptions::~msrGeneralOptions () {}

void msrGeneralOptions::initializeGeneralOptions ()
{
  // interactive mode
  fInteractive = false;
  
  // trace
  fTraceGeneral = false;
  
  fTraceVisitors = false;
  
  fTraceDivisions = false;

  fTraceParts = false;
  fTraceVoices = false;

  fTraceHarmony = false;
  

  fTraceScore = false;
  fTracePartgroups = false;
  fTraceStaves = false;
    
  fTraceSegments = false;
  fTraceMeasures = false;
  
  fTraceNotes = false;
  fTraceDurations = false;
  
  fTraceDynamics = false;
  fTraceWords = false;
  fTraceSlurs = false;
  fTraceLigatures = false;
  fTraceWedges = false;
  
  fTraceChords = false;
  fTraceTuplets = false;
  
  fTraceGracenotes = false;
  
  fTraceLyrics = false;
  
  fTraceWords = false;

  fTraceRepeats = false;
  
  fTraceStafftuning = false;
  
  fTraceMidi = false;

  fTraceALL = false;

  // debug
 // fDebug = false;
 // fDebugDebug = false;

  // forcing debug information at specific places in the code
 // fForceDebug = false;
  
    // timing information
  fDisplayCPUusage = false;

  // measure number-selective debug
  fSaveDebug = false;
  fSaveDebugDebug = false;
}

S_msrGeneralOptions gGeneralOptions;

}