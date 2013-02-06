//
//  BlendStateObject.h
//  Project Unknown
//
//  Created by Robert Bu on 2/5/13.
//  Copyright (c) 2013 heizi. All rights reserved.
//

#ifndef Project_Unknown_BlendStateObject_h
#define Project_Unknown_BlendStateObject_h

#include "UKN/PreDeclare.h"
#include "UKN/GraphicSettings.h"

namespace ukn {
    
    // blend state descriptor
    // used in d3d10+ to improve performance
    // currently one render target only
    
    struct UKN_API BlendStateDesc {
        // gl_sample_alpha_to_coverage_arb
        bool alpha_to_converage;
        
        /* rgba blend factor */
        float4 blend_factor;
        
        struct BlendState {
            bool enabled;
            RenderStateParam src;
            RenderStateParam dst;
            RenderStateParam op;
            RenderStateParam src_alpha;
            RenderStateParam dst_alpha;
            RenderStateParam op_alpha;
            uint8 write_mask; // D3D*_COLOR_WRITE_ENABLE_ALL
        };
        BlendState blend_state;
    };
    
    class UKN_API BlendStateObject {
    public:
        BlendStateObject(const BlendStateDesc& desc):
        mDesc(desc) {
        }
        
        // force base
        virtual ~BlendStateObject() = 0;
      
        const BlendStateDesc& getDesc() const { return mDesc; }
        
    private:
        BlendStateDesc mDesc;
    };
    
}


#endif
