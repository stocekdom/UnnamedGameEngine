//
// Created by dominik on 10.12.25.
//

#ifndef GAME1_LOGGER_H
#define GAME1_LOGGER_H
#include <ctime>
#include <fstream>
#include <string>

#define LOG_ERROR( message ) logging::Logger::log( logging::LogLevel::ERROR, message );
#define LOG_WARNING( message ) logging::Logger::log( logging::LogLevel::WARNING, message );
#define LOG_INFO( message ) logging::Logger::log( logging::LogLevel::INFO, message );
#define LOG_DEBUG( message ) logging::Logger::log( logging::LogLevel::DEBUG, message );

#define RUNTIME_ERROR throw std::runtime_error( "Application runtime error" );

namespace logging
{
   enum class LogLevel
   {
      DEBUG,
      INFO,
      WARNING,
      ERROR
   };

   class Logger
   {
      public:
         Logger();

         ~Logger();

         Logger( const Logger& ) = delete;

         Logger& operator=( const Logger& ) = delete;

         static void log( LogLevel level, const std::string& message );

      private:
         //

         std::ofstream logFile;

         static Logger& getInstance();

         static std::tm getTime();

         static std::string getTimeString( const std::tm& time );

         static std::string levelToString( LogLevel level );

         static std::string levelToColor( LogLevel level );

         void logImpl( LogLevel level, const std::string& message );
   };
}
#endif //GAME1_LOGGER_H
