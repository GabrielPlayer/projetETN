# define read_tl 1
# define read_tr 2

bool last_state_l = false;
bool last_state_r = false;

int picots_l = 0;
int picots_r = 0;

void setup() {
    setup_dist();
}

void loop() {
  
    update_dist();

}

void setup_dist() {
    pinMode(read_tl, INPUT);
    pinMode(read_tr, INPUT); 
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
