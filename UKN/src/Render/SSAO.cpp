#include "UKN/SSAO.h"
#include "UKN/Shader.h"
#include "UKN/GraphicDevice.h"
#include "UKN/GraphicFactory.h"
#include "UKN/Context.h"
#include "UKN/LightManager.h"
#include "UKN/RenderTarget.h"
#include "UKN/Model.h"
#include "UKN/Camera.h"
#include "UKN/SamplerStateObject.h"
#include "UKN/BlendStateObject.h"
#include "UKN/SpriteBatch.h"

namespace ukn {

    SSAO::SSAO(const float2& size):
    mSize(size),
    mSampleRadius(0.3),
    mDistanceScale(1.0) {
        if(!this->init()) {
        }
    }

    SSAO::~SSAO() {

    }

    const EffectPtr& SSAO::getEffect() const {
        return mEffect;
    }

    const RenderTargetPtr& SSAO::getSSAOTarget() const {
        return mSSAOTarget;
    }

    const RenderTargetPtr& SSAO::getCompositeTarget() const {
        return mCompositeTarget;
    }

    const RenderTargetPtr& SSAO::getSSAOBlurTarget() const {
        return mSSAOBlurTarget;
    }

    float2 SSAO::size() const {
        return mSize;
    }

    float SSAO::getSampleRadius() const {
        return mSampleRadius;
    }

    float SSAO::getDistanceScale() const {
        return mDistanceScale;
    }

    void SSAO::setSampleRadius(float r) {
        mSampleRadius = r;
    }
    
    void SSAO::setDistanceScale(float r) {
        mDistanceScale = r;
    }

    void SSAO::render(const CompositeRenderTargetPtr& scene, const TexturePtr& target) {
        GraphicDevice& gd = Context::Instance().getGraphicFactory().getGraphicDevice();
        CameraPtr currCamera = gd.getCurrFrameBuffer()->getViewport().camera;
        
        mRT->attachCamera(currCamera);

        this->makeSSAO(scene);
        this->makeSSAOBlur(scene);
        this->makeFinal(target);
    }

    bool SSAO::init() {
        GraphicFactory& gf = Context::Instance().getGraphicFactory();

        if(mSize[0] == 0 && mSize[1] == 0) {
            Window& wnd = Context::Instance().getApp().getWindow();
            mSize = float2((float)wnd.width(), (float)wnd.height());
        }
        /* render targets */
        {
            mRT = MakeSharedPtr<CompositeRenderTarget>();

            mSSAOTarget = MakeSharedPtr<ukn::RenderTarget>((uint32)mSize[0],
                                                           (uint32)mSize[1],
                                                           1,
                                                           ukn::EF_RGBA8);

            mSSAOBlurTarget = MakeSharedPtr<ukn::RenderTarget>((uint32)mSize[0],
                                                               (uint32)mSize[1],
                                                               1,
                                                               ukn::EF_RGBA8);

            mCompositeTarget = MakeSharedPtr<ukn::RenderTarget>((uint32)mSize[0],
                                                                (uint32)mSize[1],
                                                                1,
                                                                ukn::EF_RGBA8);
        }

        /* effect */
        {
            ukn::ShaderPtr vertexShader;
            ukn::ShaderPtr fragmentShader;
            
            mEffect = gf.createEffect();

            if(mEffect) {
                vertexShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_vert.cg"), 
                                                     VERTEX_SHADER_DESC("VertexProgram"));
                fragmentShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_frag.cg"), 
                                                       FRAGMENT_SHADER_DESC("FragmentProgram"));

                mSSAOTechnique = mEffect->appendTechnique(fragmentShader, vertexShader, ShaderPtr());

                vertexShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_blur_vert.cg"), 
                                                     VERTEX_SHADER_DESC("VertexProgram"));
                fragmentShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_blur_frag.cg"), 
                                                       FRAGMENT_SHADER_DESC("FragmentProgram"));
            
                mSSAOBlurTechnique = mEffect->appendTechnique(fragmentShader, vertexShader, ShaderPtr());

                vertexShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_composite_vert.cg"), 
                                                     VERTEX_SHADER_DESC("VertexProgram"));
                fragmentShader = mEffect->createShader(MIST_LOAD_RESOURCE(L"deferred/ssao_composite_frag.cg"), 
                                                       FRAGMENT_SHADER_DESC("FragmentProgram"));

                mCompositeTechnique = mEffect->appendTechnique(fragmentShader, vertexShader, ShaderPtr());
            }
        }

        {
            mRandomNormalTex = gf.load2DTexture(mist::ResourceLoader::Instance().loadResource(L"RandomNormals.png"));
        }

        return true;
    }

    void SSAO::makeSSAO(const CompositeRenderTargetPtr& gbuffer) {
        GraphicDevice& gd = Context::Instance().getGraphicFactory().getGraphicDevice();

        mRT->attach(ATT_Color0, mSSAOTarget);
        mRT->attachToRender();
        gd.clear(CM_Color, color::White, 1.0f, 0);

        const ShaderPtr& fragmentShader = mSSAOTechnique->getPass(0)->getFragmentShader();
        fragmentShader->setTextureVariable("normalMap", gbuffer->getTargetTexture(ATT_Color1));
        fragmentShader->setTextureVariable("depthMap", gbuffer->getTargetTexture(ATT_Color2));
        fragmentShader->setTextureVariable("randNormalMap", mRandomNormalTex);

        gd.setSamplerState(SamplerStateObject::LinearClamp(), 0);
        gd.setSamplerState(SamplerStateObject::PointClamp(), 1);
        gd.setSamplerState(SamplerStateObject::LinearWrap(), 2);

        float3 cornerFrustum;
        const CameraPtr& cam = gd.getCurrFrameBuffer()->getViewport().camera;
        cornerFrustum[1] = float(tanf(cam->getFOV() / 2.0f)) * cam->getFarPlane();
        cornerFrustum[0] = cornerFrustum[1] * cam->getAspect();
        cornerFrustum[2] = cam->getFarPlane();
        mSSAOTechnique->getPass(0)->getVertexShader()->setFloatVectorVariable("cornerFrustum", cornerFrustum);
        fragmentShader->setMatrixVariable("projection", cam->getProjMatrix());
        fragmentShader->setFloatVariable("sampleRadius", mSampleRadius);
        fragmentShader->setFloatVariable("distanceScale", mDistanceScale);
        fragmentShader->setFloatVectorVariable("gbufferSize", this->size());

        SpriteBatch::DefaultObject().drawQuad(mSSAOTechnique, Vector2(-1, 1), Vector2(1, -1));

        mRT->detachFromRender();
    }
    
    void SSAO::makeSSAOBlur(const CompositeRenderTargetPtr& gbuffer) {
        GraphicDevice& gd = Context::Instance().getGraphicFactory().getGraphicDevice();

        mRT->attach(ATT_Color0, mSSAOBlurTarget);
        mRT->attachToRender();
        gd.clear(CM_Color, color::White, 1.0f, 0);

        gd.setSamplerState(SamplerStateObject::LinearClamp(), 2);

        const ShaderPtr& fragmentShader = mSSAOBlurTechnique->getPass(0)->getFragmentShader();
        fragmentShader->setTextureVariable("normalMap", gbuffer->getTargetTexture(ATT_Color1));
        fragmentShader->setTextureVariable("depthMap", gbuffer->getTargetTexture(ATT_Color2));
        fragmentShader->setTextureVariable("SSAO", mSSAOTarget->getTexture());

        fragmentShader->setFloatVectorVariable("blurDirection", float2(1, 1));
        fragmentShader->setFloatVectorVariable("targetSize", this->size());
        
        SpriteBatch::DefaultObject().drawQuad(mSSAOBlurTechnique, Vector2(-1, 1), Vector2(1, -1));

        mRT->detachFromRender();
    }

    void SSAO::makeFinal(const TexturePtr& target) {
        GraphicDevice& gd = Context::Instance().getGraphicFactory().getGraphicDevice();

        mRT->attach(ATT_Color0, mCompositeTarget);
        mRT->attachToRender();
        gd.clear(CM_Color, color::White, 1.0f, 0);

        const ShaderPtr& fragmentShader = mCompositeTechnique->getPass(0)->getFragmentShader();
        fragmentShader->setTextureVariable("colorMap", target);
        fragmentShader->setTextureVariable("SSAO", this->mSSAOTarget->getTexture());
        
        SpriteBatch::DefaultObject().drawQuad(mCompositeTechnique, Vector2(-1, 1), Vector2(1, -1));

        mRT->detachFromRender();
    }

    const TexturePtr& SSAO::getFinalTexture() const {
        return mCompositeTarget->getTexture();
    }

} // namespace ukn