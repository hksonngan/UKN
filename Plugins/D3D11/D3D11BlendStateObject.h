#include "UKN/BlendStateObject.h"

#include "D3D11Preq.h"

namespace ukn {

    class D3D11GraphicDevice;

    class D3D11BlendStateObject: public BlendStateObject {
    public:
        D3D11BlendStateObject(const BlendStateDesc& desc, D3D11GraphicDevice* device);
        virtual ~D3D11BlendStateObject();

        ID3D11BlendState* getD3DBlendState() const;

    private:
        COM<ID3D11BlendState>::Ptr mBlendState;
    };

}