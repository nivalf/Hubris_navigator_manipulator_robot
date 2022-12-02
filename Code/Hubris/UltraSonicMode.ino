void ultraSonicMode() {
  switch (Hubris.getState()) {
    case 0:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(1);
      break;
    case 1:  // reduce speed
      if (Hubris.getFrontDistance() < 35.0) {
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(2);
      }
      break;
    case 2:  // turn left
      if (Hubris.getFrontDistance() < 13.0) {
        Hubris.turnLeft();
        Hubris.setState(3);
      }
      break;
    case 3:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(5);
      break;
    case 4:
      if (Hubris.getFrontDistance() < 20.0) {
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(5);
      }
      break;
    case 5:
      if (Hubris.getFrontDistance() < 6.0) {
        Hubris.moveBackward();
        Hubris.setState(6);
      }
      break;
    case 6:
      if (Hubris.getFrontDistance() > 20.0) {
        Hubris.turnLeft();
        Hubris.setState(0);
      }
  }
}