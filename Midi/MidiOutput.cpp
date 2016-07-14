// MidiOutput.cpp: implementation of the CMidiOutput class.
//
//////////////////////////////////////////////////////////////////////

#include "..\\stdafx.h"
//#include "FingerSmooth.h"
#include "MidiOutput.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma comment(lib, "winmm")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMidiOutput::CMidiOutput()
{
	m_hMidi = NULL;
}

CMidiOutput::~CMidiOutput()
{
    MIDIOutClose();
}

void CMidiOutput::InitializeMIDIDevices()
{
//	int i;
	MIDIOUTCAPS midicaps;
	BOOL isAdd;

	//Obj.Clear
	isAdd = false;
	if(midiOutGetDevCaps(MIDIMAPPER, &midicaps, sizeof(MIDIOUTCAPS)) == 0){		//若获取设备信息成功
//		  Obj.AddItem midicaps.szPname       '添加设备名称
//		  Obj.ItemData(Obj.NewIndex) = MIDIMAPPER   '这是默认设备ID  = -1
		isAdd = true;
	}
		//添加其他设备
	for(unsigned int i = 0; i < midiOutGetNumDevs(); ++i){
		if(midiOutGetDevCaps(i, &midicaps, sizeof(MIDIOUTCAPS)) == 0){
		  //Obj.AddItem midicaps.szPname
		  //Obj.ItemData(Obj.NewIndex) = i
		  isAdd = true;
		}//End If
	}
	//Midi_OutDevsToList = isAdd
}

void CMidiOutput::MIDIOutOpen(UINT dev_id)
{
    MIDIOutClose();
    m_uiMidiError = midiOutOpen(&m_hMidi, dev_id, 0, 0, 0);
	midi_outerr();
    //MIDI_OutOpen = (hMidi <> 0);
}

void CMidiOutput::MIDIOutClose()
{
    if(m_hMidi != 0){
        m_uiMidiError = midiOutClose(m_hMidi);
		midi_outerr();
        m_hMidi = 0;
    }
}

void CMidiOutput::midi_outerr()
{
	char s[128];

	if(m_uiMidiError != 0){
		midiOutGetErrorText(m_uiMidiError, s, MAXERRORLENGTH);
		AfxMessageBox(s, MB_OK, 0);
	}
}

void CMidiOutput::NoteOn(UCHAR ch, UCHAR kk, UCHAR v)
{
	midi_outshort(0x90 + ch, kk, v);
}

void CMidiOutput::NoteOff(UCHAR ch, UCHAR kk)
{
	midi_outshort(0x80 + ch, kk, 0);
}

void CMidiOutput::midi_outshort(UCHAR channel, UCHAR note, UCHAR volume){
    m_uiMidiError = midiOutShortMsg(m_hMidi, (volume<<16) | (note<<8) | channel);
	midi_outerr();
}

void CMidiOutput::StopAllNote()
{
	for(UCHAR i = 0; i < 128; ++i)
		NoteOff(0, i);
}
void CMidiOutput::InstrumentChange(UCHAR ch, UCHAR cc0nr, UCHAR pnr){
	ControllerChange(ch, 0, cc0nr);
	midi_outshort(0xC0 + ch, pnr, 0);
}
void CMidiOutput::ControllerChange(UCHAR ch, UCHAR ccnr, UCHAR v){
	midi_outshort(0xB0 + ch, ccnr, v);
}

/*

Sub midisetrpn(ch As Integer, pmsb As Integer, plsb As Integer, msb As Integer, lsb As Integer)
    Call midi_outshort(ch, &H65, pmsb)
    Call midi_outshort(ch, &H64, plsb)
    Call midi_outshort(ch, &H6, msb)
    Call midi_outshort(ch, &H26, lsb)
End Sub*/ 