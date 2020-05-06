#define SETPOINT         8
#define WALL_DIST_L      15
#define WALL_DIST_F      15
#define WALL_DIST_R      15

#define FIRST_RUN        3
#define SECOND_RUN       4
#define WAIT             2

#define NOT_PRESS        1
#define PRESS            0

#define SLOW             0
#define FAST             1

#define VALORBLANCO1     400
#define VALORBLANCO2     400

#define PRESS            0
#define RELEASE          1
#define CONFIRMATION     1
#define LIBERATION       3

#define START            0
#define LEFT_OO          1
#define FRONT_OO         2
#define RIGHT_NOO        3
#define LEFT_NOO         4
#define FRONT_NOO        5
#define NO_OPTION        6
#define POST_TURN        10

#define LEFT             0
#define RIGHT            1

//CNYs
#define SENFLOOR1        A1
#define SENFLOOR2        A0

//SHARPS
#define SHARPR           A5 
#define SHARPL           A7 
#define SHARPF           A6 

#define BTN1             A4
#define BTN2             A3
#define BTN3             A2

#define LED1             13
#define LED2             4

#define PWMR             6
#define DIR_R1           12
#define DIR_R2           11

#define PWML             5
#define DIR_L1           10
#define DIR_L2           9

#define ENC_L            2
#define ENC_R            3

#define GEAR_NUM         ((float) 7 * 37 * 3.5 * 19 )
#define GEAR_DEN         ((float) 1.2 * 11 * 13 * 1 )
#define GEAR_RED         ( GEAR_NUM / GEAR_DEN )
#define TICKS_REV        ((int) GEAR_RED*3)

#define WHEEL_DIA        32.0
#define WHEEL_PER        (WHEEL_DIA * 3.14159265)   

#define SCALE_FACTOR     (1000.0 / TICKS_REV * 1000.0 * WHEEL_PER)

#define  DEGREE_90       59
#define  LEFT_TURN90     32.2
#define  RIGHT_TURN90    38
#define  TURN_180        64.4
#define  CELL            200
#define  PAUSE_TIME      20

#define LEFT_FREE        readSharp(SHARPL) >  WALL_DIST_L   
#define FRONT_FREE       readSharp(SHARPF) >  WALL_DIST_F   
#define RIGHT_FREE       readSharp(SHARPR) >  WALL_DIST_R   

void inicializar (void);
void setMotors (int, int);
void turnLeft(int);
void turnRight(int);
void moveForward(void);
void turnLeft90(int);
void turn180(int);
void turnRight90(int);
void moveCell(int);
void resetTicks(void);
float readSharp(int);
volatile long long encoderTicks[2] = {0, 0};
volatile float encoderDistance[2] = {0, 0};

int motor_dir[2];
float target_vel[2];
int ticks_before;
