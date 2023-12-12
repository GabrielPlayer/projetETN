
// --- Motors pins ---
#define motor_A_pwm 9 // moteur de droite
#define motor_A_sens 8
#define motor_B_pwm 6 // moteur de gauche
#define motor_B_sens 7

#define read_tl 1
#define read_tr 11

// --- Capteurs pins ---
#define LUMIERE_GAUCHE 12
#define LUMIERE_DROITE 13
#define MUR_GAUCHE 10
#define MUR_DROITE 5
#define MUR_FACE 4
#define PORTE_GAUCHE 3
#define PORTE_DROITE 2

// --- Constants ---
#define pwm_period 1000 // microseconds

// --- Motors variables ---
float pwm_proportion_A = 0;
float pwm_proportion_B = 0;
bool last_state_l = false;
bool last_state_r = false;
int picots_l = 0;
int picots_r = 0;

// --- Capteurs variables ---
bool etpDirLumiere = true; //  Rotation sur place pour trouver la lumiere pour avancer
bool etpPasserPorte = false; // Avance jusqu a la porte en restant droit
bool etpVirageDroiteEntree = false; //  Rotation a droite pour etre dans le couloir
bool etpPorteGauche = false; // Avance jusqu au passage en restant droit  
bool etpVirageGauche = false; // Rotation a gauche pour venir dans le virage 
bool etpPorteDroite = false; // Avance jusqu au passage en restant droit  
bool etpVirageDroiteSortie = false; // Rotation a droite pour sortir
bool etpFinirCourse = false; // Avance tout droit

// --- Timing Etape ---
int timingEtp2 = 15000;
int timingEtp3 = 15000;
int timingEtp4 = 15000;
int timingEtp5 = 15000;
int timingEtp6 = 15000;
int timingEtp7 = 15000;

// --- Debut Etape ---
int etape2 = 0;
int etape3 = 0;
int etape4 = 0;
int etape5 = 0;
int etape6 = 0;
int etape7 = 0;

void setup() {
  Serial.begin(9600);
  // --- Motors pins ---
  pinMode(motor_A_pwm, OUTPUT);
  pinMode(motor_A_sens, OUTPUT);
  pinMode(motor_B_pwm, OUTPUT);
  pinMode(motor_B_sens, OUTPUT);
  // --- Dist pins ---  
  pinMode(read_tl, INPUT);
  pinMode(read_tr, INPUT);
  // --- Capteurs pins ---
  pinMode(LUMIERE_GAUCHE, INPUT);
  pinMode(LUMIERE_DROITE, INPUT);
  pinMode(MUR_GAUCHE, INPUT);
  pinMode(MUR_DROITE, INPUT);
  pinMode(MUR_FACE, INPUT);  
  // --- Motors pins out ---
  digitalWrite(motor_A_sens, HIGH);
  digitalWrite(motor_B_sens, HIGH);
}

void loop() {
  bool res;
  
  if (etpDirLumiere){ // Rotation
    res = detectionLumiereLateral();
    if (res){
      etpDirLumiere = false;
      etpPasserPorte = true;
      etape1 = millis();
    }
    
  } else if (etpPasserPorte){ // Avance
    detectionLumiereFace();
    if (millis()-etape2>=timingEtp2){
      etpPasserPorte = false;
      etpVirageDroiteEntree = true;
      etape3 = millis();
    }
    
  } else if (etpVirageDroiteEntree){ // Virage
    tournerVirageDroite();
    if (millis()-etape3>=timingEtp3){
      etpVirageDroiteEntree = false;
      etpPorteGauche = true;
      etape4 = millis();
    }
    
  } else if (etpPorteGauche){ // Avance
    detectionMurLateral();
    if (millis()-etape4>=timingEtp4){
      etpPorteGauche = false;
      etpVirageGauche = true;
      etape5 = millis();
    }

  } else if (etpVirageGauche){ // Virage
    tournerVirageGauche();
    if (millis()-etape5>=timingEtp5){
      etpVirageGauche = false;
      etpPorteDroite = true;
      etape6 = millis();
    }
    
  } else if (etpPorteDroite){ // Avance
    detectionMurLateral();
    if (millis()-etape6>=timingEtp6){
      etpPorteDroite = false;
      etpVirageDroiteSortie = true;
      etape7 = millis();
    }
    
  } else if (etpVirageDroiteSortie){ // Virage
    tournerVirageDroite();
    if (millis()-etape7>=timingEtp7){
      etpVirageDroiteSortie = false;
      etpFinirCourse = true;
    }
    
  } else if (etpFinirCourse){ // Avance
    avancer();
  }
  gestion_pwm_motor_A();
  gestion_pwm_motor_B();
}

// ----- Gestion du Moteur ----- 
void gestion_pwm_motor_A(){
    if (micros()%pwm_period < pwm_proportion_A * pwm_period){
        digitalWrite(motor_A_pwm, HIGH);
    } else {
        digitalWrite(motor_A_pwm, LOW);
    }
}

void gestion_pwm_motor_B(){
    if (micros()%pwm_period < pwm_proportion_B * pwm_period){
        digitalWrite(motor_B_pwm, HIGH);
    } else {
        digitalWrite(motor_B_pwm, LOW);
    }
}

bool finVirageDroite90(){
  if ( picots_l >= 151){    
    return true;
  }
  return false;
}

bool finVirageGauche180(){
  if ( picots_r >= 151*2){
    return true;
  }
  return false;
}

void avancer(){
  pwm_proportion_A = 1;
  pwm_proportion_B = 1;
}

void tournerDroiteSurPlace(){
  pwm_proportion_A = 0;
  pwm_proportion_B = 1;
}

void tournerGaucheSurPlace(){
  pwm_proportion_A = 1;
  pwm_proportion_B = 0;
}

void ajusterVersGauche(){
  pwm_proportion_A = 1;
  pwm_proportion_B = 0.8;
}

void ajusterVersDroite(){
  pwm_proportion_A = 0.8;
  pwm_proportion_B = 1;
}

void tournerVirageDroite(){  
  pwm_proportion_A = 0.28;
  pwm_proportion_B = 1;  
}

void tournerVirageGauche(){
  pwm_proportion_A = 1;
  pwm_proportion_B = 0.28;
  
}

void update_dist() {
    if(digitalRead(read_tl) != last_state_l) {
        picots_l++;
        last_state_l = !last_state_l ;
    }
    if(digitalRead(read_tr) != last_state_r) {
        picots_r++;
        last_state_r = !last_state_r;
    }
}

void reset_dist() {  
    picots_l = 0;    
    picots_r = 0;
}
// ----- ----- ----- ----- -----

// ----- Gestion des Capteurs ----- 
void detectionLumiereFace(){  
  bool tourneGauche = digitalRead(LUMIERE_GAUCHE);
  bool tourneDroite = digitalRead(LUMIERE_DROITE);
  if (tourneGauche == false && tourneDroite == false) {
    avancer();
  }
  else if (tourneGauche == true && tourneDroite == false) {
    ajusterVersGauche();
  }
  else if (tourneGauche == false && tourneDroite == true) {
    ajusterVersDroite();
  }
}

bool detectionLumiereLateral(){  
  bool tourneGauche = digitalRead(LUMIERE_GAUCHE);
  bool tourneDroite = digitalRead(LUMIERE_DROITE);
  if (tourneGauche == false && tourneDroite == false) {
    return true;
  }
  else if (tourneGauche == true && tourneDroite == false) {
    tournerGaucheSurPlace();
    return false;
  }
  else if (tourneGauche == false && tourneDroite == true) {
    tournerDroiteSurPlace();
    return false;
  }
}

bool detectionMurFace(){  
  bool murFace = digitalRead(MUR_FACE);
  if (murFace == true) {
    return true;
  }
  return false;
}

void detectionMurLateral(){
  bool murGauche = digitalRead(MUR_GAUCHE);
  bool murDroite = digitalRead(MUR_DROITE);
  if (murGauche == true && murDroite == false) {
    avancer();
  }
  else if (murGauche == true && murDroite == true) {
     ajusterVersGauche();
  }
  else if (murGauche == false && murDroite == false) {
     ajusterVersDroite();
  }  
}

bool detectionPorteGauche(){
  bool murGauche = digitalRead(PORTE_GAUCHE);
  if (murGauche == true) {
    return true;
  }
  return false;  
}

bool detectionPorteDroite(){
  bool murDroite = digitalRead(PORTE_DROITE);
  if (murDroite == true) {
    return true;
  }
  return false;  
}
// ----- ----- ----- ----- ----- -----