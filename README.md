#Ещё вопросы

1) Допустим, массив int x[5]. x - указатель на начало массива

&x == x // ошибка компиляции, разные типы: int (*TYPE)[5] и int *TYPE - &x - на что он указывает? На все 5 элементов, что ли? Или опять на первый элемент, но проблема в несовпадении типов? 

Тогда это как понять &x[5]? &x[5] == &x ?

2) *(x + 2) // int &TYPE  - шо за тип &type ? 

x[2] // int &TYPE

#Все лабы

Сегм. ошибка - похоже, MPI-функции не знают когда остановить внутренний счётчик j, отсюда и обращение к тёмной области памяти. То есть надо как-то перейти к одномерным массивам?
#MPI_Bin_comparator.c

Выдаёт неправильные двоичные числа => ошибка в dec_to_bin? 

#MPI_Bin_comparator2.c

comparator.c: В функции ‘dec_to_bin’:

comparator.c:133: предупреждение: функция возвращает адрес локальной переменной

# Общие вопросы
1) Ну опять. В лабе с.4 пишут : int argc, char*** argv. Почему теперь 3 звезды? Почему там звёзды ближе к типу, а не к переменной ( Как Саня советовал )?

2) %50.25f - 50 знаков до запятой, 25 после, если число меньше по объёму знаков, пробелы заполняются нулями? 

3) Почему бы вместо одной программы для разного числа ядер не написать разные программы для каждого ядра в рамках одной задачи? Это ведь наиболее эффективный способ? Это ведь модель разделённых данных? Почему так не делают? Это не оптимально с точки зрения времени?

4) "-o", "-n" - шо за фрукт? Правильно называть его ключ компиляции?  
А я пишу "-np" заместо "-n". В чём разница - секрет буквы p?

5) Если бы не были созданы языки высокого уровня, не было бы компиляторов?

6) Полностью неупорядоченный массив - что это за суть?

7) O( (n-1)/2 ) ?= O( n/2 ) - верно ли, то есть константа здесь не учитывается? ( вопрос связан с сортировкой слиянием, конкретно с случаем, когда кол-во элементов - нечётно! )

8) O( O( n ) ) - чему равно?

9) с. 48 - Любой выч. системе, реализующей алгоритм, можно сопоставить строгую паралл. форму графа, а значит, каноническую форму. Но она отображает наилучший алгоритм? То есть по сути утверждается, что мы всегда для любой задачи можем найти наилучшее решение?

10) NP-полная задача - такая, для которой не доказано, что её можно решить за полиномиальное время?
Причём здесь полный перебор?

11) с. 52 сколько таких возможных abcdef? Не могу пока составить общий алгоритм подсчёта.

12) Как аварийно завершить int main()? exit 1? return !0 ?

# MPIsum2.c 
1) До 4 ядер наращивание кол-ва ядер уменьшает время выполнения, затем время увеличивается примерно пропорционально кол-ву ядер? Почему и что не так?

# Вопросы из методички Гергеля
1) double t1, t2, dt;
t1 = MPI_Wtime();
ѕ
t2 = MPI_Wtime();
dt = t2 – t1; - MPI_Wtime() отсчитывает время с некоторого прошлого момента. Здесь - вторая ф-я может не от первой время отсчитывать, а от произвольного момента, правильно я понимаю? Какой тогда смысл в такой конструкции?
