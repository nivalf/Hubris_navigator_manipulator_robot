void curve_path() {
  switch (Hubris.getState()) {
    case 0:
      // circle radius : 77
      Hubris.moveForwardCurveLeft(1.20);
      Hubris.setState(1);
      break;
    case 1:
      if (Hubris.completedOneWheelRotation() && Hubris.reachedBlackLine()) {
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
        // circle radius: 20
        Hubris.setTurnSpeed(10);
        Hubris.moveBackwardCurveLeft(8);
        Hubris.setState(5);
      }
      break;
    case 5:
      if (Hubris.orientedAbove90()) {
        Hubris.resetWheelEncoders();
        Hubris.setSpeed(50);
        Hubris.moveBackward();
        Hubris.setState(6);
      }
      break;
    case 6:
      if (Hubris.completedWheelRotation(1.4)) {
        Hubris.resetWheelEncoders();
        Hubris.setTurnSpeed(30);
        Hubris.moveBackwardCurveRight(1.8);
        Hubris.setState(7);
      }
    case 7:
      if (Hubris.reachedBlackLine()) {
        Hubris.orient90cw();
        Hubris.resetWheelEncoders();
        Hubris.setState(8);
      }
      break;
    case 8:  // go forward
      Hubris.setSpeed(50);
      Hubris.moveBackward();
      Hubris.setState(9);
      break;
    case 9:
      if (Hubris.completedWheelRotation(2.35)) {
        Hubris.stop();
      }
      break;
  }
}