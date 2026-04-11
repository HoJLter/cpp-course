#include "core/Application.h"
#include "utils/Log.h"
#include <ctime>
#include <sstream>
#include <iomanip>

int main() {
    Log::setLogger(LoggerType::Console);
    Application app(600, 800);
    app.run();

}