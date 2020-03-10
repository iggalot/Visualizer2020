#include "Visualizer.h"
#include "VisualizerFrame.h"
//#include "VisualizerHelper.h"

// ----------------------------------------------------------------------------
// MyFrame: main application window
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(VisualizerFrame, wxFrame)
EVT_MENU(wxID_NEW, VisualizerFrame::OnNewWindow)
//EVT_MENU(NEW_STEREO_WINDOW, VisualizerFrame::OnNewStereoWindow)
EVT_MENU(wxID_CLOSE, VisualizerFrame::OnClose)
wxEND_EVENT_TABLE()

VisualizerFrame::VisualizerFrame(bool stereoWindow)
    : wxFrame(NULL, wxID_ANY, "wxWidgets OpenGL Cube Sample")
{
    int stereoAttribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0 };

    new VisualizerCanvas(this, stereoWindow ? stereoAttribList : NULL);

    SetIcon(wxICON(sample));

    // Make a menubar
    wxMenu* menu = new wxMenu;
    menu->Append(wxID_NEW);
    //menu->Append(NEW_STEREO_WINDOW, "New Stereo Window");
    menu->AppendSeparator();
    menu->Append(wxID_CLOSE);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menu, "&Cube");

    SetMenuBar(menuBar);

    CreateStatusBar();

    SetClientSize(400, 400);
    Show();

    // test IsDisplaySupported() function:
    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
    wxLogStatus("Double-buffered display %s supported",
        wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

    if (stereoWindow)
    {
        const wxString vendor = VisualizerFrame::glGetwxString(GL_VENDOR).Lower();
        const wxString renderer = VisualizerFrame::glGetwxString(GL_RENDERER).Lower();
        if (vendor.find("nvidia") != wxString::npos &&
            renderer.find("quadro") == wxString::npos)
            ShowFullScreen(true);
    }
}

void VisualizerFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void VisualizerFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event))
{
    new VisualizerFrame();
}

//void VisualizerFrame::OnNewStereoWindow(wxCommandEvent& WXUNUSED(event))
//{
//    new VisualizerFrame(true);
//}

const wxString VisualizerFrame::glGetwxString(GLenum name)
{
        const GLubyte* v = glGetString(name);
        if (v == 0)
        {
            // The error is not important. It is GL_INVALID_ENUM.
            // We just want to clear the error stack.
            glGetError();

            return wxString();
        }

        return wxString((const char*)v);

}

