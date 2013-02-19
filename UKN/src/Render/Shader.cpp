//
//  Shader.cpp
//  Project Unknown
//
//  Created by Robert Bu on 9/5/12.
//  Copyright (c) 2012 heizi. All rights reserved.
//

#include "UKN/Shader.h"
#include "UKN/Context.h"

namespace ukn {

    EffectPass::EffectPass(Effect* parent):
        mParent(parent) {

    }

    EffectPass::~EffectPass() {
    
    }
        
    void EffectPass::setFragmentShader(const ShaderPtr& shader) {
        mFragmentShader = shader;
    }

    void EffectPass::setVertexShader(const ShaderPtr& shader) {
        mVertexShader = shader;
    }

    void EffectPass::setGeometryShader(const ShaderPtr& shader) {
        mGeometryShader = shader;
    }

    ShaderPtr EffectPass::getFragmentShader() const {
        return mFragmentShader;
    }

    ShaderPtr EffectPass::getVertexShader() const {
        return mVertexShader;
    }

    ShaderPtr EffectPass::getGeometryShader() const {
        return mGeometryShader;
    }

    const vertex_elements_type& EffectPass::getVertexFormat() const {
        return mFormat;
    }
    
    void EffectPass::setVertexFormat(const vertex_elements_type& format) {
        mFormat = format;
    }

    void EffectPass::begin() {
        if(mVertexShader)
            mVertexShader->bind();
        if(mFragmentShader)
            mFragmentShader->bind();
        if(mGeometryShader)
            mGeometryShader->bind();
    }

    void EffectPass::end() {
        if(mVertexShader)
            mVertexShader->unbind();
        if(mFragmentShader)
            mFragmentShader->unbind();
        if(mGeometryShader)
            mGeometryShader->unbind();
    }

    Effect::Effect() {

    }

    Effect::~Effect() {
    
    }
    
    void Effect::setVertexFormat(uint32 passIndex, const vertex_elements_type& format) {
        if(passIndex < this->getNumPasses()) {
            this->mPasses[passIndex]->setVertexFormat(format);
        } else
           log_error(L"Effect::setVertexFormat: pass overflow");
    }

    uint32 Effect::getNumPasses() const {
        return mPasses.size();
    }

    void Effect::appendPass(const EffectPassPtr& pass) {
        mPasses.push_back(pass);
    }

    EffectPassPtr Effect::createPass() {
        EffectPass* pass = new EffectPass(this);
        return EffectPassPtr(pass);
    }

    EffectPassPtr Effect::getPass(uint32 pass) const {
        if(pass < mPasses.size())
            return mPasses.at(pass);
        else
            log_error(format_string("Effect::getPass, pass %d overflows", pass));
    }

    EffectPassPtr Effect::appendPass() {
        EffectPassPtr pass = this->createPass();
        this->appendPass(pass);
        return pass;
    }

}