#include "mist/Platform.h"
#include "ukn/Shader.h"

#include <d3dcommon.h>
#include "Cg/cg.h"

#if defined(MIST_PLATFORM_32)
#pragma comment(lib, "lib/cg.lib")
#pragma comment(lib, "lib/cgD3D11.lib")
#else
#pragma comment(lib, "libx.64/cg.lib")
#pragma comment(lib, "libx.64/cgD3D11.lib")
#endif

struct ID3D11InputLayout;

namespace ukn {

    class D3D11GraphicDevice;

    class DxEffectPass: public EffectPass {
    public:
        DxEffectPass(Effect* parent, D3D11GraphicDevice*);
        virtual ~DxEffectPass();

    private:
        D3D11GraphicDevice* mDevice;
    };

    class CgDxEffect: public Effect {
    public:
        CgDxEffect(D3D11GraphicDevice* device);
        virtual ~CgDxEffect();

        void bind(uint32 pass) override;
        void unbind(uint32 pass) override;

        ShaderPtr createShader(const ResourcePtr& resource, const ShaderDesc& desc) override;
        EffectPassPtr createPass() override;

        CGcontext getContext() const;

    private:
        CGcontext mContext;
        D3D11GraphicDevice* mDevice;
    };

    class CgDxShader: public Shader {
    public:
        CgDxShader(CGcontext context);
        virtual ~CgDxShader();

        bool initialize(D3D11GraphicDevice* device, const ResourcePtr& resource, const ShaderDesc& desc);

        bool setMatrixVariable(const char* name, const Matrix4& mat) override;
	    bool setFloatVectorVariable(const char* name, const float4& vec) override;
	    bool setIntVectorVariable(const char* name, const int4& vec) override;
	    bool setTextureVariable(const char* name, const TexturePtr& tex) override;

        bool setFloatVariable(const char* name, uint32 len, const float* vals) override;
        bool setIntVariable(const char* name, uint32 len, const int* vals) override;
        
	    bool getMatrixVariable(const char* name, Matrix4& mat) override;
	    bool getFloatVectorVariable(const char* name, float4& vec) override;
	    bool getIntVectorVariable(const char* name, int4& vec) override;

        void bind() override;
        void unbind() override;
        
        CGprogram getProgram() const;
        CGcontext getContext() const;
        const ShaderDesc& getDesc() const;

        ID3DBlob* getCompiledProgram() const;

    private:
        CGprogram mProgram;
        CGcontext mContext;
        ShaderDesc mDesc;
    };

}