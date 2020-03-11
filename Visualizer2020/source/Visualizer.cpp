#include "Visualizer.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../../sample.xpm"
#endif


class GraphicsManager;

// ----------------------------------------------------------------------------
// MyApp: the application object
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(Visualizer);

bool Visualizer::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    new VisualizerFrame(this->GetWinWidth(), this->GetWinHt());

    return true;
}

int Visualizer::OnExit()
{
    delete m_glContext;
    delete m_glStereoContext;

    return wxApp::OnExit();
}





