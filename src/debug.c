
#include "../includes/cube3d.h"

void	d(void)
{
	printf(BOLD GREEN "\n\n\t---------DEBUG-----------\n\n" RESET);
}


// *******************DEBUG FUNCTION RAYCASTING***************************
void debug_map_and_player(t_data *data)
{
    printf("\n=== MAP DEBUG INFO ===\n");
    printf("Map dimensions: height=%d\n", data->map_height);
    
    // Print the actual map
    printf("Map layout:\n");
    for (int i = 0; i < data->map_height; i++)
    {
        if (data->map[i] != NULL)
        {
            printf("Row %d: [%s] (length: %zu)\n", i, data->map[i], ft_strlen(data->map[i]));
        }
        else
        {
            printf("Row %d: NULL\n", i);
        }
    }
    
    printf("\nPlayer info:\n");
    printf("Player position: (%.2f, %.2f)\n", data->player->player_pos_x, data->player->player_pos_y);
    printf("Grid position: (%d, %d)\n", (int)data->player->player_pos_x, (int)data->player->player_pos_y);
    
    // Check what's at player position
    int px = (int)data->player->player_pos_x;
    int py = (int)data->player->player_pos_y;
    
    if (is_map_coordinates(px, py, data))
    {
        printf("Character at player position: '%c'\n", data->map[px][py]);
    }
    else
    {
        printf("ERROR: Player is outside map bounds!\n");
    }
    
    // Check surrounding area
    printf("\n3x3 area around player:\n");
    for (int i = px - 1; i <= px + 1; i++)
    {
        for (int j = py - 1; j <= py + 1; j++)
        {
            if (is_map_coordinates(i, j, data))
            {
                char c = data->map[i][j];
                if (i == px && j == py)
                    printf("[%c]", c);  // Player position in brackets
                else
                    printf(" %c ", c);
            }
            else
            {
                printf(" X ");  // Out of bounds
            }
        }
        printf("\n");
    }
    printf("=== END DEBUG ===\n\n");
}

void test_coordinate_system(t_data *data)
{
    printf("\n=== COORDINATE SYSTEM TEST ===\n");
    printf("Testing map[0][0]: ");
    if (data->map[0] && data->map[0][0])
        printf("'%c'\n", data->map[0][0]);
    else
        printf("NULL or invalid\n");
    
    printf("Testing map[1][1]: ");
    if (data->map_height > 1 && data->map[1] && ft_strlen(data->map[1]) > 1)
        printf("'%c'\n", data->map[1][1]);
    else
        printf("NULL or invalid\n");
        
    printf("Map access pattern: data->map[row][col] or data->map[y][x]\n");
    printf("Player coordinates: x=%.2f (col), y=%.2f (row)\n", 
           data->player->player_pos_x, data->player->player_pos_y);
    printf("=== END COORDINATE TEST ===\n\n");
}
// ***************************END******************************
