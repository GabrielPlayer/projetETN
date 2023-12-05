
// --- Motors pins ---

# define motor_A_pwm 9    // moteur de droite
# define motor_A_sens 8
# define motor_B_pwm 6    // moteur de gauche
# define motor_B_sens 7

// --- Constants ---

# define pwm_period 1000 // microseconds

// --- Motors variables ---

float pwm_proportion_A;
float pwm_proportion_B;



// ---*---*---*--- ---*---*---*--- Main ---*---*---*--- ---*---*---*---

void setup()
{
    init_motor();
  
    pwm_proportion_A = 0;
    pwm_proportion_B = 1;
 
}

void loop()
{
    gestion_pwm_motor_A();
    gestion_pwm_motor_B();
}

// ---*---*---*--- ---*---*---*--- END Main ---*---*---*--- ---*---*---*---



// --- Motor routines' ---

void init_motor(){
    pinMode(motor_A_pwm, OUTPUT);
    pinMode(motor_A_sens, OUTPUT);
    pinMode(motor_B_pwm, OUTPUT);
    pinMode(motor_B_sens, OUTPUT);
  
    digitalWrite(motor_A_sens, HIGH);
    digitalWrite(motor_B_sens, HIGH);
}

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
  pwm_porportion_B = 0.8;
}
void ajusterVersDroite(){
  pwm_proportion_A = 0.8;
  pwm_porportion_B = 1;
}
void tournerVirageDroite(){
  pwm_proportion_A = 0.5;
  pwm_proportion_B = 1;
  
}
void tournerVirageGauche(){
  pwm_proportion_A = 1;
  pwm_proportion_B = 0.5;
  
}
