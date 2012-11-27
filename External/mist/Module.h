//
//  Module.h
//  Mist
//
//  Created by Ruiwei Bu on 12/22/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#ifndef MISTModule_h
#define MISTModule_h

#include "mist/Platform.h"
#include "mist/Uncopyable.h"
#include "mist/Event.h"

#include <vector>
#include <map>

namespace mist {
    
    class DllLoader;
    
    class Module: Uncopyable {
    public:
        virtual const MistString& getName() const = 0;
        
        virtual bool init() = 0;
        
        virtual void update() = 0;
        
        virtual void shutdown() = 0;
    };
        
    class ModuleManager: Uncopyable {
    protected:
        ModuleManager();
        ~ModuleManager();
        
    public:
        static ModuleManager& Instance();
        static void Destroy();
        
        bool addModule(Module* module);
        bool delModule(Module* module);
        
        bool addModuleFromDll(const MistString& name);
        bool delModule(const MistString& name);
        
        void onUpdate(void*, NullEventArgs&);
        
    private:
        typedef std::vector<Module*> ModuleList;
        ModuleList mModules;
        
        void delModule(ModuleList::iterator it);
        
        typedef std::map<Module*, DllLoader*> ModuleLoaderMap;
        ModuleLoaderMap mModuleLoaders;
    };
    
} // namespace mist


#endif
