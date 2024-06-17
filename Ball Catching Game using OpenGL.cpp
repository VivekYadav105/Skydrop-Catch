#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;


float BALL_RADIUS = 0.08f;
float BASKET_HEIGHT = 0.1f;
float BASKET_WIDTH = 0.3f;
float BASKET_SPEED = 0.02f;
float WINDOW_WIDTH = 640;
float WINDOW_HEIGHT = 480;
float ball_speed = 0.02f;
int page = 0;
float bx = 0.0;
int high_score = 0;
float dx = 0.01;
float ball_x = 0.0f;
float ball_y = 1.0f;
float basket_x = 0.0f;
int score = 0;
int miss = 0;
bool game_over = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool pause = true;
const char* message = "Game Over!"; // the message to display

void changeSpeed();
void resetGame();
void highScore();


void drawBall(GLfloat x, GLfloat y) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        GLfloat radian = i * M_PI / 180.0f;
        glVertex2f(x + BALL_RADIUS * cos(radian), y + BALL_RADIUS * sin(radian));
    }
    glEnd();

}

void drawBasket(GLfloat x) {
    glColor3f(0.52f, 0.37f, 0.26f);
    glBegin(GL_QUADS);
    glVertex2f(basket_x - BASKET_WIDTH / 2, -0.9f);
    glVertex2f(basket_x - 0.1f + BASKET_WIDTH / 2, -0.9f);
    glVertex2f(basket_x + BASKET_WIDTH / 2, -0.9 + BASKET_HEIGHT);
    glVertex2f(basket_x - 0.1f - BASKET_WIDTH / 2, -0.9 + BASKET_HEIGHT);
    glEnd();
}

void drawScore(GLint score) {
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.9f, 0.9f);
    char str[20];

    sprintf(str, "Score: %d", score);
    for (int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

void drawMoon(){
    glColor3f(1.0f, 1.0f, 1.0f); // set color to white

    // draw moon using filled circle
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(cos(degInRad) * 0.2 + 0.5, sin(degInRad) * 0.2 + 0.5);
    }
    glEnd();

    glFlush();
}

void gameOver(){
    // set color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    // set position
    glRasterPos2f(-0.2f, 0.0f);

    // draw the message one character at a time
    int len = strlen(message);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glFlush();
}

void highScore(){
    std::ifstream file("highScore.txt"); // Open the file for reading
    string line;
    file>>line;
    file>>high_score;
    file.close();
    cout<<line<<" "<<high_score<<endl;
}

void pauseGame(){
    // set color to red
    glColor3f(1.0f, 1.0f, 0.0f);

    // set position
    glRasterPos2f(-0.2f, 0.0f);

    // draw the message one character at a time
    char* message = "GAME PAUSED!!!";
    int len = strlen(message);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glFlush();

}

void drawMissing(GLint miss){
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(0.7f, 0.9f);
    char str[20];
    sprintf(str, "Miss: %d", miss);
    for (int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

void updateBasket() {
    if (leftKeyPressed) {
        basket_x -= BASKET_SPEED; // Move paddle left
        if (basket_x - 0.1f - BASKET_WIDTH/2 < -1.0f) {
            basket_x = -0.9f + BASKET_WIDTH/2; // Clamp paddle to left edge of screen
        }
    }
    if (rightKeyPressed) {
        basket_x += BASKET_SPEED; // Move paddle right
    if (basket_x + BASKET_WIDTH/2 > 1.0f) {
            basket_x = 1.0f - BASKET_WIDTH/2; // Clamp paddle to right edge of screen
        }
    }
}

void changeSpeed(){
     if (score >= 10 && score<=30){
            cout<<"increased speed"<<ball_speed<<endl;
            ball_speed = 0.03f;
            BASKET_SPEED = 0.035f;
    }
    else if (score >= 30 && score<=40){
        ball_speed = 0.04f;
        BASKET_SPEED = 0.048f;
    }
    else if(score>=40){
        ball_speed = 0.05f;
        BASKET_SPEED = 0.06f;
    }
}

void resetGame(){
    ball_speed = 0.02f;
     page = 0;
    bx = 0.0;
    dx = 0.01;
    ball_x = 0.0f;
    ball_y = 1.0f;
    basket_x = 0.0f;
    score = 0;
    miss = 0;
    game_over = false;
    leftKeyPressed = false;
    rightKeyPressed = false;
    pause = true;
}

void home(){
    glClearColor(0.4,0.6,1.0,0.3);
    drawBall(bx,0.34);

    glColor3f(1.0,1.0,1.0);
    glRasterPos2f(-0.5f, 0.5f);
    char *title = "Ball catching game in OPENGL";
    int j = strlen(title);
    glPixelZoom(2.0f,2.0f);

    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    glColor4f(0.0,0.3,0.2,1.0);
    char *option1 = "Instructions";
    glRasterPos2f(-0.7f, -0.7f);
    j = strlen(option1);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, option1[i]);
    }
    char *option2 = "Team";
    glRasterPos2f(-0.0f, -0.7f);
    j = strlen(option2);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, option2[i]);
    }
    glColor4f(0.5,0.9,0.2,1.0);
    char *start = "START";
    glRasterPos2f(-0.1f, 0.0f);
    j = strlen(start);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
    }
    glColor4f(0.0,0.3,0.2,1.0);
    char *option3 = "Exit";
    glRasterPos2f(0.4f, -0.7f);
    j = strlen(option3);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, option3[i]);
    }

    glFlush();
}


void game(){
    glBegin(GL_QUADS);//Sky
    glVertex2f(-1.0f,-0.85f);
    glVertex2f(1.0f, -0.85f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    drawMoon();
    glColor3f(0.196f, 0.196f, 0.8f);
    glBegin(GL_QUADS);// Sea
    glVertex2f(-1.0f,-1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.85f);
    glVertex2f(-1.0f, -0.85f);
    glEnd();

    drawBall(ball_x, ball_y);
    drawBasket(basket_x);
    drawScore(score);
    drawMissing(miss);


    if(game_over == true){
        gameOver();
    }
    if(pause && !game_over) pauseGame();

}


void team()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // draw game graphics here

    // set color to white
    glColor3f(1.0f, 1.0f, 1.0f);
    // draw team member names
    glPixelZoom(2.0f,2.0f);
    glRasterPos2f(-0.7f, 0.5f);

    char names[32] = "Team Members:";
    int j = strlen(names);
    for (int i = 0; i <32; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, names[i]);
    }
    glFlush();
    glColor4f(0.5,0.9,0.2,1.0);
    glPixelZoom(1.0f,1.0f);
    char *name1 = "Ankathi Vivek(20bcs016)";
    j = strlen(name1);
    glRasterPos2f(-0.45f, 0.38f);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name1[i]);
    }
    char *name2 = "Nirmal Swaroop(20bcs068)";
    glRasterPos2f(-0.45f, 0.26f);
    j = strlen(name2);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name2[i]);
    }
    char *name3 = "M. Rajesh Naidu (20bcs079)";
    j = strlen(name3);
    glRasterPos2f(-0.45f, 0.14f);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name3[i]);
    }
    char *name4 = "P.Vivek Yadav (20bcs105)";
    j = strlen(name4);
    glRasterPos2f(-0.45f, 0.02f);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name4[i]);
    }
    // draw game over message and other UI elements

    char *name5 = "<- Go back";
    j = strlen(name5);
    glColor3f(0.2,0.3,0.4);
    glRasterPos2f(0.45f, -0.24f);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name5[i]);
    }

    // swap the buffers to display the scene
    glFlush();
}


void instuctions(){
    char *heading = "INSTRUCTIONS";
    glRasterPos2f(-0.2f, 0.9f);
    int j = strlen(heading);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading[i]);
    }

    char *instruction1 = "GAME CONTORLS";
    glRasterPos2f(-0.9f, 0.7f);
    j = strlen(instruction1);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instruction1[i]);
    }
    char *instruction2 = "ESC -- Exit the game";
    glRasterPos2f(-0.9f, 0.55f);
    j = strlen(instruction2);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, instruction2[i]);
    }
    char *instruction3 = "A -- Move the boat to the left";
    glRasterPos2f(-0.9f, 0.45f);
    j = strlen(instruction3);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, instruction3[i]);
    }
    char *instruction4 = "D -- Move the boat to the right";
    glRasterPos2f(-0.9f, 0.35f);
    j = strlen(instruction4);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, instruction4[i]);
    }
     char *pauseInstruction = "SPACEBAR -- Pause the game";
    glRasterPos2f(-0.9f, 0.25f);
    j = strlen(pauseInstruction);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pauseInstruction[i]);
    }
     char *resetInstruction = "R -- Return to home";
    glRasterPos2f(-0.9f, 0.15f);
    j = strlen(resetInstruction);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, resetInstruction[i]);
    }
    glColor4f(1.0,0.0,0.0,1.0);
    char *instruction5 = "If you miss 3 balls it is game over for you";
    glRasterPos2f(-0.65f, -0.2f);
    j = strlen(instruction5);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction5[i]);
    }
    glColor4f(0.0,0.0,1.0,1.0);
    char *instruction6 = "TRY TO CATCH AS MANY BALLS AS YOU CAN";
    glRasterPos2f(-0.95f, -0.45f);
    j = strlen(instruction6);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instruction6[i]);
    }

    char *instruction7 = "ALL THE BEST";
    glRasterPos2f(-0.95f, -0.55f);
    j = strlen(instruction7);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instruction7[i]);
    }

    char *option = "<- Go back";
    glRasterPos2f(0.4f, -0.9f);
    j = strlen(option);
    for (int i = 0; i <j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, option[i]);
    }

    glFlush();
}


void update() {

    if(pause==false){
        BASKET_SPEED = 0.025f;
        ball_speed = 0.02f;
        changeSpeed();
        if (!game_over) {
            ball_y -= ball_speed;
        if (ball_y < -1.0f) {
            ball_x = (GLfloat)rand() / RAND_MAX * 2 - 1;
            ball_y = 1.0f;
            score--;
            miss++;
        }
        if (ball_y < -1.0f + BASKET_HEIGHT + BALL_RADIUS &&
            ball_x > basket_x - 0.1f - BASKET_WIDTH / 2 &&
            ball_x < basket_x + BASKET_WIDTH / 2) {
            ball_x = (GLfloat)rand() / RAND_MAX * 2 - 1;
            ball_y = 1.0f;
            score++;
        }
    }
        if (miss >= 3){
            game_over = true;
            BASKET_SPEED = 0;
        }
    }
    else{

        ball_speed = 0;
        BASKET_SPEED = 0;
    }


}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    if(page==0){
        home();
    }
    else if (page==1){
        instuctions();
    }
    else if(page==2){
        team();
    }
    else if (page==3){
        game();
    }
    glutSwapBuffers();
}


void keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Left arrow keya
            leftKeyPressed = true;
        break;
        case 'd': // Right arrow key
            rightKeyPressed = true;
        break;
        case 27: // Escape key
            exit(0);
        break;
        case GLUT_KEY_RIGHT:
            rightKeyPressed = true;
        default:
            break;
    }
}


void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Left arrow key
            leftKeyPressed = false;
            break;
        case ' ':
            if(pause) pause = false;
            else pause = true;

            break;
        case 'd': // Right arrow key
            rightKeyPressed = false;
            break;
        case 'r':
            resetGame();
            break;
        default:
            break;
}
}


void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float ndcX = (float)(2 * x) / WINDOW_WIDTH - 1.0f;
        float ndcY = -((float)(2 * y) / WINDOW_HEIGHT - 1.0f);
        std::cout << "Left button clicked at (" << ndcX << ", " << ndcY << ")" << std::endl;
        switch(page){
            case 0:
                if(ndcX>=-0.7f && ndcX<=-0.3f && ndcY<=-0.62f && ndcY>=-0.69f) page = 1;
                if(ndcX>=0.005f && ndcX<=0.185f && ndcY<=-0.63f && ndcY>=-0.7f) page = 2;
                if(ndcX>=0.4f && ndcX<=0.53f && ndcY<=-0.62f && ndcY>=-0.68f) exit(0);
                if(ndcX>=-0.09f && ndcX<=0.14f && ndcY<=0.07f && ndcY>=0.00f){
                        pause = false;
                        page = 3;
                }
                break;
            case 1:
                if(ndcX>=0.4f && ndcX<=0.75f && ndcY<=-0.82f && ndcY>=-0.9f) page = 0;
                break;
            case 2:
                if(ndcX>=0.45f && ndcX<=0.8f && ndcY<=-0.16f && ndcY>=-0.25f) page = 0;
                break;
        }
    }
}

void timer(int) {
    if(page==3) {
        update();
        updateBasket();
    }
    else if(page==0){
        if(bx>=0.5){
            dx=-0.01;
        }
        if(bx<=-0.5){
            dx = 0.01;
        }
        bx = bx+dx;
    }
    // Update paddle position based on input
glutPostRedisplay(); // Mark window for redisplay
glutTimerFunc(16, timer, 0); // Call timer function again after 16ms


}

void reshape(int w,int h){
    WINDOW_WIDTH = w;
    WINDOW_HEIGHT = h;


    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Catch the Ball");
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(mouseClick);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutMainLoop();
    return 0;
}
