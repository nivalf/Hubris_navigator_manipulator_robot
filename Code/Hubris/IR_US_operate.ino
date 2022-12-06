void IR_US_operate() {
  switch (Hubris.getState()) {
    case 0:  // calibration
      Hubris.setState(1);
      break;
    case 1:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(2);
      break;
    case 2:  // reduce speed
      if (Hubris.blackLineInProximity()) {
        Hubris.reOrient();
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(3);
      }
      break;
    case 3:  // turn left
      if (Hubris.reachedBlackLine()) {
        Hubris.reOrient();
        Hubris.turn90Left();
        Hubris.setState(4);
      }
      break;
    case 4:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(5);
      break;
    case 5:
      if (Hubris.getFrontDistance() < 20.0) {
        // Hubris.reOrient();
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(6);
      }
      break;
    case 6:
      if (Hubris.isMarkerSwitchPressed()) {
        // Hubris.reOrient();
        Hubris.moveBackward();
        Hubris.setState(7);
      }
      break;
    case 7:
      if (Hubris.getFrontDistance() > 13.0) {
        // Hubris.reOrient();
        Hubris.turn90Left();
        Hubris.setState(8);
      }
      break;
    case 8:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(9);
      break;
    case 9:  // reduce speed
      if (Hubris.blackLineInProximity()) {
        // Hubris.reOrient();
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(10);
      }
      break;
    case 10:  // turn left
      if (Hubris.reachedBlackLine()) {
        // Hubris.reOrient();
        Hubris.turn90Left();
        Hubris.setState(11);
      }
      break;
    case 11:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(12);
      break;
    case 12:
      if (Hubris.getFrontDistance() < 20.0) {
        // Hubris.reOrient();
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(13);
      }
      break;
    case 13:
      if (Hubris.getFrontDistance() < 6.0) {
        Hubris.stop();
      }
      break;
  }
}