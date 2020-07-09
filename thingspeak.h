#ifndef thingspeak_h

  #define thingspeak_h

  void thingsSpeakGsmSetup();
  void thingsSpeakSetPrivateSendKey(String privateKey_in);
  void thingsSpeakSend(float* parFields_in,  unsigned char noOfParameters_in);


#endif
