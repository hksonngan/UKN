//
//  App.h
//  Project Unknown
//
//  Created by Robert Bu on 11/24/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef Project_Unknown_App_h
#define Project_Unknown_App_h

#include "mist/Platform.h"
#include "mist/Uncopyable.h"
#include "mist/Signal.h"
#include "mist/Event.h"

#include "UKN/PreDeclare.h"
#include "UKN/GraphicSettings.h"

namespace ukn {
    
    // Game App Luncher
    
    class AppInstance: public Uncopyable {
    public:
        AppInstance(const UknString& name);
        ~AppInstance();
        
        Window&     getWindow() const;
		WindowPtr   getWindowPtr() const;
        
        void create(const UknString& cfgname=L"config.xml");
        void create(const ContextCfg& cfg);
        
        void run();
        void terminate();
        
        void update();
        void render();
        
        void        setCamera(CameraPtr camera);
        CameraPtr   getCamera() const;
        
    protected:
        virtual void onRender();
        virtual void onUpdate();
        virtual void onInit();
        
    private:
        void doCreate();
        void onWindowClose(void* wnd, NullEventArgs&);
        
        UknString mName;
        bool mInited;    

        WindowPtr mMainWindow;
        CameraPtr mCamera;
    };
    
} // namespace ukn

#endif
