#ifndef TRAINER_DP_H
#define TRAINER_DP_H

void trainer_dp_1(int retry);
int dp_1_check(char *line);
void trainer_dp_1_launcher(void);

void trainer_dp_2(int retry);
int dp_2_check(char *line);
void trainer_dp_2_launcher(void);

void trainer_dp_3(int retry);
int dp_3_check(char *line);
void trainer_dp_3_launcher(void);

void trainer_dp_4(int retry);
int dp_4_check(char *line);
void trainer_dp_4_launcher(void);

void trainer_dp_5(int retry);
int dp_5_check(char *line);
void trainer_dp_5_launcher(void);

void trainer_dp_6(int retry);
int dp_6_check(char *line);
void trainer_dp_6_launcher(void);

//Takes in the inputs to registers r0 and r1 and a function to check each line
//manages the running of the swap level based on this.
void swapLevel(int r0Val, int r1Val ,int (*lineCheck) (char *line));

void trainer_dp_7(int retry);
int dp_7_check(char *line);
void trainer_dp_7_launcher(void);

void trainer_dp_8(int retry);
int dp_8_check(char *line);
void trainer_dp_8_launcher(void);

#endif
