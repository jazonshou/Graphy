#pragma once
#include <map>
#include <stdexcept>
#include <string>

#include "TaskWrapper.hpp"
#include "pros/screen.hpp"


#define MAX_CACHE_SIZE 360
#define GRAPH_TOP 40
#define GRAPH_BOTTOM 215
#define GRAPH_LEFT 25
#define GRAPH_RIGHT 455
#define MAX_DATA 14

namespace graphy {

class AsyncGrapher : public TaskWrapper {
    private:
    std::map<std::string, std::vector<double>> container;
    std::map<std::string, uint32_t> colors;
    std::string title;
    uint refreshRate;
    int cnt;
    bool autoZoom = true;

    public:
    /**
     * @brief Construct a new Async Grapher object
     *
     * @param title graph title
     * @param rate refresh rate
     */
    AsyncGrapher(const std::string &title, const uint rate = 10);

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
     * @param maxValArg Value that the "val" gets divided by for placement on the graph.
     */
    void update(const std::string &name, double val, double maxValArg = 1);

    /**
     * @brief Set the refresh rate
     *
     * @param rate refresh rate
     */
    void setRefreshRate(const uint rate);

    /**
     * @brief Get the current refresh rate
     *
     * @return refresh rate
     */
    uint getRefreshRate();

    
    /**
     * @brief Get the Container of all values for the graphs
     * 
     * @return std::map<std::string, std::vector<double>>* 
     */
    std::map<std::string, std::vector<double>>& getContainer();

    /**
     * @brief If you have data points you want to plot, you can directly input them
     * with this function.
     * 
     * @param An std::pair to a string and then your data points
     */
    void insertNewGraph(std::pair<std::string, std::vector<double>>& newGraph, uint32_t color = COLOR_CORNFLOWER_BLUE);

    /**
     * @brief Make the graph automatically zoom in. Max value of the graph is at the top.
     * 
     */
    void activateAutoZoom();  

    /**
     * @brief Turns off auto zoom. All updates have to be divided by the max value.
     * 
     */
    void deactivateAutoZoom();

    protected:
    void loop() override;
};

}  // namespace graph
