#include "Grapher.hpp"

AsyncGrapher::AsyncGrapher(const std::string &title, const okapi::QTime &rate) {
    this->title = title;
    this->refreshRate = rate;
}

void AsyncGrapher::addDataType(const std::string &name, const uint32_t color) {
    container.insert({name, {0.0}});
    colors.insert({name, color});
}

void AsyncGrapher::update(const std::string &name, double val) {
    container[name].push_back(val);
    if(container[name].size() > MAX_CACHE_SIZE) {
        container[name].erase(container[name].begin());
    }
}

void AsyncGrapher::setRefreshRate(const okapi::QTime &rate) {
    this->refreshRate = rate;
}

okapi::QTime AsyncGrapher::getRefreshRate() {
    return this->refreshRate;
}

void AsyncGrapher::loop() {
    while(true) {
        //Reset screen
        pros::screen::erase();

        // Draw graph
        pros::screen::set_pen(COLOR_WHITE);
        pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 1, title.c_str());
        pros::screen::draw_line(GRAPH_LEFT, GRAPH_TOP, GRAPH_LEFT, GRAPH_BOTTOM);
        pros::screen::draw_line(GRAPH_LEFT, GRAPH_BOTTOM, GRAPH_RIGHT, GRAPH_BOTTOM);

        for(const auto &item : container) {
            pros::screen::set_pen(colors[item.first]);
            for(int i = 0; i < item.second.size()-1; i++) {
                double val1 = item.second[i] * (GRAPH_BOTTOM - GRAPH_TOP);
                double val2 = item.second[i+1] * (GRAPH_BOTTOM - GRAPH_TOP);
                pros::screen::draw_line(GRAPH_LEFT + i, GRAPH_BOTTOM - val1, GRAPH_LEFT + i + 1, GRAPH_BOTTOM - val2);
            }
        }

        pros::delay(refreshRate.convert(okapi::millisecond));
    }
}