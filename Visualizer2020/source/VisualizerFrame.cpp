#include "Visualizer.h"
#include "VisualizerFrame.h"
//#include "VisualizerHelper.h"

// ----------------------------------------------------------------------------
// MyFrame: main application window
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(VisualizerFrame, wxFrame)
EVT_MENU(wxID_NEW, VisualizerFrame::OnNewWindow)
EVT_MENU(wxID_CLOSE, VisualizerFrame::OnClose)
wxEND_EVENT_TABLE()

VisualizerFrame::VisualizerFrame(GLuint wid, GLuint ht) : wxFrame(NULL, wxID_ANY, "Visualizer 1.0")
{
    width = wid;
    height = ht;

    new VisualizerCanvas(this, NULL);

    SetIcon(wxICON(sample));

    // Make a menubar
    wxMenu* menu = new wxMenu;
    menu->Append(wxID_NEW);
    menu->AppendSeparator();
    menu->Append(wxID_CLOSE);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menu, "&File");

    SetMenuBar(menuBar);

    CreateStatusBar();

    SetClientSize(width,height);
    Show();

    // test IsDisplaySupported() function:
    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
    wxLogStatus("Double-buffered display %s supported",
        wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");
}

void VisualizerFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void VisualizerFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event))
{
    new VisualizerFrame(width, height);
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


