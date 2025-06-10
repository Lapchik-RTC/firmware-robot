void Orkestr::calibr()
{
    ///// preKalibr /////
    
    float pKvel = -0.2;
    kalibrON1 = 1;
    kalibrON2 = 1;
    kalibrON3 = 1;
    kalibrON4 = 1;
    kalibrON5 = 1;
    kalibrON6 = 1;
    while(millis() - preKalibrTimer < 1500)
    {
        serv1.setGoalSpeed(pKvel);
        serv2.setGoalSpeed(pKvel);
        serv3.setGoalSpeed(pKvel);
        serv4.setGoalSpeed(pKvel);
        serv5.setGoalSpeed(pKvel);
        serv6.setGoalSpeed(pKvel);
    }
    
    /////////////////////
    float vel = -1.6;
    
    int whaitTimeCalibr = 1500;
    ///  dv1  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_1) < TRIG_CUR_1 && kalibrON1 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv1.setGoalSpeed(vel);
    }
    kalibrON1 = 0;
    serv1.setGoalSpeed(0);

    ///  dv2  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_2) < TRIG_CUR_2 && kalibrON2 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv2.setGoalSpeed(-vel);
    }
    kalibrON2 = 0;
    serv2.setGoalSpeed(0);

    ///  dv3  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_3) < TRIG_CUR_3 && kalibrON3 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv3.setGoalSpeed(-vel);
    }
    kalibrON3 = 0;
    serv3.setGoalSpeed(0);

    ///  dv4  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_4) < TRIG_CUR_4 && kalibrON4 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv4.setGoalSpeed(vel);
    }
    kalibrON4 = 0;
    serv4.setGoalSpeed(0);

    ///  dv5  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_5) < TRIG_CUR_5 && kalibrON5 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv5.setGoalSpeed(vel);
    }
    kalibrON5 = 0;
    serv5.setGoalSpeed(0);

    ///  dv6  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_6) < TRIG_CUR_6 && kalibrON6 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv6.setGoalSpeed(-vel);
    }
    kalibrON6 = 0;
    serv6.setGoalSpeed(0);
    
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();   
}







/////// Main Calibr ///////
void Orkestr::ostCalibr()
{    
    /*uint32_t timeOstCalibr = millis();
    float velOC = -1.0;
    int dir[6] = {1,1,1,1,1,1};
    while (millis() - timeOstCalibr < 3100)
    {       
        if(modc(enc_1.get_phi(), 2.0*M_PI) < M_PI) dir[0] = -1;
        else dir[0] = 1;

        if(modc(enc_2.get_phi(), 2.0*M_PI) < M_PI) dir[1] = -1;
        else dir[1] = 1;

        if(modc(enc_3.get_phi(), 2.0*M_PI) < M_PI) dir[2] = -1;
        else dir[2] = 1;

        if(modc(enc_4.get_phi(), 2.0*M_PI) < M_PI) dir[3] = -1;
        else dir[3] = 1;

        if(modc(enc_5.get_phi(), 2.0*M_PI) < M_PI) dir[4] = -1;
        else dir[4] = 1;

        if(modc(enc_6.get_phi(), 2.0*M_PI) < M_PI) dir[5] = -1;
        else dir[5] = 1;

        serv1.setGoalSpeed(velOC * dir[0]);
        serv2.setGoalSpeed(velOC * dir[1]);
        serv3.setGoalSpeed(velOC * dir[2]);
        serv4.setGoalSpeed(velOC * dir[3]);
        serv5.setGoalSpeed(velOC * dir[4]);
        serv6.setGoalSpeed(velOC * dir[5]);
    }
    velOC = -0.3;
        serv1.setGoalSpeed(velOC * dir[0]);
        serv2.setGoalSpeed(velOC * dir[1]);
        serv3.setGoalSpeed(velOC * dir[2]);
        serv4.setGoalSpeed(velOC * dir[3]);
        serv5.setGoalSpeed(velOC * dir[4]);
        serv6.setGoalSpeed(velOC * dir[5]);*/
    calibr_();
    stendUp();
}
