// vol_control.c

int ToggleMute(BOOL bToggle) {
    // most of this is copied and pasted from SetMasterVolume.. 
    // ..which in turn i half re-wrote from something on koders
    DWORD dwSpeakerControlID;

    // OPEN HANDLE TO MIXER 0
    HANDLE hMixer;
    if (mixerOpen((LPHMIXER) & hMixer, 0, 0, 0, 0) != MMSYSERR_NOERROR) {
        return 1;
    }

    // OBTAIN SPEAKER CONTROL ID
    MIXERLINE mxrline;
    mxrline.cbStruct = sizeof (MIXERLINE);
    mxrline.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
    mixerGetLineInfo(hMixer,
            &mxrline,
            MIXER_GETLINEINFOF_COMPONENTTYPE);

    MIXERLINECONTROLS mxrlinectrl;
    MIXERCONTROL mxrctrl;
    mxrlinectrl.cbStruct = sizeof (MIXERLINECONTROLS);
    mxrlinectrl.dwLineID = mxrline.dwLineID;
    mxrlinectrl.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
    mxrlinectrl.cbmxctrl = sizeof (MIXERCONTROL);
    mxrlinectrl.pamxctrl = &mxrctrl;
    mxrctrl.cbStruct = sizeof (MIXERCONTROL);

    mixerGetLineControls(hMixer,
            &mxrlinectrl,
            MIXER_GETLINECONTROLSF_ONEBYTYPE);

    dwSpeakerControlID = mxrctrl.dwControlID; // all for this..

    // GO AHEAD AND SET VOLUME    

    MIXERCONTROLDETAILS mcd;
    MIXERCONTROLDETAILS_BOOLEAN paDetails;

    ZeroMemory(&paDetails, sizeof (paDetails));
    mcd.paDetails = &paDetails;
    mcd.cbDetails = sizeof (paDetails);

    mcd.cbStruct = sizeof (mcd);

    mcd.dwControlID = dwSpeakerControlID;
    mcd.cChannels = 1; // 'all channels' 
    mcd.cMultipleItems = 0;

    paDetails.fValue = bToggle;

    if (mixerSetControlDetails(hMixer,
            &mcd,
            MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR) {
        // something along the line messed up
        mixerClose(hMixer);
        return 1;
    }

    mixerClose(hMixer);
    return 0;
}

int SetMasterVolume(int volPercent) {

    DWORD dwSpeakerControlID;

    // OPEN HANDLE TO MIXER 0
    HANDLE hMixer;
    if (mixerOpen((LPHMIXER) & hMixer, 0, 0, 0, 0) != MMSYSERR_NOERROR) {
        return 1;
    }

    // OBTAIN SPEAKER CONTROL ID
    MIXERLINE mxrline;
    mxrline.cbStruct = sizeof (MIXERLINE);
    mxrline.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
    mixerGetLineInfo(hMixer,
            &mxrline,
            MIXER_GETLINEINFOF_COMPONENTTYPE);

    MIXERLINECONTROLS mxrlinectrl;
    MIXERCONTROL mxrctrl;
    mxrlinectrl.cbStruct = sizeof (MIXERLINECONTROLS);
    mxrlinectrl.dwLineID = mxrline.dwLineID;
    mxrlinectrl.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
    mxrlinectrl.cbmxctrl = sizeof (MIXERCONTROL);
    mxrlinectrl.pamxctrl = &mxrctrl;
    mxrctrl.cbStruct = sizeof (MIXERCONTROL);

    mixerGetLineControls(hMixer,
            &mxrlinectrl,
            MIXER_GETLINECONTROLSF_ONEBYTYPE);

    dwSpeakerControlID = mxrctrl.dwControlID; // all for this..

    // GO AHEAD AND SET VOLUME    

    MIXERCONTROLDETAILS mcd;
    MIXERCONTROLDETAILS_UNSIGNED paDetails;

    ZeroMemory(&paDetails, sizeof (paDetails));
    mcd.paDetails = &paDetails;
    mcd.cbDetails = sizeof (paDetails);

    mcd.cbStruct = sizeof (mcd);

    mcd.dwControlID = dwSpeakerControlID;
    mcd.cChannels = 1; // 'all channels' 
    mcd.cMultipleItems = 0;

    paDetails.dwValue = (unsigned short) ((volPercent * 65535.0) / 100); // pump pump pump it up

    if (mixerSetControlDetails(hMixer,
            &mcd,
            MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR) {
        // something along the line messed up
        mixerClose(hMixer);
        return 1;
    }

    mixerClose(hMixer);
    return 0;
}

