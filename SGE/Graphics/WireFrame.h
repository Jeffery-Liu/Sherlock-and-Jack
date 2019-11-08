#ifndef INCLUDED_WIREFRAME_H
#define INCLUDED_WIREFRAME_H

//====================================================================================================
// Filename:	WireFrame.h
// Description:	Class for line rendering.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <d3dx9.h>
#include <vector>

//====================================================================================================
// Class Declarations
//====================================================================================================

class WireFrame
{
public:
	// Constructor
	WireFrame();
	WireFrame(const WireFrame&);

	// Destructor
	virtual ~WireFrame();

	// Function to create/destroy a new wireframe
	void Create();
	void Destroy();

	// Function to render the wireframe
	virtual void Render();

	// Functions to add lines
	void AddLine(float x0, float y0, float x1, float y1);
	void AddRect(float x, float y, float w, float h);
	void AddCircle(float x, float y, float r);

	// Function to remove all lines
	void Purge();

	// Function to set line width
	void SetLineWidth(float fLineWidth);

	// Function to set line color
	void SetColor(DWORD rgb);

protected:
	// Members
	std::vector<D3DXVECTOR2> mVertices;

	ID3DXLine* mpLineRenderer;

	D3DXCOLOR mColor;
};

#endif // #ifndef INCLUDED_WIREFRAME_H