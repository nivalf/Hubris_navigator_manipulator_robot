void operate() {
  switch (Hubris.getState()) {
      //   case 0:  // calibration
      //     break;
    case 1:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(2);
      break;
    case 2:  // reduce speed
      if (Hubris.blackLineInProximity()) {
        Hubris.setSpeed(reducedSpeed);
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
      if (Hubris.buttonPressed()) {
        Hubris.setState(1);
      }
      // else if (Hubris.reachedBlackLine()) {
      //   Hubris.setState(5);
      // }
      break;
    case 5:
      Hubris.stop();
      break;
  }
}