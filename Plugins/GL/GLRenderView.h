//
//  GLRenderView.h
//  Project Unknown
//
//  Created by Ruiwei Bu on 12/2/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef Project_Unknown_GLRenderView_h
#define Project_Unknown_GLRenderView_h

#include "UKN/RenderView.h"
#include "UKN/Uncopyable.h"
#include "UKN/GraphicSettings.h"

#include "GLTexture.h"
#include "glfw/glfw3.h"

namespace ukn {
    
    class GLRenderView: public RenderView {
    public:
        GLRenderView();
        virtual ~GLRenderView();
        
        void clearDepth(float depth);
        void clearStencil(int32 stencil);
        void clearDepthStencil(float depth, int32 stencil);
        
    protected:
        void doClear(uint32 flags, const class Color& clr, float depth, int32 stencil);
        
    protected:
        GLuint mTex;
        GLuint mFBO;
        GLuint mIndex;
    };
    
    typedef SharedPtr<GLRenderView> GLRenderViewPtr;
    
    class GLScreenColorRenderView: Uncopyable, public GLRenderView {
    public:
        GLScreenColorRenderView(uint32 width, uint32 height, ElementFormat ef);
        
        void clearColor(const Color& clr);
        void clearDepth(float depth);
        void clearStencil(int32 stencil);
        void clearDepthStencil(float depth, int32 stencil);
        
        void onAttached(FrameBuffer& fb, uint32 att);
        void onDetached(FrameBuffer& fb, uint32 att);
    };
    
    typedef SharedPtr<GLScreenColorRenderView> GLScreenColorRenderViewPtr;
    
    class GLScreenDepthStencilRenderView: Uncopyable, public GLRenderView {
    public:
        GLScreenDepthStencilRenderView(uint32 width, uint32 height, ElementFormat ef);
        
        void clearColor(const Color& clr);
        
        void onAttached(FrameBuffer& fb, uint32 att);
        void onDetached(FrameBuffer& fb, uint32 att);
    };
    
    typedef SharedPtr<GLScreenDepthStencilRenderView> GLScreenDepthStencilRenderViewPtr;
    
    class GLTexture2DRenderView: Uncopyable, public GLRenderView {
    public:
        GLTexture2DRenderView(Texture& texture, int32 index, int32 level);
        
        void clearColor(const Color& clr);
        
        void onAttached(FrameBuffer& fb, uint32 att);
        void onDetached(FrameBuffer& fb, uint32 att);
        
    private:
        GLTexture2D& mTexture;
        int32 mIndex;
        int32 mLevel;
    };
    
    typedef SharedPtr<GLTexture2DRenderView> GLTexture2DRenderViewPtr;
    
} // namespace ukn

#endif