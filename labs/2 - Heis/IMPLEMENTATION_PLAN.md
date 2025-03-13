# Elevator Implementation Plan

## 1. Implement Stop Button Functionality
- Add stop button detection in the input handling
- Update state machine to handle stop button presses
- Implement the safety requirements (S4-S7)
- Clear all orders when stop button is pressed
- Keep door open while stop button is pressed when at a floor

## 2. Add Obstruction Detection
- Add obstruction detection in the input handling
- Update door logic to keep door open during obstruction
- Implement 3-second timer after obstruction is cleared

## 3. Implement DOOR_OPEN State
- Add DOOR_OPEN as a proper state in the state machine
- Update the state transitions to include DOOR_OPEN state
- Ensure elevator is always stationary when door is open
- Keep track of door timer

## 4. Improve Order Handling
- Fix the direction logic to properly handle up/down orders
- Ensure elevator completes current direction before changing
- Make sure all orders are correctly served

## 5. Refine Safety Features
- Add checks to prevent door opening between floors
- Add boundary checks to prevent elevator moving outside defined floors
- Implement proper handling of edge cases

## 6. Testing and Debugging
- Test each FAT requirement systematically
- Fix any bugs or inconsistencies
- Ensure all requirements are met

## Implementation Order
1. Modify states.c to include DOOR_OPEN state in the state machine
2. Update input.c to detect stop button and obstruction
3. Implement stop button logic
4. Implement obstruction logic
5. Refine order handling logic
6. Final testing and debugging

## Code Changes Required
- Update main.c to include DOOR_OPEN in the state machine switch
- Create stop_button.c and stop_button.h for stop button functionality
- Update open_door() function to handle obstruction
- Add door timer functionality
- Improve the standing_still, driving_up, and driving_down functions