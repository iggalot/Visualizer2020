#ifndef _VISUALIZER_FRAME_H_
#define _VISUALIZER_FRAME_H_


#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/glcanvas.h"

// Define a new frame type
class VisualizerFrame : public wxFrame
{
public:
    VisualizerFrame(bool stereoWindow = false);

private:
    void OnClose(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);
    //void OnNewStereoWindow(wxCommandEvent& event);

    const wxString glGetwxString(GLenum name);

    wxDECLARE_EVENT_TABLE();
};

#endif // _VISUALIZER_FRAME_H_
