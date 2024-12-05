const int frontLEDPin = 4;//variable to hold the arduino pin that each LED is getting power from
const int rightLEDPin = 3;
const int backLEDPin = 2;
const int leftLEDPin = 5;

const int frontMicPin = A4;
const int rightMicPin = A3;
const int backMicPin = A2;
const int leftMicPin = A5;

void setup()
{
  //make sure each pin is doing what we want
  Serial.begin(9600);

  pinMode(frontLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);
  pinMode(backLEDPin, OUTPUT);
  pinMode(leftLEDPin, OUTPUT);

  pinMode(frontMicPin, INPUT);
  pinMode(rightMicPin, INPUT);
  pinMode(backMicPin, INPUT);
  pinMode(leftMicPin, INPUT);
}



void bigMethod()//does all calculations, tracks the noises, decides which ones are relevant, and lights up the right LED
{
  //values to track max and min noise recorded by each mic over a time interval
  int fmn = 1024;
  int fmx = 0;
  int rmn = 1024;
  int rmx = 0;
  int bmn = 1024;
  int bmx = 0;
  int lmn = 1024;
  int lmx = 0;

  for (int i = 0; i < 1000; i++)//constabntly runs, checking for new maximum and minimum values coming from the mics
  {
    int fval = analogRead(frontMicPin);
    fmn = min(fval, fmn);
    fmx = max(fval, fmx);

    int rval = analogRead(rightMicPin);
    rmn = min(rval, rmn);
    rmx = max(rval, rmx);

    int bval = analogRead(backMicPin);
    bmn = min(bval, bmn);
    bmx = max(bval, bmx);

    int lval = analogRead(leftMicPin);
    lmn = min(lval, lmn);
    lmx = max(lval, lmx);
  }
  int fdelta = fmx - fmn;
  int rdelta = rmx - rmn;
  int bdelta = bmx - bmn;
  int ldelta = lmx - lmn;

//prints for testing/close analysis
  Serial.print("Front Max: ");  Serial.println(fmx);  //Serial.print(" Front Min: ");  Serial.print(fmn);  Serial.print(" Front Delta: "); Serial.println(fdelta);
  Serial.print("Right Max: "); Serial.println(rmx); //Serial.print(" Right Min: ");  Serial.print(rmn);  Serial.print(" Right Delta: "); Serial.println(rdelta);
  Serial.print("Back Max: "); Serial.println(bmx); //Serial.print(" Back Min: "); Serial.print(bmn);  Serial.print(" Back Delta: ");  Serial.println(bdelta);
  Serial.print("Left Max: ");  Serial.println(lmx); //Serial.print(" Left Min: "); Serial.print(lmn);  Serial.print(" Left Delta: "); Serial.println(ldelta);


  double avgDelta = (fdelta + rdelta + bdelta + ldelta) / 4.0;

//calculates average max value from each mic and decides if one or more mics is significantly higher than others, if so activates that LED
  double avgMx = (fmx+rmx+bmx+lmx)/4.0;
  Serial.print("Average Max: "); Serial.println(avgMx);

    digitalWrite(frontLEDPin, LOW);
    digitalWrite(rightLEDPin, LOW);
    digitalWrite(backLEDPin, LOW);
    digitalWrite(leftLEDPin, LOW);

  if (fmx > avgMx * 1.1)
  {
    digitalWrite(frontLEDPin, HIGH);
    Serial.println("FRONT LED ON");
  }

    if (rmx > avgMx * 1.1)
    {
      digitalWrite(rightLEDPin, HIGH);
      Serial.println("RIGHT LED ON");
    }

    if (bmx > avgMx * 1.1)
    {
      digitalWrite(backLEDPin, HIGH);
      Serial.println("BACK LED ON");
    }

    if (lmx > avgMx * 1.1)
    {
      digitalWrite(leftLEDPin, HIGH);
      Serial.println("LEFT LED ON");
    }
  
}
  
  void loop()
  {
    bigMethod();
    //digitalWrite(5, HIGH);
    
  }
