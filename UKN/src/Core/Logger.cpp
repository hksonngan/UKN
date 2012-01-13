//
//  Logger.cpp
//  Project Unknown
//
//  Created by Robert Bu on 12/1/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#include "UKN/Logger.h"
#include "UKN/Stream.h"
#include "UKN/TimeUtil.h"
#include "UKN/Common.h"
#include "UKN/StringUtil.h"

namespace ukn {
    
    Logger& Logger::Instance() {
        static Logger* g_Instance = 0;
        if(!g_Instance) {
            FileStream* default_stream = new FileStream();
            // open with no write buffer, no append and write mode
            default_stream->open(L"ukn_log.txt", true, false, true);
            g_Instance = new Logger(StreamPtr(default_stream));
        }
        return *g_Instance;
    }
    
    Logger::Logger(StreamPtr outputStream):
    mOutputStream(outputStream),
    mPrependTime(true),
    mPrependLevel(true) {
        
    }
    
    Logger::~Logger() {
        if(mOutputStream)
            mOutputStream->close();
    }
    
    void Logger::redirect(StreamPtr outputStream) {
        mOutputStream = outputStream;
    }
    
    void Logger::setFeature(LoggerFeature feature, bool flag) {
        switch(feature) {
            case LF_PrependRunningTime:
                mPrependTime = flag;
                break;
            case LF_PrependLevelName:
                mPrependLevel = flag;
                break;
            case LF_OutputToConsole:
                mOutputToConsole = flag;
                break;
        }
    }
    
    inline String loglevel_to_string(LogLevel level) {
        switch(level) {
            case LL_Error:
                return "*Error* ";
            case LL_Warning:
                return "*Warning* ";
            case LL_Notice:
                return "*Notice* ";
            case LL_Info:
            default:
                return String();
        }
    }
    
    void Logger::log(const String& log, LogLevel level) {
        String realLog;
        if(mPrependTime) {
            realLog += String(format_string("[%.3f] ", (float)FrameCounter::Instance().getRunningTime() / Timestamp::Resolution()));
        }
        if(mPrependLevel) {
            realLog += loglevel_to_string(level);
        }
        realLog += log;
        
        mLogQueue.push_back(realLog);
        
        if(mOutputStream) {
#ifdef UKN_OS_WINDOWS
            *mOutputStream<<realLog.ansi_str()<<"\r\n";
#else
			*mOutputStream<<realLog.ansi_str()<<"\n";
#endif // UKN_OS_WINDOWS
            if(mOutputToConsole) {
                printf("%s\n", realLog.ansi_str());
            }
        }
    }
    
    Logger& Logger::operator<<(const String& log) {
        this->log(log, LL_Info);
        return *this;
    }
    
    void Logger::clear() {
        mLogQueue.clear();
    }
    
    size_t Logger::getLogSize() const {
        return mLogQueue.size();
    }
   
    const std::deque<String>& Logger::getLogQueue() const {
        return mLogQueue;
    }
    
    void log_error(const String& log) {
        Logger::Instance().log(log, LL_Error);
    }
    
    void log_notice(const String& log) {
        Logger::Instance().log(log, LL_Notice);
    }
    
    void log_warning(const String& log) {
        Logger::Instance().log(log, LL_Warning);
    }
    
    void log_info(const String& log) {
        Logger::Instance().log(log, LL_Info);
    }
    
    
} // namespace ukn
