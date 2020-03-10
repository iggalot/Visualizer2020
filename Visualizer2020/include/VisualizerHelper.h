#ifndef _VISUALIZER_HELPER_H_
#define _VISUALIZER_HELPER_H_

#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/glcanvas.h"

enum
{
    NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// control ids
enum
{
    SpinTimer = wxID_HIGHEST + 1
};

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;

    for (;; )
    {
        GLenum err = glGetError();
        if (err == GL_NO_ERROR)
            return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if (err == errLast)
        {
            wxLogError("OpenGL error state couldn't be reset.");
            return;
        }

        errLast = err;

        wxLogError("OpenGL error %d", err);
    }
}

// function to draw the texture for cube faces
static wxImage DrawDice(int size, unsigned num)
{
    wxASSERT_MSG(num >= 1 && num <= 6, "invalid dice index");

    const int dot = size / 16;        // radius of a single dot
    const int gap = 5 * size / 32;      // gap between dots

    wxBitmap bmp(size, size);
    wxMemoryDC dc;
    dc.SelectObject(bmp);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetBrush(*wxBLACK_BRUSH);

    // the upper left and lower right points
    if (num != 1)
    {
        dc.DrawCircle(gap + dot, gap + dot, dot);
        dc.DrawCircle(size - gap - dot, size - gap - dot, dot);
    }

    // draw the central point for odd dices
    if (num % 2)
    {
        dc.DrawCircle(size / 2, size / 2, dot);
    }

    // the upper right and lower left points
    if (num > 3)
    {
        dc.DrawCircle(size - gap - dot, gap + dot, dot);
        dc.DrawCircle(gap + dot, size - gap - dot, dot);
    }

    // finally those 2 are only for the last dice
    if (num == 6)
    {
        dc.DrawCircle(gap + dot, size / 2, dot);
        dc.DrawCircle(size - gap - dot, size / 2, dot);
    }

    dc.SelectObject(wxNullBitmap);

    return bmp.ConvertToImage();
}

#endif _VISUALIZER_HELPER_H_

