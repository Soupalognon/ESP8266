//Code de Durand Gabriel 
//Dernières modif le :20/12/2015



void setup()
{
  Serial.begin(9600);

  Serial.println("Init Terminee");
}

void loop()
{
  if(Serial.available())
  {
    long temps = millis();
    String temp = "";
    while(millis() - temps < 10);
    {
      while(Serial.available())
      {
      char carac = Serial.read();
      temp += carac;
      }
    }
    Serial.print(temp);
    Serial.print("#");
  }
}

