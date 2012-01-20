//
//  Font.h
//  Project Unknown
//
//  Created by Robert Bu on 11/23/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef Project_Unknown_Font_h
#define Project_Unknown_Font_h

#include "UKN/Platform.h"
#include "UKN/Uncopyable.h"
#include "UKN/PreDeclare.h"
#include "UKN/Renderable.h"
#include "UKN/Serializer.h"
#include "UKN/Color.h"

#include <vector>

namespace ukn {
    
    /**
     * Font based on freetype for font loading and SpriteBatch for rendering
     **/
    
    enum FontAlignment {
        FA_Left     = 1UL,
        FA_Right    = 1UL << 1,
        FA_Center   = 1UL << 2,
        
        FA_XCenter  = 1UL << 3
    };
    
    enum FontStyle {
        FS_Shadow,
        FS_Stroke,
        FS_Italic,
        FS_Bold,
    };
    
    enum FontStyleProperty {
        FSP_Shadow_XOffset,
        FSP_Shadow_YOffset,
        FSP_Stroke_Width,
    };
    
    class UKN_API Font: Uncopyable, public virtual IRenderable, public virtual IConfigSerializable {
    public:
        Font();
        ~Font();
           
        /**
         * load from font config resource
         * should be .uknfnt
         **/
        bool loadFromResource(const ResourcePtr& resource);
        
        /**
         * set font style 
         **/
        void setStyle(FontStyle style, bool flag);
        void setStyleProperty(FontStyleProperty sp, int32 prop);
        
        void draw(const char* str, float x, float y, FontAlignment alignment, const Color& clr = color::White);
        
        // inherited from Renderable
        void render();
        
        void onRenderBegin();
        void onRenderEnd();
        
        float2 getStringDimensions(const char* str, float kw=0, float kh=0);
        
        const String& getName() const;
        
        Box getBound() const;
        RenderBufferPtr getRenderBuffer() const;
        
        bool isValid() const;
        
        bool deserialize(const ConfigParserPtr& cfg);
        bool serialize(const ConfigParserPtr& cfg);
        
    private:
        friend class AssetManager;
        
        uint32 getGlyphByChar(uint16 chr);
        void flushCache();
        void setFTStyle(uint32 style);
        
        uint32 mFontSize;
        String mFontName;
        
        bool mEnableStroke;
        bool mEnableShadow;
        
        int32 mStrokeWidth;
        int32 mShadowXOffset;
        int32 mShadowYOffset;
        
        SpriteBatchPtr mSpriteBatch;
        
        struct StringData;
        Array<StringData> mRenderQueue;
        
        void doRender(const StringData& data);
        
        struct FTLibrary;
        struct FTFace;
        struct FTGlyph;
        
        friend struct FTGlyph;
        
        ScopedPtr<FTFace> mFace;
        std::vector<FTGlyph> mGlyphs;
    };
    
} // namespace ukn  

#endif
