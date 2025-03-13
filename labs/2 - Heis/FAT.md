# FAT (Factory Acceptance Test) Tracking

This document tracks the requirements and their implementation status for the elevator project.

## Implemented Features

- Basic state machine (STANDING_STILL, DRIVING_UP, DRIVING_DOWN)
- Button input detection
- Floor sensor detection
- Floor indicator light functionality
- Basic elevator movement (up/down)
- Button lamp functionality (turning on when pressed)
- Turning off button lamps when reaching a destination floor
- Basic door open/close functionality (3-second timer)
- Elevator startup initialization (drives to bottom floor)

## Features To Implement

### Oppstart (Startup)
- [x] O1: Elevator in defined state at startup (currently goes to floor 0)
- [x] O2: Ignore bestillings before elevator is in defined state
- [x] O3: Reject unrealistic start conditions (ignore stop button during init)

### Håndtering av bestillinger (Order Handling)
- [x] H1: Ensure all orders are served 
- [x] H2: Implement proper order handling logic (don't handle orders in opposite direction)
- [x] H3: Mark orders at current floor as completed
- [x] H4: Elevator should stand still when there are no unserved orders

### Bestillingslys og etasjelys (Order and Floor Lights)
- [x] L1: Order button light turns on when order is made
- [x] L2: Order button light turns off when no corresponding order exists
- [x] L3: Correct floor light is on when elevator arrives at a floor
- [x] L4: Floor light shows last visited floor when elevator is between floors
- [x] L5: Only one floor light is on at a time
- [x] L6: Stop button light is on while pressed, off when released

### Heis-dør (Elevator Door)
- [x] D1: Door opens for 3 seconds when arriving at a floor with an active order
- [x] D2: Door is closed when there are no unserved orders
- [x] D3: If stop button is pressed at a floor, the door opens and remains open
- [x] D4: If obstruction is activated, door remains open until obstruction is deactivated

### Sikkerhet (Safety)
- [x] S1: Elevator is always stationary when door is open
- [x] S2: Door never opens outside of a floor
- [x] S3: Elevator never moves outside defined area (1-4 floors)
- [x] S4: Elevator stops immediately when stop button is pressed
- [x] S5: All unserved orders are deleted when stop button is pressed
- [x] S6: Elevator ignores all new orders while stop button is held
- [x] S7: After stop button is released, elevator stands still until new orders arrive

### Robusthet (Robustness)
- [x] R1: Obstruction switch doesn't affect system when door is closed
- [x] R2: Program doesn't need to be restarted due to undefined behavior
- [x] R3: After elevator reaches defined state at startup, no new calibration rounds are necessary

## FAT Test Cases Status

### Oppstart (Startup)
- [x] O1: Test elevator reaching defined state
- [x] O2: Test ignoring orders before defined state
- [x] O3: Test ignoring stop button during initialization

### Håndtering av bestillinger (Order Handling)
- [x] H1: Test elevator going to correct floor when order from floor panel
- [x] H2: Test elevator going to correct floor when order from elevator panel
- [x] H3: Test elevator completing downward journey before handling upward orders
- [x] H4: Test handling of multiple buttons pressed simultaneously
- [x] H5: Test all orders are served, even with continuous button presses

### Bestillingslys og etasjelys (Order and Floor Lights)
- [x] L1: Test correct floor light is on when elevator arrives
- [x] L2: Test floor light behavior when elevator is between floors
- [x] L3: Test order button lights turn on when pressed
- [x] L4: Test order button lights turn off when order is served

### Heis-dør (Elevator Door)
- [x] D1: Test door opens when elevator stops at a floor
- [x] D2: Test door remains open for 3 seconds
- [x] D3: Test elevator stands still while door is open
- [x] D4: Test door closes before elevator moves
- [x] D5: Test door closes and elevator stands still with no new orders

### Sikkerhet (Safety)
- [x] S1: Test elevator stops immediately when stop button is pressed
- [x] S2: Test all orders are deleted when stop button is pressed
- [x] S3: Test stop button light is on while pressed
- [x] S4: Test all order buttons are ignored while stop button is active
- [x] S5: Test elevator remains stationary after stop button is released
- [x] S6: Test elevator remembers position after emergency stop between floors
- [x] S7: Test door opens if stop button is activated at a floor

### Robusthet (Robustness)
- [x] R1: Test program stability during presentation

## Implementation Plan

### Priority 1: Core Functionality
1. Implement stop button functionality
2. Implement obstruction detection
3. Fix door behavior (with obstruction handling)

### Priority 2: Order Handling
1. Improve order handling logic to meet requirement H2
2. Ensure all orders are served (H1)

### Priority 3: Safety Features
1. Implement proper safety checks (S1-S7)

### Priority 4: Testing and Refinement
1. Test all FAT requirements
2. Refine code and fix bugs