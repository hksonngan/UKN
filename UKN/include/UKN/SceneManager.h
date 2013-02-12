#ifndef Project_Unknown_SceneManager_h
#define Project_Unknown_SceneManager_h

#include "UKN/PreDeclare.h"
#include "UKN/Frustum.h"
#include "UKN/Renderable.h"

namespace ukn {

    class UKN_API SceneManager: Uncopyable {
    public:
        typedef std::vector<SceneObjectPtr> SceneObjectList;
        
    protected:
        typedef std::vector<RenderablePtr> RenderItemsList;
        
    public:
        SceneManager();
        virtual ~SceneManager();
        
        static SceneManagerPtr NullObject();
        
        virtual void clipScene();
        
        void addSceneObject(const SceneObjectPtr& obj);
        void delSceneObject(const SceneObjectPtr& obj);
        
        void addRenderable(const RenderablePtr& renderable);
        
        SceneObjectList& getSceneObjects();
        const SceneObjectList& getSceneObjects() const;
        
        virtual bool isBoxVisible(const Box& box);
        
        void clear();
        
        void update();
        
        uint32 numObjectsRendered() const;
        uint32 numRenderableRendered() const;
        uint32 numPrimitivesRenderered() const;
        uint32 numVerticesRendered() const;
        
    protected:
        void flush();
        
        virtual void onAddSceneObject(const SceneObjectPtr& obj);
        virtual void onDelSceneObject(const SceneObjectPtr& obj);
        
    protected:
        const Frustum* mFrustim;
        
        SceneObjectList mSceneObjects;
        
    private:
        void flushScene();
        
        uint32 mNumObjectsRendered;
        uint32 mNumRenderableRendered;
        uint32 mNumPrimitivesRendered;
        uint32 mNumVerticesRendered;
    };
    
}


#endif