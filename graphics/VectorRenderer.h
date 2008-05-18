/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef VECTOR_RENDERER_H
#define VECTOR_RENDERER_H

#include "common/scummsys.h"
#include "graphics/surface.h"
#include "graphics/colormasks.h"
#include "common/system.h"

namespace Graphics {

void vector_renderer_test(OSystem *_system);

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
 * TODO: Expand documentation.
 *
 * @see VectorRendererSpec
 * @see VectorRendererAA
 */
class VectorRenderer {

public:
	VectorRenderer() : _shadowOffset(0), _fillMode(kNoFill), _activeSurface(NULL), _strokeWidth(1), _gradientFactor(1) {}
	virtual ~VectorRenderer() {}

	enum FillMode {
		kNoFill = 0,
		kForegroundFill = 1,
		kBackgroundFill = 2,
		kGradientFill = 3
	};

/*	enum ColorMode {
		kForegroundColor,
		kBackgroundColor
	}; */

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
	 * Gets the pixel pitch for the current drawing surface.
	 * Note: This is a real pixel-pitch, not a byte-pitch.
	 * That means it can be safely used in pointer arithmetics and
	 * in pixel manipulation.
	 *
	 * @return integer with the active bytes per pixel
	 */
	virtual uint16 surfacePitch() {
		return _activeSurface->pitch / _activeSurface->bytesPerPixel;
	}

	/**
	 * Gets the BYTES (not bits) per Pixel we are working on,
	 * based on the active drawing surface.
	 *
	 * @return integer byte with the active bytes per pixel value
	 */
	virtual uint8 bytesPerPixel() {
		return _activeSurface->bytesPerPixel;
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

	virtual void setGradientColors(uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2) = 0;

	/**
	 * Sets the active drawing surface. All drawing from this
	 * point on will be done on that surface.
	 *
	 * @param surface Pointer to a Surface object.
	 */
	virtual void setSurface(Surface *surface) {
		_activeSurface = surface;
	}

	/**
	 * Fills the active surface with the specified fg/bg color.
	 * Defaults to using the active Foreground color for filling.
	 *
	 * @param mode Color mode (bg or fg color) used to fill.
	 */
	virtual void fillSurface(FillMode mode = kForegroundFill) = 0;

	/**
	 * Clears the active surface.
	 */
	virtual void clearSurface() {
		byte *src = (byte *)_activeSurface->pixels;
		memset(src, 0, _activeSurface->w * _activeSurface->h * _activeSurface->bytesPerPixel);
	}

	/**
	 * Sets the active fill mode for all shapes.
	 *
	 * @see VectorRenderer::FillMode
	 * @param mode Specified fill mode.
	 */
	virtual void setFillMode(VectorRenderer::FillMode mode) {
		_fillMode = mode;
	}

	/**
	 * Sets the stroke width. All shapes drawn with a stroke will
	 * have that width.
	 *
	 * @param width Witdh of the stroke in pixels.
	 */
	virtual void setStrokeWidth(int width) {
		_strokeWidth = width;
	}

	/**
	 * Enables adding shadows to all drawn primitives.
	 * Shadows are drawn automatically under the shapes, at the
	 * given x/y offsets.
	 *
	 * @param x_offset Horizontal offset for the shadows.
	 * @param y_offset Vertical offset for the shadows.
	 * @see shadowDisable()
	 */
	virtual void shadowEnable(int offset) {
		if (offset > 0)
			_shadowOffset = offset;
	}

	/**
	 * Disables adding shadows to all drawn primitives.
	 *
	 * @see shadowEnable()
	 */
	virtual void shadowDisable() {
		_shadowOffset = 0;
	}

	virtual void setGradientFactor(int factor) {
		if (factor > 0)
			_gradientFactor = factor;
	}

protected:
	Surface *_activeSurface; /** Pointer to the surface currently being drawn */

	FillMode _fillMode; /** Defines in which way (if any) are filled the drawn shapes */
	
	int _shadowOffset; /** offset for drawn shadows */
	int _strokeWidth; /** Width of the stroke of all drawn shapes */

	int _gradientFactor;
	int _gradientBytes[3];
};


/**
 * VectorRendererSpec: Specialized Vector Renderer Class
 *
 * This templated class implements the basic subset of vector operations for
 * all platforms by allowing the user to provide the actual Pixel Type and
 * pixel information structs.
 *
 * This class takes two template parameters:
 *
 * @param PixelType Defines a type which may hold the color value of a single
 *        pixel, such as "byte" or "uint16" for 8 and 16 BPP respectively.
 *
 * @param PixelFormat Defines the type of the PixelFormat struct which contains all
 *        the actual information of the pixels being used, as declared in "graphics/colormasks.h"
 *                    
 * TODO: Expand documentation.
 *
 * @see VectorRenderer
 */
template<typename PixelType, typename PixelFormat>
class VectorRendererSpec : public VectorRenderer {
	typedef VectorRenderer Base;

public:
	/**
	 * @see VectorRenderer::drawLine()
	 */
	void drawLine(int x1, int y1, int x2, int y2);

	/**
	 * @see VectorRenderer::drawCircle()
	 */
	void drawCircle(int x, int y, int r);

	/**
	 * @see VectorRenderer::drawSquare()
	 */
	void drawSquare(int x, int y, int w, int h);

	/**
	 * @see VectorRenderer::drawRoundedSquare()
	 */
	void drawRoundedSquare(int x, int y, int r, int w, int h);

	/**
	 * @see VectorRenderer::setFgColor()
	 */
	void setFgColor(uint8 r, uint8 g, uint8 b) {
		this->_fgColor = RGBToColor<PixelFormat>(r, g, b);
	}

	/**
	 * @see VectorRenderer::setBgColor()
	 */
	void setBgColor(uint8 r, uint8 g, uint8 b) {
		this->_bgColor = RGBToColor<PixelFormat>(r, g, b);
	}

	void setGradientColors(uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2) {
		_gradientEnd = RGBToColor<PixelFormat>(r2, g2, b2);
		_gradientStart = RGBToColor<PixelFormat>(r1, g1, b1);

		Base::_gradientBytes[0] = (_gradientEnd & PixelFormat::kRedMask) - (_gradientStart & PixelFormat::kRedMask);
		Base::_gradientBytes[1] = (_gradientEnd & PixelFormat::kGreenMask) - (_gradientStart & PixelFormat::kGreenMask);
		Base::_gradientBytes[2] = (_gradientEnd & PixelFormat::kBlueMask) - (_gradientStart & PixelFormat::kBlueMask);
	}

	/**
	 * @see VectorRenderer::fillSurface()
	 */
	void fillSurface(FillMode mode = kForegroundFill) {
		PixelType *ptr = (PixelType *)_activeSurface->getBasePtr(0, 0);

		int w = _activeSurface->w;
		int h = _activeSurface->h ;
		int pitch = surfacePitch();

		if (mode == kBackgroundFill)
			Common::set_to(ptr, ptr + w*h, _bgColor);
		else if (mode == kForegroundFill)
			Common::set_to(ptr, ptr + w*h, _fgColor);
		else if (mode == kGradientFill) {
			int i = h;
			while (i--) {
				Common::set_to(ptr, ptr + w, calcGradient(h - i, h));
				ptr += pitch;
			}
		}
	}

protected:

	/**
	 * Draws a single pixel on the surface with the given coordinates and
	 * the given color.
	 *
	 * @param x Horizontal coordinate of the pixel.
	 * @param y Vertical coordinate of the pixel.
	 * @param color Color of the pixel
	 */
	virtual inline void putPixel(int x, int y, PixelType color) {
		PixelType *ptr = (PixelType *)_activeSurface->getBasePtr(x, y);
		*ptr = color;
	}

	/**
	 * Blends a single pixel on the surface with the given coordinates, color
	 * and Alpha intensity.
	 *
	 * @param x Horizontal coordinate of the pixel.
	 * @param y Vertical coordinate of the pixel.
	 * @param color Color of the pixel
	 * @param alpha Alpha intensity of the pixel (0-255)
	 */
	virtual inline void blendPixel(int x, int y, PixelType color, uint8 alpha) {
		if (alpha == 255)
			putPixel(x, y, color);
		else if (alpha > 0)
			blendPixelPtr((PixelType*)Base::_activeSurface->getBasePtr(x, y), color, alpha);
	}

	virtual inline void blendPixelPtr(PixelType *ptr, PixelType color, uint8 alpha);

	/*
	 * "Bresenham's Line Algorithm", as described in Wikipedia.
	 * Based on the current implementation in "graphics/primitives.cpp".
	 *
	 * Generic line drawing algorithm for the aliased renderer. Optimized with no
	 * floating point operations and direct access to pixel buffer, assumes no special cases.
	 */
	virtual void drawLineAlg(int x1, int y1, int x2, int y2, int dx, int dy, PixelType color);
	virtual void drawCircleAlg(int x, int y, int r, PixelType color, FillMode fill_m);
	virtual void drawRoundedSquareAlg(int x1, int y1, int r, int w, int h, PixelType color, FillMode fill_m);
	virtual void drawSquareAlg(int x, int y, int w, int h, PixelType color, FillMode fill_m);
	virtual void drawSquareShadow(int x, int y, int w, int h, int blur);
	virtual void drawRoundedSquareShadow(int x, int y, int r, int w, int h, int blur);

	inline PixelType calcGradient(uint32 pos, uint32 max) {
		PixelType output = 0;
		pos = (MIN(pos * Base::_gradientFactor, max) << 12) / max;
		
		output |= (_gradientStart + ((Base::_gradientBytes[0] * pos) >> 12)) & PixelFormat::kRedMask;
		output |= (_gradientStart + ((Base::_gradientBytes[1] * pos) >> 12)) & PixelFormat::kGreenMask;
		output |= (_gradientStart + ((Base::_gradientBytes[2] * pos) >> 12)) & PixelFormat::kBlueMask;
		output |= ~(PixelFormat::kRedMask | PixelFormat::kGreenMask | PixelFormat::kBlueMask);
	
		return output;
	}

	inline void blendFill(PixelType *first, PixelType *last, PixelType color, uint8 alpha) {
		while (first != last)
			blendPixelPtr(first++, color, alpha);
	}	

	PixelType _fgColor; /** Foreground color currently being used to draw on the renderer */
	PixelType _bgColor; /** Background color currently being used to draw on the renderer */

	PixelType _gradientStart;
	PixelType _gradientEnd;
};

/**
 * VectorRendererAA: Anti-Aliased Vector Renderer Class
 *
 * This templated class inherits all the functionality of the VectorRendererSpec
 * class but uses better looking yet slightly slower AA algorithms for drawing
 * most primivitves. May be used in faster platforms.
 *                    
 * TODO: Expand documentation.
 *
 * @see VectorRenderer
 * @see VectorRendererSpec
 */
template<typename PixelType, typename PixelFormat>
class VectorRendererAA : public VectorRendererSpec<PixelType, PixelFormat> {
	typedef VectorRendererSpec<PixelType, PixelFormat> Base;
protected:
	/**
	 * "Wu's Line Antialiasing Algorithm" as published by Xiaolin Wu, July 1991
	 * Based on the implementation found in Michael Abrash's Graphics Programming Black Book.
	 *
	 * Generic line drawing algorithm for the Antialiased renderer. Optimized with no
	 * floating point operations, assumes no special cases.
	 *
	 * @see VectorRenderer::drawLineAlg()
	 */
	void drawLineAlg(int x1, int y1, int x2, int y2, int dx, int dy, PixelType color);

	/**
	 * "Wu's Circle Antialiasing Algorithm" as published by Xiaolin Wu, July 1991
	 * Based on the theoretical concept of the algorithm.
	 *
	 * Implementation of Wu's algorithm for circles using fixed point arithmetics.
	 * Could be quite fast.
	 *
	 * @see VectorRenderer::drawCircleAlg()
	 */
	virtual void drawCircleAlg(int x, int y, int r, PixelType color, VectorRenderer::FillMode fill_m);

	virtual void drawRoundedSquareAlg(int x1, int y1, int r, int w, int h, PixelType color, VectorRenderer::FillMode fill_m);
};

} // end of namespace Graphics

#endif
