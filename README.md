# Общие вопросы
1) Например, char * var, char* var, char *var - какой вариант наиболее грамотный?

2) %3d, %4.234f - шо за фрукт? %.41f - 41 цифра после запятой?

# MPIsum2.c 
1) До 4 ядер наращивание кол-ва ядер уменьшает время выполнения, затем время увеличивается примерно пропорционально кол-ву ядер? Почему и что не так?

# Вопросы из методички Гергеля
1) double t1, t2, dt;
t1 = MPI_Wtime();
ѕ
t2 = MPI_Wtime();
dt = t2 – t1; - MPI_Wtime() отсчитывает время с некоторого прошлого момента. Здесь - вторая ф-я может не от первой время отсчитывать, а от произвольного момента, правильно я понимаю? Какой тогда смысл в такой конструкции?
