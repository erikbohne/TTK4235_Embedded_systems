#pragma once

void checkForInput(state_data *data);
void turnOffButtonLamps(state_data *data, int floor);
int getNextUp(int buttons[4][3], int current);
int getNextDown(int buttons[4][3], int current);