#ifndef _VISUALIZER_CONTEXT_H_
#define _VISUALIZER_CONTEXT_H_

#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/glcanvas.h"

#pragma once
// the rendering context used by all GL canvases
class VisualizerContext : public wxGLContext
{
public:
    VisualizerContext(wxGLCanvas* canvas);

    // render the cube showing it at given angles
    void DrawRotatedCube(float xangle, float yangle);

private:
    // textures for the cube faces
    GLuint m_textures[6];
};

#endif // _VISUALIZER_CONTEXT_H_

