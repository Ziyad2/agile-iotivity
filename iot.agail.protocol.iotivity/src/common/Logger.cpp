/*******************************************************************************
 * Copyright (c) 2016, 2017 FBK CREATE-NET
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Description: Logger
 *              Logger. Implementation file
 *
 * Contributors:
 *    Mattia Antonini
 *******************************************************************************/

#include "Logger.h"

Logger::Logger(std::ostream * stream, int lvl)
{
    assert(stream != NULL || stream != nullptr); //Abort if stream is null
    print = stream; 
    level = lvl;
}

void Logger::d(const std::string tag, const std::string message)
{
    if(level <= LEVEL_DEBUG)
    {
        // Print blue bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;34m";
        (* (print)) << "D - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}


void Logger::v(const std::string tag, const std::string message)
{
    if(level <= LEVEL_VERBOSE)
    {
        // (* (print)) cyan bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;36m";
        (* (print)) << "V - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}

void Logger::i(const std::string tag, const std::string message)
{
    if(level <= LEVEL_INFORMATIONAL)
    {
        // (* (print)) green bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;32m";
        (* (print)) << "I - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}

void Logger::w(const std::string tag, const std::string message)
{
    if(level <= LEVEL_WARNING)
    {
        // (* (print)) yellow bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;33m";
        (* (print)) << "W - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}

void Logger::e(const std::string tag, const std::string message)
{
    if(level <= LEVEL_ERROR)
    {
        // Print red bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;31m";
        (* (print)) << "E - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}

void Logger::c(const std::string tag, const std::string message)
{
    if(level <= LEVEL_CRITICAL)
    {
        // Print red bold
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[1;31m";
        (* (print)) << "C - " << tag << " : " << message;
        if((* (print)) == std::cout || (* (print)) == std::cerr) (* (print)) << "\033[0m";
        (* (print)) << std::endl;
    }
}
