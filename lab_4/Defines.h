#pragma once

#include <QTimer>

#define FLOOR_COUNT 9
#define START_FLOOR 1

#define COLOR_ACTIVE_BUTTON "#00FF00"
#define COLOR_INACTIVE_BUTTON "#606060"

#define TEXT_GREEN "\033[0;32m"
#define TEXT_CYAN "\033[0;36m"
#define TEXT_BLUE "\033[0;34m"
#define TEXT_DEFAULT "\033[0m"

#define DOORS_STAYING_OPEN_TIME 1000
#define DOORS_MOVING_TIME 1000

#define MOVE_TIME 800
#define DOOR_OPENING_AFTER_CLOSING 600

#define ONE_FLOOR 1000
#define DOORS_TIME 1000
#define PASSENGERS_WAIT 1000

enum Direction {
    DOWN = -1,
    STAY = 0,
    UP = 1
};

#define NO_TARGET (-1)

#define STYLE \
    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, " \
    "stop: 0 #f0f0f0, stop: 0.5 #e8e8e8, stop: 1 #d0d0d0); " \
    "color: #2c3e50; " \
    "border: 2px solid #bdc3c7; " \
    "border-radius: 12px; " \
    "font: bold 12px 'Arial'; " \
    "padding: 6px; "

#define STYLE_PRESS \
    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, " \
    "stop: 0 #3498db, stop: 0.5 #2980b9, stop: 1 #1f4e79); " \
    "color: white; " \
    "border: 2px solid #2471a3; " \
    "border-radius: 12px; " \
    "font: bold 12px 'Arial'; " \
    "padding: 6px; "
