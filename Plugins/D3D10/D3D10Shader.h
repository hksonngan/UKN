#include "ukn/Shader.h"
#include "mist/Resource.h"

#include "D3D10Preq.h"

namespace ukn {

	class D3D10GraphicDevice;

	class D3D10Effect: public Shader {
	public:
		D3D10Effect(D3D10GraphicDevice* device);
		virtual ~D3D10Effect();

		bool initialize(mist::ResourcePtr& content);
		bool setLayout(const ukn::VertexFormat& format);

		virtual void bind() override;
		virtual void unbind() override;

		/*
			Variable Setters
		*/
		bool setMatrixVariable(const char* name, const D3DXMATRIX& worldMat);
		bool setRawVariable(const char* name, void* data, uint32 length);
		// vector variables are four-components 
		bool setFloatVectorVariable(const char* name, float* vec);
		bool setIntVectorVariable(const char* name, int* vec);

		/*
			Variable Getters
		*/
	    bool getMatrixVariable(const char* name, D3DXMATRIX* mat);
		bool getRawVariable(const char* name, void* data, uint32 len);
		bool getFloatVectorVariable(const char* name, float* vec);
		bool getIntVectorVariable(const char* name, int* vec);

		uint32 getPasses() const;
		void applyPass(uint32 pass);

	private:
		void logError(ID3D10Blob* error);

	private:
		ID3D10Effect* mEffect;
		ID3D10EffectTechnique* mTechnique;
		ID3D10InputLayout* mLayout;

		D3D10GraphicDevice* mDevice;
	};

	class D3D10VertexShader: public Shader {

	private:
		ID3D10VertexShader* mShader;
	};

	class D3D10FragmentShader: public Shader {

	private:
		ID3D10PixelShader* mShader;
	};

}