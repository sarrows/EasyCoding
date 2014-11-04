/***********************************************************************
 *
 * Author: Louis Chen
 * Copyright (c) 2009-2010 NanoSoft, Inc. All rights reserved.
 *
 ***********************************************************************/

#pragma once

#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

using namespace std;

#ifndef EC_FUNC_TRACE
#define EC_FUNC_TRACE EasyCoding::function_tracer __func_trace
#endif

#ifndef EC_INFO
#define EC_INFO(...) EasyCoding::logger::instance(EasyCoding::logger::LOG_SUB1)->info(__VA_ARGS__)
#endif

#ifndef EC_DEBUG
#define EC_DEBUG(...) EasyCoding::logger::instance(EasyCoding::logger::LOG_SUB1)->debug(__VA_ARGS__)
#endif

#ifndef EC_WARN
#define EC_WARN(...) EasyCoding::logger::instance(EasyCoding::logger::LOG_SUB1)->alert(__VA_ARGS__)
#endif

#ifndef EC_ERROR
#define EC_ERROR(...) EasyCoding::logger::instance(EasyCoding::logger::LOG_SUB1)->fatal(__VA_ARGS__)
#endif 

#  if defined (EC_EXPORT)
#    define ECExport __declspec (dllexport)
#  else
#    define ECExport __declspec (dllimport)
#  endif

namespace EasyCoding {

    class ECExport logger {
    public:
        enum LOG_CATEGORY {
            LOG_SUB1 = 1,
            LOG_SUB2,
            LOG_ROOT
        };
        static log4cpp::Category* instance(LOG_CATEGORY type);
        static void uninstance();
        static bool set_config_file(const char *path);

    private:
        logger();
        virtual ~logger();
        bool init();

    private:
        static logger* g_logger;
        static string g_strCfgFile;
        log4cpp::Category* _root;
        log4cpp::Category* _sub1;
        log4cpp::Category* _sub2;
    };



    ////////////////////////////////////////////////////////////////////////////
    class ECExport function_tracer
    {
    public:
        function_tracer(const char* pszFuncName);
        ~function_tracer();
    private:
        string _szName;
    };

}
