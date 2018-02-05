void playTwinkle_servo(int k){
  int p=7*k; //I've figured out that it takes about 7ms for the servo to rotate 1 degree.
  for (int j=0; j<2; j++) { //j = how many times to play this 7 beats
    for(int i=0;i<7;i++) // the constants below are obtained by trials and errors
  {   
    servo1.write(90+k);   
    delay(300-p);         
    servo1.write(70);  
    delay(300-p);   
  }
  delay(900-p);
  }
}
