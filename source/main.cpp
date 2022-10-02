#include <simplecpp>
#include<chrono>
#include<sys/time.h>
#include<ctime>
#include "shooter.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
const int RIGHT_MARGIN = WINDOW_Y-LEFT_MARGIN;
//TO prevent multiple Health-- in case of attack on shooter
bool if_colliding_shooter=false;
void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles(int level)
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS*(1<<level)/2, 10*level, -BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS*(1<<level)/2, 10*level, BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    return bubbles;
}

pair<bool,bool> check_collision(Shooter shooter,vector<Bullet>& bullets,vector<Bubble>& bubbles, int& score)
{
    bool ans=0;
    bool ans2=0;
    vector<int> hit_bubbles;
    //check for collisions among objects
    for(int i=0;i<bubbles.size();i++){
        //shooter life

        ans=ans | shooter.check_if_dead(bubbles[i]);
        //for bubbles
        int shot=-1;
        for(int j=0;j<bullets.size();j++){

            if(bullets[j].hits(bubbles[i])){
                shot=j;
                hit_bubbles.push_back(i);
                score+=bubbles[i].get_radius();
                ans2=1;
                break;
            }

        }
        if(shot!=-1)
            bullets.erase(bullets.begin()+shot);
    }
    for(int i=hit_bubbles.size()-1;i>=0;i--){

        if(bubbles[hit_bubbles[i]].get_radius()>BUBBLE_RADIUS_THRESHOLD){
            bubbles.push_back(Bubble(bubbles[hit_bubbles[i]].get_center_x()+bubbles[hit_bubbles[i]].get_radius()/2, bubbles[hit_bubbles[i]].get_center_y(), bubbles[hit_bubbles[i]].get_radius()/2, bubbles[hit_bubbles[i]].get_acc(), abs(bubbles[hit_bubbles[i]].get_vx()), 0, COLOR(255,105,180)));
            bubbles.push_back(Bubble(bubbles[hit_bubbles[i]].get_center_x()-bubbles[hit_bubbles[i]].get_radius()/2, bubbles[hit_bubbles[i]].get_center_y(), bubbles[hit_bubbles[i]].get_radius()/2, bubbles[hit_bubbles[i]].get_acc(), -abs(bubbles[hit_bubbles[i]].get_vx()), 0, COLOR(255,105,180)));
        }
        bubbles.erase(bubbles.begin()+hit_bubbles[i]);
    }
    if(if_colliding_shooter){
        if(ans)
            return {false,ans2};
        if_colliding_shooter=false;
        return {false,ans2};
    }
    if(ans==true)
        if_colliding_shooter=true;
    return {ans,ans2};
}

int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    XEvent event;
    //Remaining Health
    string msg_health="Health: _ / 3";
    Text healthLeft(RIGHT_MARGIN, TOP_MARGIN, msg_health);
    int Health=3;
    msg_health[8]=(char)Health+'0';
    healthLeft.setMessage(msg_health);

    //Timer
    Text TimerHead(LEFT_MARGIN,TOP_MARGIN,"Time:");
    Text Timer(LEFT_MARGIN + textWidth("Time:    ")/2, TOP_MARGIN, 50);

    //Level Indicator
    int Level=1;
    string level_msg="Level: _ / 3";
    Text levelIndicator(WINDOW_X/2,BOTTOM_MARGIN,level_msg);



    //Score Counter
    int Score=0;
    Text scoreHead(RIGHT_MARGIN,BOTTOM_MARGIN,"Score: ");
    Text ScoreBoard(RIGHT_MARGIN+textWidth("Score:    ")/2,BOTTOM_MARGIN,Score);


//Level Building from here
    for(Level=1;Level<=3;Level++){
        if(true){
            Text LevelIntroMsg(WINDOW_X/2,WINDOW_Y/2,"Level: ");
            Text LevelNumberinMsg(WINDOW_X/2+textWidth("Level:  ")/2,WINDOW_Y/2,Level);
            wait(3);
        }
        //Level Message Update:
        level_msg[7]=(char)Level+'0';
        levelIndicator.setMessage(level_msg);
        // Intialize the shooter
        Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);
        // Initialize the bullets (empty)
        vector<Bullet> bullets;
        // Initialize the bubbles
        vector<Bubble> bubbles = create_bubbles(Level);
        //Initialize the timer
        Timer.setMessage("50");
        time_t time_when_game_start;
        time_when_game_start=time(NULL);
        int DisplayTime=50;
        // Main game loop
        while (DisplayTime>=0 && bubbles.size()!=0)
        {
            timeval loop_start_time;
            while(gettimeofday(&loop_start_time,NULL)==-1){}
            if(DisplayTime>50-(loop_start_time.tv_sec-time_when_game_start)){
                DisplayTime--;
                string time_to_display="  ";
                int temp=DisplayTime,index=1;
                while(temp!=0){
                    time_to_display[index]=(char)(temp%10)+'0';
                    temp/=10;
                    index--;
                }
                Timer.setMessage(time_to_display);
            }
            bool pendingEvent = checkEvent(event);
            if (pendingEvent)
            {
                // Get the key pressed
                char c = charFromEvent(event);
                msg_cmd[msg_cmd.length() - 1] = c;
                charPressed.setMessage(msg_cmd);

                // Update the shooter
                if(c == 'a')
                    shooter.move(STEP_TIME, true);
                else if(c == 'd')
                    shooter.move(STEP_TIME, false);
                else if(c == 'w')
                    bullets.push_back(shooter.shoot());
                else if(c == 'q')
                    return 0;
            }

            // Update the bubbles
            move_bubbles(bubbles);

            // Update the bullets
            move_bullets(bullets);
            //Check for Collisions
            pair<bool,bool> coll_result=check_collision(shooter,bullets,bubbles,Score);
            if(coll_result.first){
                Health--;
                msg_health[8]=(char)Health+'0';
                healthLeft.setMessage(msg_health);
                if(Health==0)
                    break;
            }
            if(coll_result.second){
                string score_to_display="   ";
                int temp=Score,index=2;
                while(temp!=0){
                    score_to_display[index]=(char)(temp%10)+'0';
                    temp/=10;
                    index--;
                }
                ScoreBoard.setMessage(score_to_display);
            }
            timeval curr_time;
            while(gettimeofday(&curr_time,NULL)==-1){}
            double time_taken_in_loop=(curr_time.tv_usec-loop_start_time.tv_usec);
            time_taken_in_loop/=1000000;
            if((time_taken_in_loop<=STEP_TIME && time_taken_in_loop>=0)){
                wait(STEP_TIME-time_taken_in_loop);
            }
        }
        if(DisplayTime<=0){
            Text Timer(LEFT_MARGIN + textWidth("Time:    ")/2, TOP_MARGIN,0);
            Text TimeEndLoss(WINDOW_X/2,WINDOW_Y/2,"GAME OVER!!");
            Text Final_gross_score_head(WINDOW_X/2,WINDOW_Y/2+textHeight(),"Total Score:      ");
            Text Final_gross_score_value(WINDOW_X/2+textWidth("Total Score:     ")/2,WINDOW_Y/2+textHeight(),Score);
            wait(3);
            return 0;
        }
        if(Health==0){
            Text LifeEndLoss(WINDOW_X/2,WINDOW_Y/2,"GAME OVER!!");
            Text Final_gross_score_head(WINDOW_X/2,WINDOW_Y/2+textHeight(),"Total Score:      ");
            Text Final_gross_score_value(WINDOW_X/2+textWidth("Total Score:     ")/2,WINDOW_Y/2+textHeight(),Score);
            wait(3);
            return 0;
        }
    }
    //Game Completed
    Text victory_msg(WINDOW_X/2,WINDOW_Y/2,"Congratulations!!!");
    Text Final_gross_score_head(WINDOW_X/2,WINDOW_Y/2+textHeight(),"Total Score:      ");
    Text Final_gross_score_value(WINDOW_X/2+textWidth("Total Score:     ")/2,WINDOW_Y/2+textHeight(),Score);
    wait(3);
    return 0;
}
