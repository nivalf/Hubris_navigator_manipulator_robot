void operate() {
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
        Hubris.setSpeed(reducedSpeed);
        Hubris.moveForward();
        Hubris.setState(3);
      }
      break;
    case 3:  // turn left
      if (Hubris.reachedBlackLine()) {
        Hubris.turn90Left();
        Hubris.setState(4);
        Hubris.setSpeed(lineFollowSpeed);
      }
      break;
    case 4:  // follow line
      Hubris.followLine();
      if (Hubris.getFrontDistance() < 6.0) {  // marker pressed
        Hubris.reOrient();
        Hubris.moveBackward();
        Hubris.setState(5);
      }
      break;
    case 5:
      if (Hubris.getFrontDistance() > 13.0) {
        Hubris.turn90Left();
        Hubris.setState(0);
      }
      break;
    // case 6:
    //   Hubris.stop();
    //   break;
  }
}