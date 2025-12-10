//
// Created by dominik on 10.12.25.
//

#include "Logger.h"

#include <chrono>
#include <iostream>
#include <filesystem>

logging::Logger::Logger()
{
   std::string path = "Logs";

   std::error_code ec;

   if( !std::filesystem::create_directory( path, ec ) )
   {
      if( ec )
      {
         std::cerr << levelToColor( LogLevel::ERROR ) << getTimeString( getTime() ) << " " << levelToString( LogLevel::ERROR ) <<
               "Could not create Logs directory " << path << "\033[0m" << std::endl;
         RUNTIME_ERROR;
      }
   }

   path += "/";
   path += getTimeString( getTime() ) + ".log";
   logFile.open( path, std::ios::out | std::ios::app );

   if( !logFile.is_open() )
   {
      std::cerr << levelToColor( LogLevel::ERROR ) << getTimeString( getTime() ) << " " << levelToString( LogLevel::ERROR ) <<
            "Could not open log file at " << path << "\033[0m" << std::endl;
      RUNTIME_ERROR;
   }
}

logging::Logger::~Logger()
{
   if( logFile.is_open() )
      logFile.close();
}

void logging::Logger::log( LogLevel level, const std::string& message )
{
   getInstance().logImpl( level, message );
}

logging::Logger& logging::Logger::getInstance()
{
   static Logger instance;
   return instance;
}

std::tm logging::Logger::getTime()
{
   auto now = std::chrono::system_clock::now();
   std::time_t t = std::chrono::system_clock::to_time_t( now );
   std::tm time;

#ifdef _WIN32
   localtime_s( &time, &t );
#else
   localtime_r( &t, &time );
#endif

   return time;
}

std::string logging::Logger::getTimeString( const std::tm& time )
{
   std::stringstream ss;
   ss << std::put_time( &time, "%d.%m.%Y %H:%M:%S" );
   return ss.str();
}

std::string logging::Logger::levelToString( LogLevel level )
{
   switch( level )
   {
      case LogLevel::DEBUG: return "[DEBUG]: ";
      case LogLevel::INFO: return "[INFO]: ";
      case LogLevel::WARNING: return "[WARNING]: ";
      case LogLevel::ERROR: return "[ERROR]: ";
      default: return "[UNKNOWN]: ";
   }
}

std::string logging::Logger::levelToColor( LogLevel level )
{
   switch( level )
   {
      case LogLevel::DEBUG: return "\033[96m";
      case LogLevel::INFO: return "\033[92m";
      case LogLevel::WARNING: return "\033[93m";
      case LogLevel::ERROR: return "\033[91m";
      default: return "\033[0m";
   }
}

void logging::Logger::logImpl( LogLevel level, const std::string& message )
{
   // TODO [WARN] not thread safe. Add mutex if using multiple threads
   const auto levelStr = levelToString( level );
   const auto timeStr = getTimeString( getTime() );

   std::cout << levelToColor( level ) << timeStr << " " << levelStr << message << "\033[0m" << std::endl;

   if( logFile.is_open() )
   {
      logFile << timeStr << " " << levelStr << message << std::endl;
      logFile.flush();
   }

   if( level == LogLevel::ERROR )
      RUNTIME_ERROR;
}
