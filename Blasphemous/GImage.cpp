#include "Stdafx.h"
#include "GImage.h"

GImage::GImage() : _imageInfo(nullptr)
, _fileName(nullptr)
, _isTrans(false)
, _transColor(RGB(0, 0, 0))
, _blendImage(NULL) {}

HRESULT GImage::init(int width, int height)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_EMPTY;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    _fileName = nullptr;
    _isTrans = false;
    _transColor = RGB(0, 0, 0);

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);
    return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = resID;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc); 
    _imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    _fileName = nullptr;
    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL; 
    }

    ReleaseDC(_hWnd, hdc);
    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);   
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = strlen(fileName);

    _fileName = new char[len + 1];
    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);
    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc); 
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);    
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;
    _imageInfo->frameHeight = height / maxFrameY;

    int len = strlen(fileName);

    _fileName = new char[len + 1];
    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);
    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc); 
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;
    _imageInfo->frameHeight = height / maxFrameY;

    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL; 
    }

    ReleaseDC(_hWnd, hdc);
    return S_OK;
}

HRESULT GImage::initForAlphaBlend(void)
{
    HDC hdc = GetDC(_hWnd);

    _blendFunc.BlendFlags = 0;
    _blendFunc.AlphaFormat = 0;
    _blendFunc.BlendOp = AC_SRC_OVER;

    _blendImage = new IMAGE_INFO;
    _blendImage->loadType = LOAD_FILE;
    _blendImage->resID = 0;
    _blendImage->hMemDC = CreateCompatibleDC(hdc);
    _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
    _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
    _blendImage->width = WINSIZE_X;
    _blendImage->height = WINSIZE_Y;

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
    _isTrans = isTrans;
    _transColor = transColor;
}

void GImage::release(void)
{
    if (_imageInfo)
    {
        // �̹��� ����
        SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);

        SAFE_DELETE(_imageInfo);
        SAFE_DELETE_ARRAY(_fileName);

        _isTrans = false;
        _transColor = RGB(0, 0, 0);
    }
    if (_blendImage)
    {
        SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
        DeleteObject(_blendImage->hBit);
        DeleteDC(_blendImage->hMemDC);

        SAFE_DELETE(_blendImage);
    }
}

void GImage::render(HDC hdc)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                       
            0,                         
            0,                         
            _imageInfo->width,         
            _imageInfo->height,        
            _imageInfo->hMemDC,        
            0, 0,                      
            _imageInfo->width,         
            _imageInfo->height,        
            _transColor                
        );
    }
    else
    {
        BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);

    }
}

void GImage::render(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                        
            destX,                      
            destY,                      
            _imageInfo->width,          
            _imageInfo->height,         
            _imageInfo->hMemDC,         
            0, 0,                       
            _imageInfo->width,          
            _imageInfo->height,         
            _transColor                 
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);

    }
}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                       
            destX,                     
            destY,                     
            sourWidth,                 
            sourHeight,                
            _imageInfo->hMemDC,        
            sourX, sourY,              
            sourWidth,                 
            sourHeight,                
            _transColor                
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, SRCCOPY);

    }
}

// �̹��� Ŭ����: Ȯ��
void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                    
            destX,                  
            destY,                  
            destWidth,              
            destHeight,             
            _imageInfo->hMemDC,     
            sourX, sourY,       
            sourWidth,              
            sourHeight,             
            _transColor             
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, SRCCOPY);

    }
}

// ���ķ��� - ���̵���, ���̵�ƿ�
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            0, 0,
            SRCCOPY
        );
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _transColor
        );
        AlphaBlend
        (
            hdc,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );

    }
    else
    {
        AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );

        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _transColor
        );

        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );

    }
    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            sourWidth, sourHeight,
            _imageInfo->hMemDC,
            sourX, sourY,
            sourWidth, sourHeight,
            _transColor
        );
        AlphaBlend
        (
            hdc,
            destX, destY,
            sourWidth, sourHeight,
            _blendImage->hMemDC,
            sourX, sourY,
            sourWidth, sourHeight,
            _blendFunc
        );

    }
    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            destWidth, destHeight,
            _imageInfo->hMemDC,
            sourX, sourY,
            sourWidth, sourHeight,
            _transColor
        );
        AlphaBlend
        (
            hdc,
            destX, destY,
            destWidth, destHeight,
            _blendImage->hMemDC,
            sourX, sourY,
            sourWidth, sourHeight,
            _blendFunc
        );

    }
    else
    {
        AlphaBlend(hdc, destX, destY, destWidth, destHeight,
            _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

    }
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                       
            destX,                     
            destY,                     
            _imageInfo->frameWidth,    
            _imageInfo->frameHeight,   
            _imageInfo->hMemDC,        
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, 
            _imageInfo->frameWidth,    
            _imageInfo->frameHeight,   
            _transColor                
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);

    }
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > _imageInfo->maxFrameX)
    {

        _imageInfo->currentFrameX = _imageInfo->maxFrameX;
    }
    if (currentFrameY > _imageInfo->maxFrameY)
    {
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                        
            destX,                      
            destY,                      
            _imageInfo->frameWidth,     
            _imageInfo->frameHeight,    
            _imageInfo->hMemDC,         
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,     
            _imageInfo->frameHeight,    
            _transColor                 
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);

    }
}

void GImage::frameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY)
{
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > _imageInfo->maxFrameX)
    {
        _imageInfo->currentFrameX = _imageInfo->maxFrameX;
    }
    if (currentFrameY > _imageInfo->maxFrameY)
    {
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                       
            destX,                     
            destY,                     
            destWidth,                 
            destHeight,                
            _imageInfo->hMemDC,        
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,     
            _imageInfo->frameHeight,    
            _transColor                 
        );
    }
    else
    {
        BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);

    }
}

void GImage::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;
    
    if (currentFrameX > _imageInfo->maxFrameX)
    { 
        _imageInfo->currentFrameX = _imageInfo->maxFrameX; 
    }     
    if (currentFrameY > _imageInfo->maxFrameY) 
    { 
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }      
    
    if (!_blendImage) this->initForAlphaBlend();
    
    if (alpha < 0) { _blendFunc.SourceConstantAlpha = 0; }
    else if (alpha > 255) 
    { 
        _blendFunc.SourceConstantAlpha = 255; 
    }
    else 
    { 
        _blendFunc.SourceConstantAlpha = alpha; 
    }     
    
    if (_isTrans) {
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);         
        
        GdiTransparentBlt(
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->frameWidth, 
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor);

        GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
    else
    {
        GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
}