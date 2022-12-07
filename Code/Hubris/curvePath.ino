void curve_path() {
  switch(Hubris.getState()){
    case 0:
      Hubris.moveForwardCurveLeft(1.20);
      Hubris.setState(1);
      break;
    case 1:
      if(Hubris.reachedBlackLine()){    // check completed one wheel rotation
        Hubris.orient90ccw();
        Hubris.resetWheelEncoders();
        Hubris.setState(2);
      }
      break;
    case 2:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(3);
      break;
    case 3:
      if (Hubris.getFrontDistance() < 20.0) {
        Hubris.setSpeed(REDUCED_SPEED);
        Hubris.moveForward();
        Hubris.setState(4);
      }
      break;
    case 4:
      if (Hubris.isMarkerSwitchPressed()) {
        Hubris.moveBackwardCurveLeft(3);
        Hubris.setState(5);
      }
      break;
    case 5:
      if (Hubris.orientedAbove90()) {
        Hubris.stop();
      }

      // nothing
      break;
  } 
}