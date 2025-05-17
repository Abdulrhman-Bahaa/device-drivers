#include "oled.hpp"


class OledLine {
    private:
        uint8_t start_x;
        uint8_t start_y;
        uint8_t end_x;
        uint8_t end_y;
        uint8_t thickness;

    public:
    OledLine(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y) {
        this->start_x = start_x;
        this->start_y = start_y;
        this->end_x = end_x;
        this->end_y = end_y;
        this->thickness = 1;
    }

    OledLine() {
        this->start_x = 0;
        this->start_y = 0;
        this->end_x = 0;
        this->end_y = 0;
        this->thickness = 1;
    }
};