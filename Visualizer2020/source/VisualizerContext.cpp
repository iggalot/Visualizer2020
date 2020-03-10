#include "Visualizer.h"
#include "VisualizerContext.h"
#include "VisualizerHelper.h"



// ----------------------------------------------------------------------------
// TestGLContext
// ----------------------------------------------------------------------------

VisualizerContext::VisualizerContext(wxGLCanvas* canvas)
    : wxGLContext(canvas)
{
    SetCurrent(*canvas);

    // set up the parameters we want to use
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    // add slightly more light, the default lighting is rather dark
    GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // set viewing projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

    // create the textures to use for cube sides: they will be reused by all
    // canvases (which is probably not critical in the case of simple textures
    // we use here but could be really important for a real application where
    // each texture could take many megabytes)
    glGenTextures(WXSIZEOF(m_textures), m_textures);

    for (unsigned i = 0; i < WXSIZEOF(m_textures); i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        const wxImage img(DrawDice(256, i + 1));

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(),
            0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
    }

    CheckGLError();
}

void VisualizerContext::DrawRotatedCube(float xangle, float yangle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(xangle, 1.0f, 0.0f, 0.0f);
    glRotatef(yangle, 0.0f, 1.0f, 0.0f);

    // draw six faces of a cube of size 1 centered at (0, 0, 0)
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[1]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[2]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[3]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[4]);
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[5]);
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    glFlush();

    CheckGLError();
}


VisualizerContext& Visualizer::GetContext(wxGLCanvas* canvas, bool useStereo)
{
    VisualizerContext* glContext;
    if (useStereo)
    {
        if (!m_glStereoContext)
        {
            // Create the OpenGL context for the first stereo window which needs it:
            // subsequently created windows will all share the same context.
            m_glStereoContext = new VisualizerContext(canvas);
        }
        glContext = m_glStereoContext;
    }
    else
    {
        if (!m_glContext)
        {
            // Create the OpenGL context for the first mono window which needs it:
            // subsequently created windows will all share the same context.
            m_glContext = new VisualizerContext(canvas);
        }
        glContext = m_glContext;
    }

    glContext->SetCurrent(*canvas);

    return *glContext;
}
