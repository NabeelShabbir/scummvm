enum VideoMode {		/* Video scalers */
	VIDEO_SCALE = 0,
	VIDEO_2XSAI = 1,
	VIDEO_SUPERSAI = 2,
	VIDEO_SUPEREAGLE = 3
};

enum {					/* Camera modes */
	CM_NORMAL = 1,
	CM_FOLLOW_ACTOR = 2,
	CM_PANNING = 3
};

struct CameraData {		/* Camera state data */
	ScummPoint _cur;
	ScummPoint _dest;
	ScummPoint _accel;
	ScummPoint _last;
	int _leftTrigger, _rightTrigger;
	byte _follows, _mode;
	bool _movingToActor;
};


struct VirtScreen {		/* Virtual screen areas */
	int number;
	uint16 unk1;
	uint16 topline;
	uint16 width,height;
	uint16 size;
	byte alloctwobuffers;
	byte scrollable;
	uint16 xstart;
	byte tdirty[40];
	byte bdirty[40];
	byte *screenPtr;
	byte *backBuf;
};

struct MouseCursor {	/* Mouse cursor */
	int8 hotspot_x, hotspot_y;
	byte colors[4];
	byte data[32];
};

struct ColorCycle {		/* Palette cycles */
	uint16 delay;
	uint16 counter;
	uint16 flags;
	byte start;
	byte end;
};

struct EnqueuedObject {		/* Objects to draw */
	uint16 a,b,c,d,e;
	int16 x,y;
	uint16 width,height;
	uint16 j,k,l;
};

struct BompHeader {			/* Bomp header */
	uint16 unk;
	uint16 width,height;
} GCC_PACK;

struct BompDrawData {		/* Bomp graphics data */
	byte *out;
	int outwidth, outheight;
	int x,y;
	byte scale_x, scale_y;
	byte *dataptr;
	int srcwidth, srcheight;
};

struct Gdi {
	Scumm *_vm;

	byte *_readPtr;
	uint _readOffs;

	int8 _cursorActive;

	int _numZBuffer;
	int _imgBufOffs[4];
	byte _disable_zbuffer;

	bool _useOrDecompress;
	byte _numLinesToProcess;
	byte _tempNumLines;
	byte _currentX;
	byte _hotspot_x;
	byte _hotspot_y;
	int16 _drawMouseX;
	int16 _drawMouseY;
	int16 _mask_top, _mask_bottom, _mask_right, _mask_left;
	byte _currentCursor;
	byte _mouseColors[4];
	byte _mouseColor;
	byte _mouseClipMask1, _mouseClipMask2, _mouseClipMask3;
	byte _mouseColorIndex;
	byte *_mouseMaskPtr;
	byte *_smap_ptr;
	byte *_backbuff_ptr;
	byte *_bgbak_ptr;
	byte *_mask_ptr;
	byte *_mask_ptr_dest;
	byte *_z_plane_ptr;

	byte _decomp_shr, _decomp_mask;
	byte _transparency;
	uint16 _vertStripNextInc;
	byte *_backupIsWhere;

	/* Bitmap decompressors */
	void decompressBitmap();
	void unkDecode1();
	void unkDecode2();
	void unkDecode3();
	void unkDecode4();
	void unkDecode5();
	void unkDecode6();
	void unkDecode7();
	void unkDecode8();
	void unkDecode9();
	void unkDecode10();
	void unkDecode11();

	void drawBitmap(byte *ptr, VirtScreen *vs, int x, int y, int h, int stripnr, int numstrip, byte flag);
	void clearUpperMask();

	void disableZBuffer() { _disable_zbuffer++; }
	void enableZBuffer() { _disable_zbuffer--; }

	void draw8ColWithMasking();
	void clear8ColWithMasking();
	void clear8Col();
	void decompressMaskImgOr();
	void decompressMaskImg();

	void resetBackground(byte top, byte bottom, int strip);
	void drawStripToScreen(VirtScreen *vs, int x, int w, int t, int b);
	void updateDirtyScreen(VirtScreen *vs);

	enum DrawBitmapFlags {
		dbAllowMaskOr = 1,
		dbDrawMaskOnBoth = 2,
		dbClear = 4
	};
};
