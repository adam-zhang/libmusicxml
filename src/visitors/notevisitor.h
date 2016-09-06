/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef __noteVisitor__
#define __noteVisitor__

#include <stdlib.h>

#include <ostream>
#include <string>
#include <list>

#include "conversions.h"
#include "rational.h"
#include "typedefs.h"
#include "visitor.h"
#include "xml.h"

namespace MusicXML2 
{   

/*!
\addtogroup visitors
@{
*/

/*!
\brief A note visitor.
*/
class EXP notevisitor : 
  public visitor<S_accent>,
  public visitor<S_alter>,
  public visitor<S_beam>,
  public visitor<S_breath_mark>,
  public visitor<S_chord>,
  public visitor<S_cue>,
  public visitor<S_display_octave>,
  public visitor<S_display_step>,
  public visitor<S_dot>,
  public visitor<S_duration>,
  public visitor<S_fermata>,
  public visitor<S_grace>,
  public visitor<S_instrument>,
  public visitor<S_note>,
  public visitor<S_octave>,
  public visitor<S_pitch>,
  public visitor<S_syllabic>,
  public visitor<S_text>,
  public visitor<S_rest>,
  public visitor<S_slur>,
  public visitor<S_staccato>,
  public visitor<S_staff>,
  public visitor<S_stem>,
  public visitor<S_step>,
  public visitor<S_strong_accent>,
  public visitor<S_tenuto>,
  public visitor<S_tie>,
  public visitor<S_tied>,
  public visitor<S_time_modification>,
  public visitor<S_type>,
  public visitor<S_unpitched>,
  public visitor<S_voice>
{
  public:
    S_stem          fStem;
    S_accent        fAccent;
    S_strong_accent fStrongAccent;
    S_staccato      fStaccato;
    S_tenuto        fTenuto;
    S_breath_mark   fBreathMark;

    enum      { C, D, E, F, G, A, B, last=B, diatonicSteps=last };
    enum type { kUndefinedType, kPitched, kUnpitched, kRest };
    enum      { kUndefinedDynamics = -1, kUndefinedStaff = 0, kUndefinedVoice = 0 };

    notevisitor();
    virtual ~notevisitor() {}

    bool isGrace() const    { return fGrace; }
    bool isCue() const      { return fCue; }
    bool inChord() const    { return fChord; }
    bool inFermata() const  { return fFermata; }

    type  getType() const   { return fType; }
    int   getTie() const    { return fTie; }
    int   getStaff() const  { return fStaff; }
    int   getVoice() const  { return fVoice; }

    /*!
    \brief Compute the note MIDI pitch.
    \return The note MIDI pitch as a float value. 
    Decimal part of the value represents fine pitch and may be used to drive pitch bend messages.
    Returns -1 for non pitched notes.
    */
    virtual float getMidiPitch() const;
    virtual float getAlter() const  { return fAlter; }
    virtual int   getOctave() const { return fOctave; }

    virtual const std::string&  getStep() const           { return fStep; }
    virtual const std::string&  getInstrument() const     { return fInstrument; }
    virtual const std::string&  getGraphicType() const    { return fGraphicType; }
    virtual const rational&   getTimeModification() const { return fTimeModification; }
 
    virtual void setStep (const std::string& step)  { fStep = step; }
    virtual void setOctave (int oct)      { fOctave = oct; }
    virtual void setAlter (float alter)     { fAlter = alter; }

    // returns the dynamics value (kUndefinedDynamics when undefined)
    virtual long getDynamics() const  { return fDynamics; }
    virtual long getDuration() const  { return fDuration; }
    virtual int  getDots() const      { return fDots; }
    virtual void print (std::ostream& out) const;

    virtual const std::vector<S_tied>&  getTied() const { return fTied; }
    virtual const std::vector<S_slur>&  getSlur() const { return fSlur; }
    virtual const std::vector<S_beam>&  getBeam() const { return fBeam; }

    virtual const S_lyric&              getLastLyric() const { return fLastLyric; }
    virtual const S_syllabic&           getLastSyllabic() const { return fLastSyllabic; }
    virtual const std::map<std::string, std::list<std::list<std::string> > >&  
                                        getStanzas() const { return fStanzas; }

    static int          step2i(const std::string& step); 
    static std::string  i2step(int i);

  protected:
    bool fInNote;
    void reset();   

    virtual void visitEnd  ( S_note& elt );

    virtual void visitStart( S_accent& elt)     { fAccent = elt; }
    virtual void visitStart( S_alter& elt )     { if (fInNote) fAlter = (float)(*elt); }
    virtual void visitStart( S_beam& elt )      { fBeam.push_back (elt); }
    virtual void visitStart( S_breath_mark& elt)  { fBreathMark = elt; }
    virtual void visitStart( S_chord& elt )     { fChord = true; }
    virtual void visitStart( S_cue& elt )       { fCue = true; }
    virtual void visitStart( S_display_octave& elt ) { if (fInNote) fOctave = (int)(*elt); }
    virtual void visitStart( S_display_step& elt )  { if (fInNote) fStep = elt->getValue(); }
    virtual void visitStart( S_dot& elt )       { if (fInNote) fDots++; }
    virtual void visitStart( S_duration& elt )  { if (fInNote) fDuration = (int)(*elt); }
    virtual void visitStart( S_fermata& elt )   { fFermata = true; }
    virtual void visitStart( S_grace& elt )     { fGrace = true; }
    virtual void visitStart( S_instrument& elt ){ if (fInNote) fInstrument = elt->getValue(); }
    virtual void visitStart( S_note& elt );
    virtual void visitStart( S_octave& elt )    { if (fInNote) fOctave = (int)(*elt); }
    virtual void visitStart( S_pitch& elt )     { fType = kPitched; }
    virtual void visitStart( S_lyric& elt )     { fLastLyric = elt; }
    virtual void visitStart( S_syllabic& elt )  { fLastSyllabic = elt; }
    virtual void visitStart( S_text& elt );
    virtual void visitStart( S_rest& elt )      { fType = kRest; }
    virtual void visitStart( S_slur& elt )      { fSlur.push_back (elt); }
    virtual void visitStart( S_staccato& elt)   { fStaccato = elt; }
    virtual void visitStart( S_staff& elt)      { fStaff = int(*elt); }
    virtual void visitStart( S_stem& elt )      { fStem = elt; }
    virtual void visitStart( S_step& elt )      { if (fInNote) fStep = elt->getValue(); }
    virtual void visitStart( S_strong_accent& elt)  { fStrongAccent = elt; }
    virtual void visitStart( S_tenuto& elt)     { fTenuto = elt; }
    virtual void visitStart( S_tie& elt );
    virtual void visitStart( S_tied& elt )      { fTied.push_back (elt); }
    virtual void visitStart( S_time_modification& elt );
    virtual void visitStart( S_type& elt )      { if (fInNote) fGraphicType = elt->getValue(); }
    virtual void visitStart( S_unpitched& elt ) { if (fInNote) fType = kUnpitched; }
    virtual void visitStart( S_voice& elt )     { fVoice = int(*elt); }

  private:
    bool                fGrace, fCue, fChord, fFermata;
    type                fType;
    int                 fDots;
    StartStop::type     fTie;
    long                fDuration, fDynamics;
    std::string         fStep, fGraphicType;
    float               fAlter;
    int                 fOctave;
    int                 fStaff, fVoice;
    rational            fTimeModification;
    std::string         fInstrument;

    std::vector<S_tied> fTied;
    std::vector<S_slur> fSlur;
    std::vector<S_beam> fBeam;
    
    // the last lyric number, i.e. stanza number
    S_lyric             fLastLyric;
    // the last sysllabic spec met (single, begin, middle or end)
    S_syllabic          fLastSyllabic; 
 
    // the stanzas are referred to by number and contains list of lists of strings
    // in the case of "single", the list contains only one string
    std::map<std::string, std::list<std::list<std::string> > > 
                        fStanzas;    // <text /> occurs after <syllabic />
};

EXP std::ostream& operator<< (std::ostream& os, const notevisitor& elt);

/*! @} */

}

#endif
