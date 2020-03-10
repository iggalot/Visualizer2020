/////////////////////////////////////////////////////////////////////////////
// Name:        cube.h
// Purpose:     wxGLCanvas demo program
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include "VisualizerCanvas.h"
#include "VisualizerContext.h"
#include "VisualizerFrame.h"

// Define a new application type
class Visualizer : public wxApp
{
public:
    Visualizer() { m_glContext = NULL; m_glStereoContext = NULL; }

    // Returns the shared context used by all frames and sets it as current for
    // the given canvas.
    VisualizerContext& GetContext(wxGLCanvas* canvas, bool useStereo);

    // virtual wxApp methods
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;

private:
    // the GL context we use for all our mono rendering windows
    VisualizerContext* m_glContext;
    // the GL context we use for all our stereo rendering windows
    VisualizerContext* m_glStereoContext;
};


// Application instance declaration
DECLARE_APP(Visualizer)

#endif // _VISUALIZER_H_

