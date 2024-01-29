#include "Grapher.hpp"

namespace graphy {

AsyncGrapher::AsyncGrapher(const std::string &title, const uint rate) {
    this->title = title;
    this->refreshRate = rate;
    cnt = 0;
}

void AsyncGrapher::addDataType(const std::string &name, const uint32_t color) {
    if (cnt > MAX_DATA) {
        std::runtime_error("Error: max number of data is 14");
    } else {
        cnt++;
        container.insert({name, {0.0}});
        colors.insert({name, color});
    }
}

void AsyncGrapher::update(const std::string &name, double val, double maxValArg) {

    static int maxVal = 1;

    static int updateSize = 0;

    if (val > maxVal && autoZoom) {
        maxVal = val;
        container[name].push_back(val / maxVal);
        updateSize++;

        // If it's gone through half the length of the graph (doesn't run constantly to save resources)
        if (updateSize > MAX_CACHE_SIZE / 2) {
            // Resets the variables.
            maxVal = 1; 
            updateSize = 0;

            // Find the max value in the container, then continue graphing at that max value.
            for (const auto &item : container) {
                for (int i = 0; i < item.second.size(); i++) {
                    double val1 = item.second[i];
                    if (val1 > maxVal) {
                        maxVal = val1;
                    }
                }
            }
        }
    }
    else {
        container[name].push_back(val / maxValArg);
    }

    if (container[name].size() > MAX_CACHE_SIZE) {
        container[name].erase(container[name].begin());
    }


    
}

void AsyncGrapher::setRefreshRate(const uint rate) {
    this->refreshRate = rate;
}

uint AsyncGrapher::getRefreshRate() {
    return this->refreshRate;
}

void AsyncGrapher::loop() {
    while (true) {
        // Reset screen
        pros::screen::erase();

        // Draw graph
        pros::screen::set_pen(COLOR_WHITE);
        pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 1, title.c_str());
        pros::screen::draw_line(GRAPH_LEFT, GRAPH_TOP, GRAPH_LEFT, GRAPH_BOTTOM);
        pros::screen::draw_line(
          GRAPH_LEFT, GRAPH_BOTTOM, GRAPH_LEFT + MAX_CACHE_SIZE, GRAPH_BOTTOM);

        int indexLine = 0;
        for (const auto &item : container) {
            pros::screen::set_pen(colors[item.first]);
            pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL,
                                GRAPH_LEFT + MAX_CACHE_SIZE,
                                (++indexLine) * 14 + 30,
                                item.first.c_str());
            for (int i = 0; i < item.second.size() - 1; i++) {
                double val1 = item.second[i] * (GRAPH_BOTTOM - GRAPH_TOP);
                double val2 = item.second[i + 1] * (GRAPH_BOTTOM - GRAPH_TOP);
                pros::screen::draw_line(
                  GRAPH_LEFT + i, GRAPH_BOTTOM - val1, GRAPH_LEFT + i + 1, GRAPH_BOTTOM - val2);
            }
        }

        pros::delay(refreshRate);
    }
}

std::map<std::string, std::vector<double>>& AsyncGrapher::getContainer() {

    return container;
    
}

void AsyncGrapher::activateAutoZoom() {
    autoZoom = true;
}

void AsyncGrapher::deactivateAutoZoom() {
    autoZoom = false;
}

void AsyncGrapher::insertNewGraph(std::pair<std::string, std::vector<double>>& newGraph, uint32_t color) {
    if (cnt > MAX_DATA) {
        std::runtime_error("Error: max number of data is 14");
    } else {
        cnt++;
        container.insert({newGraph.first, newGraph.second});
        colors.insert({newGraph.first, color});
    }
}

}  // namespace graphy