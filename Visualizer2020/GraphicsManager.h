#pragma once
class Visualizer;

class GraphicsManager
{
public:
	Visualizer *ptrVisualizer;

	// Default constructor
	GraphicsManager(Visualizer *vis)
	{
		ptrVisualizer = vis;
	}

	double WinHt() { return ptrVisualizer->GetWinHt(); }
	double WinWidth() {
		return ptrVisualizer->GetWinWidth();
	}
};

