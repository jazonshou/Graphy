#pragma once
#include <map>
#include <stdexcept>
#include <string>

#include "TaskWrapper.hpp"
#include "okapi/api/units/QTime.hpp"
#include "pros/screen.hpp"


#define MAX_CACHE_SIZE 360
#define GRAPH_TOP 40
#define GRAPH_BOTTOM 215
#define GRAPH_LEFT 25
#define GRAPH_RIGHT 455
#define MAX_DATA 14

namespace graph {

class AsyncGrapher : public TaskWrapper {
    private:
    std::map<std::string, std::vector<double>> container;
    std::map<std::string, uint32_t> colors;
    std::string title;
    okapi::QTime refreshRate;
    int cnt;

    public:
    /**
     * @brief Construct a new Async Grapher object
     *
     * @param title graph title
     * @param rate refresh rate
     */
    AsyncGrapher(const std::string &title, const okapi::QTime &rate = 10 * okapi::millisecond);

    /**
     * @brief Add new graph data type
     *
     * @param name data type name
     * @param color line color
     */
    void addDataType(const std::string &name, const uint32_t color);

    /**
     * @brief Update graph
     *
     * @param name data type name
     * @param val updated data value
     */
    void update(const std::string &name, double val);

    /**
     * @brief Set the refresh rate
     *
     * @param rate refresh rate
     */
    void setRefreshRate(const okapi::QTime &rate);

    /**
     * @brief Get the current refresh rate
     *
     * @return refresh rate
     */
    okapi::QTime getRefreshRate();

    protected:
    void loop() override;
};

}  // namespace graph