/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef __msr2LpsrVisitor__
#define __msr2LpsrVisitor__

#include <map>
#include <vector>

#include "lpsr.h"

//#include "musicxml2msr.h"

namespace MusicXML2
{

/*!
\addtogroup visitors
@{
*/

/*!
\brief Produces a summary of a MusicXML part.

  A part summary consists in 
  - a number of staves
  - a map that associates each stave with the corresponding number of notes
  - a map that associates each stave with the corresponding voices and notes
  - a map that associates each stave with the correcponding lyricss
*/
class msr2LpsrVisitor :

  public visitor<S_msrScore>,
  
  public visitor<S_msrIdentification>,
  
  public visitor<S_msrPartgroup>,
  
  public visitor<S_msrPart>,
  
  public visitor<S_msrStaff>,
  
  public visitor<S_msrVoice>,

  public visitor<S_msrLyrics>,
  public visitor<S_msrLyricschunk>,
  
  public visitor<S_msrClef>,
  public visitor<S_msrKey>,
  public visitor<S_msrTime>,
  
  public visitor<S_msrWords>,
  
  public visitor<S_msrTempo>,
  
  public visitor<S_msrVoicechunk>,
  
  public visitor<S_msrMeasure>,
    
  public visitor<S_msrArticulation>,
  
  public visitor<S_msrOrnament>,

  public visitor<S_msrDynamics>,
  public visitor<S_msrSlur>,
  public visitor<S_msrWedge>,
  
  public visitor<S_msrGracenotes>,
  
  public visitor<S_msrNote>,
  public visitor<S_msrOctaveShift>,
  
  public visitor<S_msrStem>,
  public visitor<S_msrBeam>,
    
  public visitor<S_msrChord>,
  
  public visitor<S_msrTuplet>,
  
  public visitor<S_msrTie>,
    
  public visitor<S_msrBarline>,
  
  public visitor<S_msrSegno>,
  public visitor<S_msrCoda>,
  
  public visitor<S_msrEyeglasses>,
  public visitor<S_msrPedal>,

  public visitor<S_msrBarCheck>,
  public visitor<S_msrBarnumberCheck>,
  
  public visitor<S_msrBreak>,
  
  public visitor<S_msrRepeat>,
  public visitor<S_msrRepeatending>,
  
//  public visitor<S_msrComment>, // JMI
  
  public visitor<S_msrVarValAssoc>,
  
  public visitor<S_msrPageGeometry>,
  public visitor<S_msrLayout>,
  
  public visitor<S_msrRehearsal>,
  
  public visitor<S_msrMidi>

{
  public:
  
    msr2LpsrVisitor (
      S_msrOptions&  msrOpts,
      S_lpsrOptions& lpsrOpts,
      ostream&       os,
      S_msrScore     mScore);
        
    virtual ~msr2LpsrVisitor ();

    void buildLpsrScoreFromMsrScore ();

    S_lpsrScore getLpsrScore () const
        { return fLpsrScore; };
    
  protected:
      
    virtual void visitStart (S_msrScore& elt);
    virtual void visitEnd   (S_msrScore& elt);

    virtual void visitStart (S_msrIdentification& elt);
    virtual void visitEnd   (S_msrIdentification& elt);

    virtual void visitStart (S_msrPartgroup& elt);
    virtual void visitEnd   (S_msrPartgroup& elt);

    virtual void visitStart (S_msrPart& elt);
    virtual void visitEnd   (S_msrPart& elt);

    virtual void visitStart (S_msrStaff& elt);
    virtual void visitEnd   (S_msrStaff& elt);

    virtual void visitStart (S_msrVoice& elt);
    virtual void visitEnd   (S_msrVoice& elt);

    virtual void visitStart (S_msrLyrics& elt);
    virtual void visitEnd   (S_msrLyrics& elt);

    virtual void visitStart (S_msrLyricschunk& elt);
    virtual void visitEnd   (S_msrLyricschunk& elt);

    virtual void visitStart (S_msrClef& elt);
    virtual void visitEnd   (S_msrClef& elt);

    virtual void visitStart (S_msrKey& elt);
    virtual void visitEnd   (S_msrKey& elt);

    virtual void visitStart (S_msrTime& elt);
    virtual void visitEnd   (S_msrTime& elt);

    virtual void visitStart (S_msrWords& elt);
    virtual void visitEnd   (S_msrWords& elt);

    virtual void visitStart (S_msrTempo& elt);
    virtual void visitEnd   (S_msrTempo& elt);

    virtual void visitStart (S_msrVoicechunk& elt);
    virtual void visitEnd   (S_msrVoicechunk& elt);

    virtual void visitStart (S_msrMeasure& elt);
    virtual void visitEnd   (S_msrMeasure& elt);

    virtual void visitStart (S_msrArticulation& elt);
    virtual void visitEnd   (S_msrArticulation& elt);

    virtual void visitStart (S_msrOrnament& elt);
    virtual void visitEnd   (S_msrOrnament& elt);

    virtual void visitStart (S_msrDynamics& elt);
    virtual void visitEnd   (S_msrDynamics& elt);

    virtual void visitStart (S_msrWedge& elt);
    virtual void visitEnd   (S_msrWedge& elt);

    virtual void visitStart (S_msrGracenotes& elt);
    virtual void visitEnd   (S_msrGracenotes& elt);

    virtual void visitStart (S_msrNote& elt);
    virtual void visitEnd   (S_msrNote& elt);

    virtual void visitStart (S_msrOctaveShift& elt);
    virtual void visitEnd   (S_msrOctaveShift& elt);

    virtual void visitStart (S_msrStem& elt);
    virtual void visitEnd   (S_msrStem& elt);

    virtual void visitStart (S_msrBeam& elt);
    virtual void visitEnd   (S_msrBeam& elt);

    virtual void visitStart (S_msrChord& elt);
    virtual void visitEnd   (S_msrChord& elt);

    virtual void visitStart (S_msrTuplet& elt);
    virtual void visitEnd   (S_msrTuplet& elt);

    virtual void visitStart (S_msrTie& elt);
    virtual void visitEnd   (S_msrTie& elt);

    virtual void visitStart (S_msrSlur& elt);
    virtual void visitEnd   (S_msrSlur& elt);

    virtual void visitStart (S_msrBarline& elt);
    virtual void visitEnd   (S_msrBarline& elt);

    virtual void visitStart (S_msrSegno& elt);
    virtual void visitStart (S_msrCoda& elt);

    virtual void visitStart (S_msrEyeglasses& elt);
    virtual void visitStart (S_msrPedal& elt);

    virtual void visitStart (S_msrBarCheck& elt);
    virtual void visitEnd   (S_msrBarCheck& elt);
    virtual void visitStart (S_msrBarnumberCheck& elt);
    virtual void visitEnd   (S_msrBarnumberCheck& elt);

    virtual void visitStart (S_msrBreak& elt);
    virtual void visitEnd   (S_msrBreak& elt);

    virtual void visitStart (S_msrRepeat& elt);
    virtual void visitEnd   (S_msrRepeat& elt);
    virtual void visitStart (S_msrRepeatending& elt);
    virtual void visitEnd   (S_msrRepeatending& elt);

//    virtual void visitStart (S_msrComment& elt);
//    virtual void visitEnd   (S_msrComment& elt);

    virtual void visitStart (S_msrVarValAssoc& elt);
    virtual void visitEnd   (S_msrVarValAssoc& elt);

    virtual void visitStart (S_msrPageGeometry& elt);
    virtual void visitEnd   (S_msrPageGeometry& elt);

    virtual void visitStart (S_msrLayout& elt);
    virtual void visitEnd   (S_msrLayout& elt);

    virtual void visitStart (S_msrRehearsal& elt);
    virtual void visitEnd   (S_msrRehearsal& elt);

    virtual void visitStart (S_msrMidi& elt);
    virtual void visitEnd   (S_msrMidi& elt);

  private:
                     
    S_msrOptions              fMsrOptions;
    S_lpsrOptions             fLpsrOptions;
    
    ostream&                  fOstream;
    
    S_msrScore                fVisitedMsrScore;

    // the LPSR score we're building
    // ------------------------------------------------------
    S_lpsrScore               fLpsrScore;

    // it's header
    // ------------------------------------------------------
    S_lpsrHeader              fLpsrScoreHeader;

    // score
    // ------------------------------------------------------
    S_msrScore                fCurrentScoreClone;
    
    // identification
    // ------------------------------------------------------
    bool                      fOnGoingIdentification;

    // header
    // ------------------------------------------------------
    bool                      fWorkNumberKnown;
    bool                      fWorkTitleKnown;
    bool                      fMovementNumberKnown;
    bool                      fMovementTitleKnown;
    

    // page geometry
    // ------------------------------------------------------
// JMI    S_msrPageGeometry    fCurrentPageGeometry;
    
    // part groups
    // ------------------------------------------------------
    S_msrPartgroup            fCurrentPartgroupClone;
    // the current partgroup command is the top of the stack
    stack<S_lpsrPartgroupBlock>
                              fPartgroupBlocksStack;
    
    // parts
    // ------------------------------------------------------
    S_msrPart                 fCurrentPartClone;
    S_lpsrPartBlock           fCurrentPartBlock;
    
    // staves
    // ------------------------------------------------------
    S_msrStaff                fCurrentStaffClone;
    S_lpsrStaffBlock          fCurrentStaffBlock;
    // prevent clef, key and time from being handled twice
    bool                      fOnGoingStaff;

    // repeats
    // ------------------------------------------------------
    S_msrRepeat               fCurrentRepeatClone;
    bool                      fOnGoingRepeat;
 //   S_lpsrRepeatalternative fCurrentLpsrRepeatalternative;

    // measures
    // ------------------------------------------------------
    S_msrMeasure              fCurrentMeasureClone;
    
    // voice chunks
    // ------------------------------------------------------
    S_msrVoicechunk           fCurrentVoicechunkClone;
    
    // voices
    // ------------------------------------------------------    
    S_msrVoice                fCurrentVoiceClone;
    
    // lyrics
    // ------------------------------------------------------
    S_msrLyrics               fCurrentLyricsClone;

    // lyrics chunks
    // ------------------------------------------------------
    S_msrLyricschunk          fCurrentLyricschunkClone;

    // notes
    // ------------------------------------------------------
    bool                      fOnGoingNote;
    S_msrNote                 fCurrentNoteClone;

    // stems
    // ------------------------------------------------------
    S_msrStem                 fCurrentStem;
    
    // grace notes
    // ------------------------------------------------------
    S_msrGracenotes           fCurrentGracenotesClone;
    
    // chords
    // ------------------------------------------------------
    bool                      fOnGoingChord;
    S_msrChord                fCurrentChordClone;
    
    // tuplets
    // ------------------------------------------------------
//    S_msrTuplet             fCurrentTupletClone;
    bool                      fOnGoingTuplet;
    stack<S_msrTuplet>        fTupletClonesStack;
};


/*! @} */

}

#endif