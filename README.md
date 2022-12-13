# Hubris_navigator_manipulator_robot
Task:
- Navigate to the white board
- Draw on the whiteboard
- Return home

## Navigation Modes:
### 1. Curved path
- Move forward in a calculated curved path
- On detecting black line turn left & orient the bot to 90 degree from the start position.
- Move forward and draw on the whiteboard
- Reverse the bot again in a clockwise curve followed by a counter clockwise turn to reach the next black line.
- On detecting black line orient 90 degree and move backwards to reach home

IR Sensors: to detect black line
Ultrasound Sensors: to slow down the bot at a set distance from the whiteboard
Encoders: for odemetry

### 2. Using IR & Ultrasonic
- Navigate in straight lines & make 90 degree turns. 
- Detect black lines using IR 
- Ultrasonic is used to slow down the bot at set distances

### 3. Using only Ultrasonic
- Navigation by only using ultrasonic sensor readings

### 4. Using only IR
- Line follower

