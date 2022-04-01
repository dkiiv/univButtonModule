# univACC button module
# this example code was taken from carstate. you can insert it anywhere or even move most of this logic to the buttonModuleFW itself!
    if bool(pt_cp.vl["univACC"]['heartBeat']):
      ret.univACCenabled = False
      self.univACCtempdisable = False
      self.univACCspeed = 0
        # Only allow OP to enable if car is in D, S, manual, or tiptronic modes. THIS WILL BE CAR DEPENDANT!! EDIT FOR YOUR OWN PARSING LOGIC
      if pt_cp.vl["Getriebe_1"]['Waehlhebelposition__Getriebe_1_'] in [5, 9, 12, 14, 10, 11]:
        ret.cruiseState.available = True
      else:
        ret.cruiseState.available = False
        ret.cruiseState.enabled = False
        ret.univACCenabled = False
        # Toggle LKAS on, Toggle LKAS and ACC off
      if pt_cp.vl["univACC"]['buttonState'] in [1]:
        if not ret.cruiseState.enabled:
          ret.cruiseState.enabled = True
        else:
          ret.cruiseState.enabled = False
          ret.univACCenabled = False
        # Toggle ACC on/off
      if pt_cp.vl["univACC"]['buttonState'] in [2]:
        if not ret.univACCenabled:
          if self.univACCspeed == 0:
            self.univACCspeed = 5 * round(ret.vEgo/5)
          if ret.cruiseState.available:
            ret.univACCenabled = True
        else:
          ret.univACCenabled = False
        # Decrease set speed by 5
      if pt_cp.vl["univACC"]['buttonState'] in [3]:
        self.univACCspeed -= 5
        if self.univACCspeed < 0:  # Not allow set speed to breach < 0 mph
          self.univACCspeed = 0
        # Increase set speed by 5
      if pt_cp.vl["univACC"]['buttonState'] in [4]:
        self.univACCspeed += 5
        # Gas or Brake press = ACC disable, re-enable after brake release if under 15mph
      if ret.gasPressed or ret.brakePressed:
        if ret.vEgo < 15 * CV.MS_TO_MPH:
          self.univACCtempdisable = True
        ret.univACCenabled = False
      if self.univACCtempdisable and not (ret.gasPressed or ret.brakePressed):
        ret.univACCenabled = True
        self.univACCtempdisable = False
        # Link univACCspeed to cruiseState.speed
      ret.cruiseState.speed = self.univACCspeed * CV.KPH_TO_MS
      # Stock OP function if univACC button module is not present
    else:
        # Put your car's stock OP engagement controls here