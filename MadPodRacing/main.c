#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{

    // game loop
    while (1) {
        int x;
        int y;
        // x position of the next check point
        int next_checkpoint_x;
        // y position of the next check point
        int next_checkpoint_y;
        // distance to the next checkpoint
        int next_checkpoint_dist;
        // angle between your pod orientation and the direction of the next checkpoint
        int next_checkpoint_angle;
        scanf("%d%d%d%d%d%d", &x, &y, &next_checkpoint_x, &next_checkpoint_y, &next_checkpoint_dist, &next_checkpoint_angle);
        int opponent_x;
        int opponent_y;
        scanf("%d%d", &opponent_x, &opponent_y);
        int power=100;

        if(next_checkpoint_dist < 3500)
            power = 100;
        else if(next_checkpoint_dist < 2700)
            power = 100;
        else if(next_checkpoint_dist < 2000)
            power = 42;
        else if(next_checkpoint_dist < 1000)
            power = 0;
        else if(next_checkpoint_dist < 500)
            power = 21;
        if(next_checkpoint_angle > 85 && next_checkpoint_angle < 95)
            power = 0;
        printf("%d %d %d\n", next_checkpoint_x, next_checkpoint_y,power);
    }

    return 0;
}
