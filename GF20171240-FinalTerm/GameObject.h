#pragma once
#include "SDL.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
class GameObject {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual ~GameObject() {}
    /// <summary>
    /// 오브젝트의 destW,destH, row, frame, numFrame을 변경할때 사용하는 함수
    /// 인자를 전달받지 않으면 그대로 둔다.
    /// </summary>
    virtual void setModifier(int w, int h, int row = 0, int frame = 0, int numFrame = 1) = 0;
    
    virtual int getDestW() const { return m_destW; }
    virtual int getDestH() const { return m_destH; }
protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    int m_destW;
    int m_destH;

    GameObject(const LoaderParams* pParams) {
        m_currentFrame = NULL;
        m_numFrames = NULL;
        m_destW = NULL;
        m_destH = NULL;

    }
};
