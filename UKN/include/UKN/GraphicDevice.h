//
//  RenderDevice.h
//  Project Unknown
//
//  Created by Robert Bu on 11/22/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef Project_Unknown_RenderDevice_h
#define Project_Unknown_RenderDevice_h

#include "mist/Platform.h"
#include "mist/MathUtil.h"
#include "mist/Color.h"

#include "UKN/PreDeclare.h"
#include "UKN/GraphicSettings.h"

#include <stack>

namespace ukn {
    
    /**
     * Abstract GraphicrDevice Class
     * Represents a OpenGL or DirectX device depends on current platform 
     **/
    
    /**
     * Graphic Device Caps
     **/
    struct UKN_API GraphicDeviceCaps {
        uint32 max_indices;
        uint32 max_vertices;
        
        uint32 max_texture_cube_map_size;
        uint32 max_texture_width;
        uint32 max_texture_height;
        
        uint32 max_pixel_texture_units;
        uint32 max_vertex_texture_units;
    };

    struct UKN_API OrthogonalParams {
        float x;
        float y;
        float width;
        float height;
        /* displacement x, y*/
        float dx;
        float dy;

        OrthogonalParams(float _x = 0, float _y = 0, float _width = 0, float _height = 0, float _dx = 0, float _dy = 0):
            x(_x),
            y(_y),
            width(_width),
            height(_height),
            dx(_dx),
            dy(_dy) {
        }
    };
    
    class UKN_API GraphicDevice {
    public:
        GraphicDevice();
        virtual ~GraphicDevice();
        
        static GraphicDevicePtr NullObject();
        
        Matrix4 pushViewMatrix();
        Matrix4 popViewMatrix();
        
        Matrix4 pushProjectionMatrix();
        Matrix4 popProjectionMatrix();
        
    protected:
        typedef std::stack<Matrix4> MatrixStack;
        MatrixStack mViewMatrixStack;
        MatrixStack mProjMatrixStack;
        
        virtual WindowPtr doCreateRenderWindow(const UknString& name, const RenderSettings& settings) = 0;

    public:
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        
        virtual void beginRendering() = 0;
        
    public:
        virtual UknString description() const = 0;
               
        virtual void setViewMatrix(const Matrix4& mat) = 0;
        virtual void setProjectionMatrix(const Matrix4& mat) = 0;
        virtual void setWorldMatrix(const Matrix4& mat) = 0;

        virtual void getViewMatrix(Matrix4& mat) const = 0;
        virtual void getProjectionMatrix(Matrix4& mat) const = 0;
        virtual void getWorldMatrix(Matrix4& mat) const = 0;
        
        virtual void fillGraphicCaps(GraphicDeviceCaps& caps) = 0;
    
        virtual void renderBuffer(const RenderBufferPtr& buffer) = 0;
        virtual void onBindFrameBuffer(const FrameBufferPtr& frameBuffer) = 0;
        
        virtual void setRenderState(RenderStateType type, uint32 func) = 0;

        virtual void adjustPerspectiveMat(Matrix4& mat) {}
        
        /* sets up orthogonal projection with ortho parameters */
        virtual void switchTo2D(const OrthogonalParams& params = OrthogonalParams()) = 0;
        
    public:
        virtual void bindTexture(const TexturePtr& texture) = 0;
        virtual void bindEffect(const EffectPtr& effect) = 0;
    
    public:
        WindowPtr createRenderWindow(const UknString& name, const RenderSettings& settings);
        
        void bindFrameBuffer(const FrameBufferPtr& ptr);
        const FrameBufferPtr& getCurrFrameBuffer() const;
        const FrameBufferPtr& getScreenFrameBuffer() const;
        
        void clearColor(const Color& clr);
        void clearDepth(float depth);
        void clearStencil(int32 stencil);
        
        void clear(uint32 flags, const class Color& clr, float depth, int32 stencil);
        
    public:
        void setRenderTarget(const RenderTargetPtr& target);
        
    protected:
        FrameBufferPtr mCurrFrameBuffer;
        FrameBufferPtr mScreenFrameBuffer;
        
        Color mClearColor;
        float mClearDepth;
        int mClearStencil;
        
        RenderTargetPtr mCurrTarget;
    };
    
} // namespace ukn



#endif
