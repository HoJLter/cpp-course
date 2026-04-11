#include "core/Application.h"
#include "utils/Logger.h"
#include <ctime>
#include <sstream>
#include <iomanip>

int main() {
    //Application app(600, 800);
    //app.run();
    Log::setLogger(LoggerType::Console);
    Log::info("WASSUP");
    Log::info("WASSUP");
    Log::setLogger(LoggerType::File);
    Log::info("WASSUP");
    Log::warn("WASSUP");
    Log::error("WASSUP");
    Log::info("WASSUP");

    
}