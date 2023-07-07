#pragma once

class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,	// 리소스, 파일
		LOAD_EMPTY, LOAD_END			// 빈 비트맵, 로드 Done
	};

	typedef struct tagImage
	{
		DWORD		resID;			// unsigned long
		HDC			hMemDC;
		// 복사를 전제
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;				// 이미지 x좌표
		float		y;				// 이미지 y좌표
		int			width;			// 이미지 가로 크기
		int			height;			// 이미지 세로 크기
		int			currentFrameX;	// 현재 프레임 X
		int			currentFrameY;	// 현재 프레임 Y
		int			maxFrameX;		// 최대 프레임 X 개수
		int			maxFrameY;		// 최대 프레임 Y 개수
		int			frameWidth;		// 1 프레임 가로 크기
		int			frameHeight;	// 1 프레임 세로 크기
		BYTE		loadType;		// unsigned char

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char* _fileName;
	bool			_isTrans;		// 배경색을 뺄건지 안 뺄건지
	COLORREF		_transColor;	// 없앨 RGB값(마젠타 = RGB(255, 0, 255);

	BLENDFUNCTION	_blendFunc;		// 알파 블렌드 기능
	LPIMAGE_INFO	_blendImage;	// 알바 블렌드 이미지

public:
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	// 배경과 같이 중첩 배경이 필요할 때
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);
	// 투명 컬러키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 해제
	void release(void);

	// 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 이미지 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY);

	// 루프 렌더
	// ㄴ 반복 / 이미지를 밀고 당기는 방식
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ##인라인 함수##
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 X 좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// 이미지 Y 좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2); \
	}

	//  이미지 가로 / 세로 크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}

	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}
	// 프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	// 프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1프레임 가로 / 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// 최대 프레임 X / Y 개수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage(); // 변수들을 상속받는 클래스에서 사용할 수 있어야하기 때문에 초기화(+ release에서 해제)
	~GImage() {}
};