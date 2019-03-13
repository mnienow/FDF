#include "fdf.h"

// void    putpxl(int x0, int x1, int y0, int y1)
// {
//     int deltax = abs(x1 - x0);
//     int deltay = abs(y1 - y0);
//      int error = 0;
//      int deltaerr = deltay;
//      int y = y0;
//      int diry = y1 - y0;
//      if (diry > 0)
//      {
//          diry = 1;
//      }
//      if (diry < 0)
//      {
//          diry = -1;
//      }
//     while (x0 < x1)
//     {
//         mlx_pixel_put(mlx, window, x, y, 0xFFFFFF);
//     }
// }

// int		main(void)
// {
//     void    *mlx;
//     void    *window;
//     int     x1 = 500;
//     int     y1 = 500;
//     int     x2 = 600;
//     int     y2 = 550;



//     int     arr[4] = {0, 0, 10, 0};
//     int     arr2[4] = {0, 0, 10, 0};
// 	mlx = mlx_init();
// 	window = mlx_new_window(mlx, WIDTH, HEIGHT, "my awesome fdf");
//   //  mlx_pixel_put(mlx, window, x, y, 0xFFFFFF);
// 	printf("123");
//     while (x1 < x2)
//     {
//             int deltax = abs(x2 - x1);
//     int deltay = abs(y2 - y1);
//     int     y = y1;
//     double  err;
//     double  deltaerr = deltay / deltax;
//     int     diry = y2 - y1;
//         if (diry > 0)
//             diry = 1;
//         if (diry < 0)
//             diry = -1;
//         mlx_pixel_put(mlx, window, x1, y, 0xFFFFFF);
//         err = err + deltaerr;
//         printf("|%f|\n", err);
//         if (err >= 0.5)
//         {
//             y = y + diry;
//             err = err - 1;
//         }
//         x1++;
//     }
//     // while (x1 <= 600)
//     // {   
//     //     int 
//     //     mlx_pixel_put(mlx, window, x1, y1, 0xFFFFFF);
//     //     err = err + ((y2 - y1) / (x2 - x1));
//     //     if (err > 0.5)
//     //     {
//     //         y1 += 1;
//     //         err -= 1;
//     //     }
//     //     printf("|%f|\n", err);
//     //     x1++;
//     // }
// 	mlx_loop(mlx);
// 	return (0);
// }

//---------------------------окружность--------------
int     main(void)
{
    void    *mlx;
    void    *window;
    int R = 250;
    int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;
    int x1 = 0;
    // int y1 = 0;

    mlx = mlx_init();
    window = mlx_new_window(mlx, WIDTH, HEIGHT, "my awesome fdf");
    while (y >= 0)
    {
        mlx_pixel_put(mlx, window, x1 + x, y, 0xFFFFFF);
        // mlx_pixel_put(mlx, window, x1 + x, y1 - y, 0xFFFFFF);
        // mlx_pixel_put(mlx, window, x1 - x, y1 + y, 0xFFFFFF);
        // mlx_pixel_put(mlx, window, x1 - x, y1 - y, 0xFFFFFF);
    //    drawpixel(x1 + x, Y1 + y)
    //    drawpixel(X1 + x, Y1 - y)
    //    drawpixel(X1 - x, Y1 + y)
    //    drawpixel(X1 - x, Y1 - y)
       error = 2 * (delta + y) - 1;
       if ((delta < 0) && (error <= 0))
       {
           delta = delta + 2 * ++x + 1;
           continue ;
       }
       if ((delta > 0) && (error > 0))
       {
           delta = delta - 2 * --y + 1;
           continue ;
       }
       delta += 2 * (++x - y--);
    printf("delta : %d  ", delta);
    printf("error : %d\n", error);
    }
    mlx_loop(mlx);
    return (0);
}
//------------------------------------------------------------
