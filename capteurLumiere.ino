#define LUMIERE_GAUCHE 11
#define LUMIERE_DROITE 12

void setup() {
  Serial.begin(9600);
  pinMode(LUMIERE_GAUCHE, INPUT);
  pinMode(LUMIERE_DROITE, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  detectionLumiere();
  delay(500);
}

void detectionLumiere() {
  bool tourneGauche = digitalRead(LUMIERE_GAUCHE);
  bool tourneDroite = digitalRead(LUMIERE_DROITE);
  if (tourneGauche == false && tourneDroite == false) {
    Serial.println("En Face !!!");
  }
  else if (tourneGauche == true && tourneDroite == false) {
    Serial.println("Tourne a gauche vite !!!");
  }
  else if (tourneGauche == false && tourneDroite == true) {
    Serial.println("Tourne a droite vite !!!");
  }
}
