//
//  PreDeclare.h
//  Project Unknown
//
//  Created by Robert Bu on 11/22/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef Project_Unknown_PreDeclare_h
#define Project_Unknown_PreDeclare_h

#include "mist/Platform.h"
#include "mist/Resource.h"
#include "mist/Entity.h"
#include "mist/Task.h"
#include "mist/FSM.h"
#include "mist/Stream.h"
#include "mist/Component.h"
#include "mist/Ptr.h"
#include "mist/MathUtil.h"

#include <string>

namespace ukn {
    
    using namespace mist;
    
#define UKN_API MIST_API 
    
    typedef MistString UknString;
    
    typedef mist::PointTemplate<1, float> float1;
    typedef mist::PointTemplate<2, float> float2;
    typedef mist::PointTemplate<3, float> float3;
    typedef mist::PointTemplate<4, float> float4;
    
    typedef mist::PointTemplate<1, int32> int1;
    typedef mist::PointTemplate<2, int32> int2;
    typedef mist::PointTemplate<3, int32> int3;
    typedef mist::PointTemplate<4, int32> int4;
    
    typedef mist::PointTemplate<1, uint32> uint1;
    typedef mist::PointTemplate<2, uint32> uint2;
    typedef mist::PointTemplate<3, uint32> uint3;
    typedef mist::PointTemplate<4, uint32> uint4;

    struct VertexFormat;
    
    struct ContextCfg;
    
    typedef SharedPtr<mist::Resource> ResourcePtr;
    typedef SharedPtr<mist::Stream> StreamPtr;
    typedef SharedPtr<mist::Entity> EntityPtr;
    typedef SharedPtr<mist::Component> ComponentPtr;
    typedef SharedPtr<mist::Task> TaskPtr;
    typedef SharedPtr<mist::FSMState> FSMStatePtr;
    typedef SharedPtr<mist::ComponentHolder> ComponentHolderPtr;
    typedef SharedPtr<mist::ConfigParser> ConfigParserPtr;
    
    
    class GraphicDevice;
    typedef SharedPtr<GraphicDevice> GraphicDevicePtr;
    
    class GraphicFactory;
    typedef SharedPtr<GraphicFactory> GraphicFactoryPtr;
    
    class WindowFactory;
    typedef SharedPtr<WindowFactory> WindowFactoryPtr;
    
    class GraphicBuffer;
    typedef SharedPtr<GraphicBuffer> GraphicBufferPtr;
    
    class FrameBuffer;
    typedef SharedPtr<FrameBuffer> FrameBufferPtr;
    
    class RenderBuffer;
    typedef SharedPtr<RenderBuffer> RenderBufferPtr;
    
    class RenderView;
    typedef SharedPtr<RenderView> RenderViewPtr;
    
    class RenderEffect;
    typedef SharedPtr<RenderEffect> RenderEffectPtr;
    
    
    class Texture;
    typedef SharedPtr<Texture> TexturePtr;
    
    class Font;
    typedef SharedPtr<Font> FontPtr;
    
    class Texture;
   
    class Camera;
    typedef SharedPtr<Camera> CameraPtr;
    
    class Window;
    typedef SharedPtr<Window> WindowPtr;
    
    
    class AppInstance;
    typedef SharedPtr<AppInstance> AppPtr;
    
    class SpriteBatch;
    typedef SharedPtr<SpriteBatch> SpriteBatchPtr;
    
    class SceneNode;
    typedef SharedPtr<SceneNode> SceneNodePtr;
    
    class Scene;
    typedef SharedPtr<Scene> ScenePtr;
           
    class IRenderable;
    typedef SharedPtr<IRenderable> RenderablePtr;
    
    class SceneObject;
    typedef SharedPtr<SceneObject> SceneObjectPtr;
    
    class SceneManager;
    typedef SharedPtr<SceneManager> SceneManagerPtr;
    
    class SequencialAnimation;
    typedef SharedPtr<SequencialAnimation> SequencialAnimationPtr;
    
    class RenderTarget2D;
    typedef SharedPtr<RenderTarget2D> RenderTargetPtr;
    
} // namespace ukn


#endif
