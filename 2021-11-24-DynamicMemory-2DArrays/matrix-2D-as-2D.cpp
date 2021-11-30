 #include <iostream>

 int main(void)
 {
     const int W = 4;
     const int H = 3;

   double array2d[H][W] = {{0.0}};
   for (int ii = 0; ii < H; ++ii) {
     for (int jj = 0; jj < W; ++jj) {
         array2d[ii][jj] = 1.0/(ii+jj+1);
     }
   }
   std::cout << array2d[1][1] << std::endl;
 }
