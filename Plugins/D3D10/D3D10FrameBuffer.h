#include "mist/Platform.h"
#include "UKN/FrameBuffer.h"

namespace ukn {

	class D3D10FrameBuffer: public FrameBuffer {
    public:
        D3D10FrameBuffer(bool offscreen);
        virtual ~D3D10FrameBuffer();
        
        bool requiresFlipping() const;
        
        void onBind();
        void onUnbind();
        void clear(uint32 flags, const class Color& clr, float depth, int32 stencil);
        
        void swapBuffers();
        
        SharedPtr<uint8> readFrameBufferData(int32 x, int32 y, uint32 width, uint32 height, ElementFormat format);
        
    private:
        bool mOffscreen;
        
        friend class GLWindow;
    };
    
    typedef SharedPtr<D3D10FrameBuffer> GLFrameBufferPtr;

} // namespace ukn