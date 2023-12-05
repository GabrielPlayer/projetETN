#define LUMIERE_GAUCHE 7
#define LUMIERE_DROITE 8
#define MUR_GAUCHE 9
#define MUR_DROITE 10
#define MUR_FACE 11
#define PORTE_GAUCHE 12
#define PORTE_DROITE 13

void setup() {
  Serial.begin(9600);
  pinMode(LUMIERE_GAUCHE, INPUT);
  pinMode(LUMIERE_DROITE, INPUT);
  pinMode(MUR_GAUCHE, INPUT);
  pinMode(MUR_DROITE, INPUT);
  pinMode(MUR_FACE, INPUT);
  
}

void loop() {
  //detectionLumiere();
  //detectionMurFace();
  //detectionPorteGauche();
  detectionMurLateral();
  delay(500);
}

bool detectionLumiereLateral() {
  bool tourneGauche = digitalRead(LUMIERE_GAUCHE);
  bool tourneDroite = digitalRead(LUMIERE_DROITE);
  if (tourneGauche == false && tourneDroite == false) {
    Serial.println("En Face !!!");
    return true;
  }
  else if (tourneGauche == true && tourneDroite == false) {
    Serial.println("Tourne a gauche vite !!!");
    return false;
  }
  else if (tourneGauche == false && tourneDroite == true) {
    Serial.println("Tourne a droite vite !!!");
    return false;
  }
}

void detectionLumiereFace() {
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

bool detectionMurFace() {
  bool murFace = digitalRead(MUR_FACE);
  if (murFace == true) {
    Serial.println("Mur en face !!!");
    return true;
  }
  return false;
}

void detectionMurLateral() {
  bool murGauche = digitalRead(MUR_GAUCHE);
  bool murDroite = digitalRead(MUR_FACE);
  if (murGauche == false && murDroite == false) {
    Serial.println("En Face !!!");
  }
  else if (murGauche == true && murDroite == false) {
    Serial.println("Tourne a gauche vite !!!");
  }
  else if (murGauche == false && murDroite == true) {
    Serial.println("Tourne a droite vite !!!");
  }
}

bool detectionPorteGauche() {
  bool murGauche = !digitalRead(PORTE_GAUCHE);
  if (murGauche == true) {
    Serial.println("Porte a gauche !!!");
    return true;
  }
  return false;
}

bool detectionPorteDroite() {
  bool murDroite = !digitalRead(PORTE_DROITE);
  if (murDroite == true) {
    Serial.println("Porte a droite !!!");
    return true;
  }
  return false;
}
