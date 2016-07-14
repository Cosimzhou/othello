// MidiOutput.h: interface for the CMidiOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIOUTPUT_H__E43A61D7_4217_410D_B94B_14E032525942__INCLUDED_)
#define AFX_MIDIOUTPUT_H__E43A61D7_4217_410D_B94B_14E032525942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMSystem.h"

class CMidiOutput  
{
public:
	void StopAllNote();
	void midi_outerr();
	void MIDIOutClose();
	void MIDIOutOpen(UINT);
	void InitializeMIDIDevices();
	CMidiOutput();
	virtual ~CMidiOutput();
	void InstrumentChange(UCHAR ch, UCHAR cc0nr, UCHAR pnr);
	void ControllerChange(UCHAR ch, UCHAR cc0nr, UCHAR v);

	void NoteOn(UCHAR ch, UCHAR kk, UCHAR v);
	void NoteOff(UCHAR ch, UCHAR kk);
	inline void midi_outshort(UCHAR channel, UCHAR note, UCHAR volume);
protected:
	HMIDIOUT m_hMidi;
	UINT m_uiMidiError;
};

#endif // !defined(AFX_MIDIOUTPUT_H__E43A61D7_4217_410D_B94B_14E032525942__INCLUDED_)
