/***********************************************************************
 *
 * Author: Louis Chen
 * Copyright (c) 2010-2011 NanoSoft, Inc. All rights reserved.
 *
 ***********************************************************************/

#include <log/Logger.h>
#include <io.h>
#include <exception.h>

namespace EasyCoding {

    // class logger

    logger* logger::g_logger = NULL;
	string logger::g_strCfgFile;

    logger::logger()
        : _root(NULL), _sub1(NULL), _sub2(NULL)
    {
    }

    logger::~logger()
    {
        log4cpp::Category::shutdown();
        _root = _sub1 = _sub2 = NULL;
    }

    bool
    logger::init()
    {
        // Logger
        try { 
            log4cpp::PropertyConfigurator::configure(g_strCfgFile);

            _root = &log4cpp::Category::getRoot();
            _sub1 = &log4cpp::Category::getInstance(std::string("sub1"));
            _sub2 = &log4cpp::Category::getInstance(std::string("sub2"));

            return true;
        } catch(log4cpp::ConfigureFailure& e) {
            std::cout << "** Initialize logger error: " << e.what() << std::endl;
            return false;
        }
    }

    bool logger::set_config_file(const char *path)
    {
        if (0 == access(path, 4/*read only*/)) {
			// 文件存在具有读权限
            g_strCfgFile = path;
            return true;
        }
        return false;
    }

    log4cpp::Category*
    logger::instance(LOG_CATEGORY type)
    {
        if (!g_logger) {
            g_logger = new logger();
            if (!g_logger->init()) {
                delete g_logger; g_logger = NULL;
                throw Exception(1, "init logger failed!");
            }
        }

        switch (type) {
        case LOG_SUB1:
            return g_logger->_sub1;
        case LOG_SUB2:
            return g_logger->_sub2;
        case LOG_ROOT:
        default:
            return g_logger->_root;
        }
    }

    void
    logger::uninstance()
    {
		if (g_logger) {
			delete g_logger; g_logger = NULL;
        }
    }



    // class function_tracer

    function_tracer::function_tracer(const char* pszFuncName)
        : _szName(pszFuncName)
    {
        try {
            logger::instance(logger::LOG_SUB2)->debug("Entering %s() ===> |", _szName.c_str());
        } catch (Exception& e) {
			cout << e.what() << endl;
        }
    }

    function_tracer::~function_tracer()
    {
        try {
            logger::instance(logger::LOG_SUB2)->debug("Leaving %s() <=== |", _szName.c_str());
		} catch (Exception& e) {
			cout << e.what() << endl;
        }
    }

}

