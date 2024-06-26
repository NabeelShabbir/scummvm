/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef VECTOR_RENDERER_H
#define VECTOR_RENDERER_H

#include "common/rect.h"
#include "common/scummsys.h"
#include "common/str.h"

#include "graphics/managed_surface.h"

#include "gui/ThemeEngine.h"

class OSystem;

namespace Graphics {
class VectorRenderer;
struct DrawStep;

/**
 * @defgroup graphics_vector_renderer Vector renderer
 * @ingroup graphics
 *
 * @brief VectorRenderer for drawing on a given surface.
 *
 * @{
 */

typedef void (VectorRenderer::*DrawingFunctionCallback)(const Common::Rect &, const Graphics::DrawStep &);


struct DrawStep {
	DrawingFunctionCallback drawingCall; /**< Pointer to drawing function */
	Graphics::ManagedSurface *blitSrc;
	Graphics::AlphaType alphaType;

	struct Color {
		uint8 r, g, b;
		bool set;

		Color () : r(0), g(0), b(0), set(false) {}
	};
	Color fgColor; /**< Foreground color */
	Color bgColor; /**< background color */
	Color gradColor1; /**< gradient start*/
	Color gradColor2; /**< gradient end */
	Color bevelColor;

	bool autoWidth, autoHeight;
	int16 x, y, w, h; /**< width, height and position, if not measured automatically.
						  negative values mean counting from the opposite direction */

	Common::Rect padding;
	Common::Rect clip; /**< Clipping rect restriction */

	enum VectorAlignment {
		kVectorAlignManual,
		kVectorAlignLeft,
		kVectorAlignRight,
		kVectorAlignBottom,
		kVectorAlignTop,
		kVectorAlignCenter
	};

	VectorAlignment xAlign;
	VectorAlignment yAlign;

	uint8 shadow, stroke, factor, radius, bevel; /**< Misc options... */

	uint8 fillMode; /**< active fill mode */
	uint8 shadowFillMode; /**< fill mode of the shadow used */

	uint32 extraData; /**< Generic parameter for extra options (orientation/bevel) */

	uint32 scale; /**< scale of all the coordinates in FIXED POINT with 16 bits mantissa */

	uint32 shadowIntensity; /**< interval for drawing shadows in FIXED POINT with 16 bits mantissa */

	GUI::ThemeEngine::AutoScaleMode autoscale; /**< scale alphaimage if present */

	DrawStep() {
		drawingCall = nullptr;
		blitSrc = nullptr;
		alphaType = Graphics::ALPHA_OPAQUE;
		// fgColor, bgColor, gradColor1, gradColor2, bevelColor initialized by Color default constructor
		autoWidth = autoHeight = false;
		x = y = w = h = 0;
		// padding initialized by Common::Rect default constructor
		xAlign = yAlign = kVectorAlignManual;
		shadow = stroke = factor = radius = bevel = 0;
		fillMode = 0;
		shadowFillMode = 0;
		extraData = 0;
		scale = 0;
		shadowIntensity = 1 << 16;
		autoscale = GUI::ThemeEngine::kAutoScaleNone;
	}
};

VectorRenderer *createRenderer(int mode);

/**
 * VectorRenderer: The core Vector Renderer Class
 *
 * This virtual class exposes the API with all the vectorial
 * rendering functions that may be used to draw on a given Surface.
 *
 * This class must be instantiated as one of its children, which implement
 * the actual rendering functionality for each Byte Depth / Byte Format
 * combination, and may also contain platform specific code.
 *
 * When specifying define DISABLE_FANCY_THEMES eye candy related code
 * gets stripped off. This is especially useful for small devices like NDS.
 *
 * TODO: Expand documentation.
 *
 * @see VectorRendererSpec
 * @see VectorRendererAA
 */
class VectorRenderer {
public:
	VectorRenderer() : _activeSurface(NULL), _fillMode(kFillDisabled), _shadowOffset(0), _shadowFillMode(kShadowExponential),
		_disableShadows(false), _strokeWidth(1), _gradientFactor(1), _bevel(0), _dynamicData(0) {

	}

	virtual ~VectorRenderer() {}

	/** Specifies the way in which a shape is filled */
	enum FillMode {
		kFillDisabled = 0,
		kFillForeground = 1,
		kFillBackground = 2,
		kFillGradient = 3
	};

	enum TriangleOrientation {
		kTriangleAuto = 0,
		kTriangleUp,
		kTriangleDown,
		kTriangleLeft,
		kTriangleRight
	};

	enum ShadowFillMode {
		kShadowLinear = 0,
		kShadowExponential = 1
	};

	/**
	 * Draws a line by considering the special cases for optimization.
	 *
	 * @param x1 Horizontal (X) coordinate for the line start
	 * @param x2 Horizontal (X) coordinate for the line end
	 * @param y1 Vertical (Y) coordinate for the line start
	 * @param y2 Vertical (Y) coordinate for the line end
	 */
	virtual void drawLine(int x1, int y1, int x2, int y2) = 0;

	/**
	 * Draws a circle centered at (x,y) with radius r.
	 *
	 * @param x Horizontal (X) coordinate for the center of the circle
	 * @param y Vertical (Y) coordinate for the center of the circle
	 * @param r Radius of the circle.
	 */
	virtual void drawCircle(int x, int y, int r) = 0;

	/**
	 * Draws a square starting at (x,y) with the given width and height.
	 *
	 * @param x Horizontal (X) coordinate for the center of the square
	 * @param y Vertical (Y) coordinate for the center of the square
	 * @param w Width of the square.
	 * @param h Height of the square
	 */
	virtual void drawSquare(int x, int y, int w, int h) = 0;

	/**
	 * Draws a rounded square starting at (x,y) with the given width and height.
	 * The corners of the square are rounded with the given radius.
	 *
	 * @param x Horizontal (X) coordinate for the center of the square
	 * @param y Vertical (Y) coordinate for the center of the square
	 * @param w Width of the square.
	 * @param h Height of the square
	 * @param r Radius of the corners.
	 */
	virtual void drawRoundedSquare(int x, int y, int r, int w, int h) = 0;

	/**
	 * Draws a triangle starting at (x,y) with the given base and height.
	 * The triangle will always be isosceles, with the given base and height.
	 * The orientation parameter controls the position of the base of the triangle.
	 *
	 * @param x Horizontal (X) coordinate for the top left corner of the triangle
	 * @param y Vertical (Y) coordinate for the top left corner of the triangle
	 * @param base Width of the base of the triangle
	 * @param height Height of the triangle
	 * @param orient Orientation of the triangle.
	 */
	virtual void drawTriangle(int x, int y, int base, int height, TriangleOrientation orient) = 0;

	/**
	 * Draws a beveled square like the ones in the Classic GUI themes.
	 * Beveled squares are always drawn with a transparent background. Draw them on top
	 * of a standard square to fill it.
	 *
	 * @param x Horizontal (X) coordinate for the center of the square
	 * @param y Vertical (Y) coordinate for the center of the square
	 * @param w Width of the square.
	 * @param h Height of the square
	 * @param bevel Amount of bevel. Must be positive.
	 */
	virtual void drawBeveledSquare(int x, int y, int w, int h) = 0;

	/**
	 * Draws a tab-like shape, specially thought for the Tab widget.
	 * If a radius is given, the tab will have rounded corners. Otherwise,
	 * the tab will be squared.
	 *
	 * @param x Horizontal (X) coordinate for the tab
	 * @param y Vertical (Y) coordinate for the tab
	 * @param w Width of the tab
	 * @param h Height of the tab
	 * @param r Radius of the corners of the tab (0 for squared tabs).
	 * @param s Shadow size
	 */
	virtual void drawTab(int x, int y, int r, int w, int h, int s) = 0;

	/**
	 * Simple helper function to draw a cross.
	 */
	virtual void drawCross(int x, int y, int w, int h) {
		drawLine(x, y, x + w, y + w);
		drawLine(x + w, y, x, y + h);
	}

	/**
	 * Set the active foreground painting color for the renderer.
	 * All the foreground drawing from then on will be done with that color, unless
	 * specified otherwise.
	 *
	 * Foreground drawing means all outlines and basic shapes.
	 *
	 * @param r	value of the red color byte
	 * @param g	value of the green color byte
	 * @param b	value of the blue color byte
	 */
	virtual void setFgColor(uint8 r, uint8 g, uint8 b) = 0;

	/**
	 * Set the active background painting color for the renderer.
	 * All the background drawing from then on will be done with that color, unless
	 * specified otherwise.
	 *
	 * Background drawing means all the shape filling.
	 *
	 * @param r	value of the red color byte
	 * @param g	value of the green color byte
	 * @param b	value of the blue color byte
	 */
	virtual void setBgColor(uint8 r, uint8 g, uint8 b) = 0;

	virtual void setBevelColor(uint8 r, uint8 g, uint8 b) = 0;

	/**
	 * Set the active gradient color. All shapes drawn using kFillGradient
	 * as their fill mode will use this VERTICAL gradient as their fill color.
	 *
	 * @param r1	value of the red color byte for the start color
	 * @param g1	value of the green color byte for the start color
	 * @param b1	value of the blue color byte for the start color
	 * @param r2	value of the red color byte for the end color
	 * @param g2	value of the green color byte for the end color
	 * @param b2	value of the blue color byte for the end color
	 */
	virtual void setGradientColors(uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2) = 0;

	/**
	 * Sets the active drawing surface. All drawing from this
	 * point on will be done on that surface.
	 *
	 * @param surface Pointer to a Surface object.
	 */
	virtual void setSurface(ManagedSurface *surface) {
		_activeSurface = surface;
	}

	/**
	 * Returns the currently active drawing surface
	 */
	virtual ManagedSurface *getActiveSurface() {
		return _activeSurface;
	}

	/**
	 * Fills the active surface with the specified fg/bg color or the active gradient.
	 * Defaults to using the active Foreground color for filling.
	 */
	virtual void fillSurface() = 0;

	/**
	 * Clears the active surface.
	 */
	virtual void clearSurface() {
		byte *src = (byte *)_activeSurface->getPixels();
		memset(src, 0, _activeSurface->pitch * _activeSurface->h);
	}

	/**
	 * Sets the active fill mode for all shapes.
	 *
	 * @see VectorRenderer::FillMode
	 * @param mode Specified fill mode.
	 */
	virtual void setFillMode(FillMode mode) {
		_fillMode = mode;
	}

	virtual void setShadowFillMode(ShadowFillMode mode) {
		_shadowFillMode = mode;
	}

	/**
	 * Sets the stroke width. All shapes drawn with a stroke will
	 * have that width. Pass 0 to disable shape stroking.
	 *
	 * @param width Width of the stroke in pixels.
	 */
	virtual void setStrokeWidth(int width) {
		_strokeWidth = width;
	}

	/**
	 * Enables adding shadows to all drawn primitives.
	 * Shadows are drawn automatically under the shapes. The given offset
	 * controls their intensity and size (the higher the offset, the
	 * bigger the shadows). If the offset is 0, no shadows are drawn.
	 *
	 * @param offset Shadow offset.
	 */
	virtual void setShadowOffset(int offset) {
		if (offset >= 0)
			_shadowOffset = offset;
	}

	virtual void setBevel(int amount) {
		if (amount >= 0)
			_bevel = amount;
	}

	/**
	 * Sets the multiplication factor of the active gradient.
	 *
	 * @see _gradientFactor
	 * @param factor Multiplication factor.
	 */
	virtual void setGradientFactor(int factor) {
		if (factor > 0)
			_gradientFactor = factor;
	}

	/**
	 * Sets the pixel interval for drawing shadows
	 * 
	 * @param shadowIntensity interval for drawing shadows
	 */
	virtual void setShadowIntensity(uint32 shadowIntensity) {
		if (shadowIntensity > 0)
			_shadowIntensity = shadowIntensity;
		else
			warning("setShadowIntensity(): zero intensity");
	}

	/**
	 * Sets the clipping rectangle to be used by draw calls.
	 *
	 * Draw calls are restricted to pixels that are inside of the clipping
	 * rectangle. Pixels outside the clipping rectangle are not modified.
	 * To disable the clipping rectangle, call this method with a rectangle
	 * the same size as the target surface.
	 */
	virtual void setClippingRect(const Common::Rect &clippingArea) = 0;

	/**
	 * Translates the position data inside a DrawStep into actual
	 * screen drawing positions.
	 */
	void stepGetPositions(const DrawStep &step, const Common::Rect &area, uint16 &in_x, uint16 &in_y, uint16 &in_w, uint16 &in_h);

	/**
	 * Translates the radius data inside a drawstep into the real radius
	 * for the shape. Used for automatic radius calculations.
	 */
	int stepGetRadius(const DrawStep &step, const Common::Rect &area);

	/**
	 * Restrict a draw call clipping rect with a step specific clipping rect
	 */
	Common::Rect applyStepClippingRect(const Common::Rect &area, const Common::Rect &clip, const DrawStep &step);

	/**
	 * DrawStep callback functions for each drawing feature
	 */
	void drawCallback_CIRCLE(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h, radius;

		radius = stepGetRadius(step, area);
		stepGetPositions(step, area, x, y, w, h);

		drawCircle(x + radius, y + radius, radius);
	}

	void drawCallback_SQUARE(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawSquare(x, y, w, h);
	}

	void drawCallback_LINE(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawLine(x, y, x + w, y + h);
	}

	void drawCallback_ROUNDSQ(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawRoundedSquare(x, y, stepGetRadius(step, area), w, h);
	}

	void drawCallback_FILLSURFACE(const Common::Rect &area, const DrawStep &step) {
		fillSurface();
	}

	void drawCallback_TRIANGLE(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawTriangle(x, y, w, h, (TriangleOrientation)step.extraData);
	}

	void drawCallback_BEVELSQ(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawBeveledSquare(x, y, w, h);
	}

	void drawCallback_TAB(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawTab(x, y, stepGetRadius(step, area), w, h, step.shadow);
	}

	void drawCallback_BITMAP(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		blitManagedSurface(step.blitSrc, Common::Point(x, y), step.alphaType);
	}

	void drawCallback_CROSS(const Common::Rect &area, const DrawStep &step) {
		uint16 x, y, w, h;
		stepGetPositions(step, area, x, y, w, h);
		drawCross(x, y, w, h);
	}

	void drawCallback_VOID(const Common::Rect &area, const DrawStep &step) {}

	/**
	 * Draws the specified draw step on the screen.
	 *
	 * @see DrawStep
	 * @param area Zone to paint on
	 * @param step Pointer to a DrawStep struct.
	 */
	virtual void drawStep(const Common::Rect &area, const Common::Rect &clip, const DrawStep &step, uint32 extra = 0);

	/**
	 * Copies the part of the current frame to the system overlay.
	 *
	 * @param sys Pointer to the global System class
	 * @param r Zone of the surface to copy into the overlay.
	 */
	virtual void copyFrame(OSystem *sys, const Common::Rect &r) = 0;

	/**
	 * Copies the current surface to the system overlay
	 *
	 * @param sys Pointer to the global System class
	 */
	virtual void copyWholeFrame(OSystem *sys) = 0;

	/**
	 * Blits a given graphics surface on top of the current drawing surface.
	 *
	 * Note that the source surface and the active
	 * surface are expected to be of the same size, hence the area delimited
	 * by "r" in the source surface will be blitted into the area delimited by
	 * "r" on the current surface.
	 *
	 * If you wish to blit a smaller surface into the active drawing area, use
	 * VectorRenderer::blitSubSurface().
	 *
	 * @param source Surface to blit into the drawing surface.
	 * @param r Position in the active drawing surface to do the blitting.
	 */
	virtual void blitSurface(const Graphics::ManagedSurface *source, const Common::Rect &r) = 0;

	virtual void blitManagedSurface(const Graphics::ManagedSurface *source, const Common::Point &p, Graphics::AlphaType alphaType) = 0;

	/**
	 * Draws a string into the screen. Wrapper for the Graphics::Font string drawing
	 * method.
	 */
	virtual void drawString(const Graphics::Font *font, const Common::U32String &text,
	                        const Common::Rect &area, Graphics::TextAlign alignH,
	                        GUI::ThemeEngine::TextAlignVertical alignV, int deltax, bool useEllipsis, const Common::Rect &textDrawableArea) = 0;

	/**
	 * Allows to temporarily enable/disable all shadows drawing.
	 * i.e. for performance issues, blitting, etc
	 */
	virtual void disableShadows() { _disableShadows = true; }
	virtual void enableShadows() { _disableShadows = false; }

	/**
	 * Applies a whole-screen shading effect, used before opening a new dialog.
	 * Currently supports screen dimmings and luminance (b&w).
	 */
	virtual void applyScreenShading(GUI::ThemeEngine::ShadingStyle) = 0;

protected:
	ManagedSurface *_activeSurface; /**< Pointer to the surface currently being drawn */

	FillMode _fillMode; /**< Defines in which way (if any) are filled the drawn shapes */
	ShadowFillMode _shadowFillMode;

	int _shadowOffset; /**< offset for drawn shadows */
	int _bevel; /**< amount of fake bevel */
	bool _disableShadows; /**< Disables temporarily shadow drawing for overlayed images. */
	int _strokeWidth; /**< Width of the stroke of all drawn shapes */
	uint32 _dynamicData; /**< Dynamic data from the GUI Theme that modifies the drawing of the current shape */

	int _gradientFactor; /**< Multiplication factor of the active gradient */
	uint32 _shadowIntensity; /**< Intensity of the shadow */
};
/** @} */
} // End of namespace Graphics

#endif
