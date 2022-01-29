#include "md-simul.h" // this has all functions declarations

int main(void)
{
  /* NOTAS PARA EL LECTOR
   * 1. Se debe compilar el programa utilizando 'g++ md-main.cpp md-simul.cpp integrator-leapfrog.cpp'.
   * 2. Los valores de DT y NSTEPS se deben editan en md-simul.h - hay una tabla allí para referencia.
   * 3. La implementación del cálculo de la conservación mecánica se encuentra en las definiciones de
   *    las funciones "initial_conditions" y "compute_force" en el archivo "integrator-leapfrog.cpp".
   * 4. Dentro del archivo .zip se pueden encontrar diferentes figuras (en escala log-log) que muestran
   *    la conservación de la energía en función del tiempo, para diferentes DT. También se encuentran
   *    dos figuras que muestra la misma relación para todos los DT al mismo tiempo.
   * 5. Se encontró que para los DT más grandes (1.0 , 0.5 y 0.1) la energía mecánica no se conserva como
   *    se espera, especialmente al final; sin embargo, para los DT más pequeños (0.05 y 0.01) sí se conserva,
   *    de mejor manera (no perfecto) - esto se puede evidenciar en las gráficas.
   * 
   * Para el cálculo de la energía mecánica se tuvo en cuenta tanto la energía potencial (U) como la
   * energía cinética (K) de la pelota. Para el caso de la primera, se calculó en cada punto su energía
   * potencial por posición [U = m*g*y] y por interacción con alguna de las paredes [U = (k*delta^2)/2];
   * para el caso de la segunda, se calculó en cada punto la energía cinética de acuerdo a la velocidad de
   * la pelota [K = (m*v^2)/2]. Finalmente se calculó la diferencia relativa entre la energía mecánica en
   * cada punto respecto a la inicial [DE = |E(t) - E(0)|/E(0)] y se imprimió en la octava columna del
   * output del programa; a partir de estos datos se graficó DE en función del tiempo para diferentes DT.
  */

  Particle ball;

  // start system
  initial_conditions(ball);
  compute_force(ball);
  start_integration(ball, DT);
  print(ball, 0.0);

  // evolve
  for(int istep = 1; istep <= NSTEPS; ++istep) { // Comienza en 0 y llega a 20 segundos
    time_integration(ball, DT);
    compute_force(ball);
    print(ball, istep*DT);
  }
  
  return 0;
}
