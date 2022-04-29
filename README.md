# philo

## Общие условия задания:

- Один или больше философов сидят вокруг стола. Большая тарелка спагетти по центру стола.
- Философы попеременно едят, думают или спят. Пока они едят, они не думают и не спят, пока думают они не едят и не спят, когда спят они не думают и не едят.
- На столе лежат вилки, их столько же, сколько философов.
- Есть и накладывать одной вилкой неудобно, поэтому философ берет вилку в каждую руку.
- Когда философ закончил есть, он кладет вилки обратно и начинает спать. Когда просыпается, начинает думать. Симуляция останавливается, когда философ умирает от голода.
- Каждый философ должен есть и не должен голодать.
- Философы не разговаривают друг с другом.
- Философы не знают, скоро ли умрет другой философ.
- Философы должны избегать смерти.

## Общие правила:

- Глобальные переменные запрещены.
- Программа принимает следующие аргументы: `number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep`, [`number_of_times_each_philosopher_must_eat`].
    - number_of_philosophers - количество философов и также количество вилок,
    - time_to_die - (в миллисекундах) если философ не ел `time_to_die` с начала последнего приема пищи или начала симуляции, он умирает.
    - time_to_eat - (в миллисекундах) время нужное философу, чтобы поесть. В это время он должен держать две вилки.
    - time_to_sleep - (в миллисекундах) время нужное философу, чтобы поспать.
    - number_of_times_each_philosopher_must_eat - (опционально) если все философы поели `number_of_times_each_philosopher_must_eat` раз симуляция останавливается. Если не указано, симуляция останавливается, когда философ умирает.
- Каждый философ имеет номер от 1 до `number_of_philosophers`.
- Философ номер 1 сидит рядом с `number_of_philosophers`. Любой философ номер `N` сидит между `N - 1` и `N + 1`.

### Логирование

- Каждое изменение состояния философа должно быть оформлено следующим образом:
    - `timestamp_in_ms X has taken a fork`- философ X взял вилку,
    - `timestamp_in_ms X is eating` - начал есть,
    - `timestamp_in_ms X is sleeping` - начал спать,
    - `timestamp_in_ms X is thinking` - начал думать,
    - `timestamp_in_ms X died` - умер.
- Отображаемое сообщение о состоянии не следует путать с другим сообщением.
- Сообщение о смерти философа должно отображаться не более чем через 10 миллисекунд после фактической смерти философа.
- Философы должны избегать смерти.

## Основная часть

- Название программы: `philo`.
- Разрешенные файлы: `Makefile`, `*.h`, `*.c`, в директории `philo/`.
- Makefile: `NAME`, `all`, `clean`, `fclean`, `re`.
- Аргументы программы: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosopher_must_eat (опционально).
- Разрешенные функции: 
    - memset, printf, malloc, free, write,
    - usleep, gettimeofday, pthread_create,
    - pthread_detach, pthread_join, pthread_mutex_init,
    - pthread_mutex_destroy, pthread_mutex_lock,
    - pthread_mutex_unlock.
- Без использования `Libft`.
- Философы с потоками и мьютексами.
Дополнительные особенности:
- Каждый философ должен быть потоком.
- Между каждой парой философов есть одна развилка. Следовательно, если философов несколько, то у каждого философа есть вилка слева и вилка справа. Если есть только один философ, на столе должна быть только одна вилка.
- Чтобы философы не дублировали вилки, вы должны защитить состояние вилок мьютексом для каждого из них.


## Чек-лист для защиты

- [ ] Тестовые значения `1 800 200 200`: философ не должен есть и должен умереть.
- [ ] Тестовые значения `5 800 200 200`: никто не должен умереть.
- [ ] Тестовые значения `5 800 200 200 7`: никто не должен умирать, симуляция остановится, когда каждый философ поест минимум 7 раз.
- [ ] Тестовые значения `4 410 200 200`: никто не должен умереть.
- [ ] Тестовые значения `4 310 200 100`: философ умрет.

## Используемые функции

### `int usleep(useconds_t usec);`

Приостанавливает выполнение вызванного потока (как минимум) на `usec` микросекунд. Функция возвращает 0 в случае успеха. При ошибке `-1` и устанавливает нужное значение в errno.

### `int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);`

Функции `gettimeofday()` и `settimeofday()` могут получать и устанавливать время, а также часовой пояс. 
Аргумент `tv` является структурой `struct timeval` (определена в `<sys/time.h>`).

    struct timeval {
        time_t      tv_sec;     /* seconds */
        suseconds_t tv_usec;    /* microseconds */
    };

Аргумент `tz` - это `struct timezone`. Использование tz устарело, поэтому указывают NULL.

    struct timezone {
      int tz_minuteswest;     /* minutes west of Greenwich */
      int tz_dsttime;         /* type of DST correction */
    };

Функция возвращает 0 в случае успеха. При ошибке `-1` и устанавливает нужное значение в errno.

### `int pthread_create(*ptherad_t, const pthread_attr_t *attr, void* (*start_routine)(void*), void *arg);`

Функция `pthread_create()` запускает новый поток внутри потока. 
- Первый аргумент - это указатель на переменную типа pthread_t, в которую (при успехе) записывается id потока.
- Аргумент `pthread_attr_t` - атрибут потока (по умолчанию NULL).
- Аргумент `start_routin` - это функция, которая будет выполняться в новом потоке.
- `arg` - аргумент функции `start_routin`

### `int pthread_detach(pthread_t thread);`

Функция pthread_detach() используется для указания выполнении программы, что память для потока может быть освобождена после завершения этого потока. После успешного вызова этой функции нет необходимости возвращать поток с помощью `pthread_join()`.
В случае успеха возвращает 0 или номер ошибки, чтобы обозначит её.

### `int pthread_join(thread_t tid, void **status);`

Функция для ожидания завершения потока. Она блокирует вызывающий поток, пока **указанный** поток не завершится. Если status не равен NULL, он указывает на переменную, которая принимает значение статуса выхода завершенного потока при успешном завершении pthread_join().

### `int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);`

Для применения есть готовый макрос:

`pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;`

pthread_mutexattr_init() используется для инициализации объекта атрибутов взаимной блокировки.

**Взаимная блокировка** - это взаимоисключающая блокировка. Захватить такую блокировку может только одна нить. Взаимные блокировки применяются для предотвращения одновременного доступа к общим данным.

### `int pthread_mutex_destroy (mutex)`

Функция для освобождения всей области памяти, которая была выделена функцией pthread_mutex_init.

Пример:

    pthread_mutex_t mutex;
    ...
    for (i = 0; i < 10; i++) {
        
            /* создание взаимной блокировки */
            pthread_mutex_init(&mutex, NULL);
        
            /* применение взаимной блокировки */
        
            /* удаление взаимной блокировки */
            pthread_mutex_destroy(&mutex);
    }

### `int pthread_mutex_lock (pthread_mutex_t *mutex);`
### `int pthread_mutex_unlock (pthread_mutex_t *mutex);`

***Взаимная блокировка*** - это обычная блокировка, у которой есть два состояния: занята и свободна. После создания взаимная блокировка свободна. Функция `pthread_mutex_lock` захватывает взаимную блокировку на следующих условиях:

- Если взаимная блокировка свободна, функция ее захватывает.
- Если блокировка уже захвачена другой нитью, функция блокирует вызывающую нить до освобождения взаимной блокировки.
- Если взаимная блокировка уже захвачена вызывающей нитью, то возникнет тупик, либо функция вернет сообщение об ошибке, в зависимости от типа взаимной блокировки.

Функция `pthread_mutex_unlock` освобождает взаимную блокировку, если ее владельцем является вызывающая нить, соблюдая следующие условия:

- Если взаимная блокировка уже свободна, функция возвращает сообщение об ошибке.
- Если владельцем взаимной блокировки является вызывающая нить, функция освобождает блокировку.
- Если владельцем взаимной блокировки является другая нить, функция возвращает сообщение об ошибке или освобождает блокировку, в зависимости от типа взаимной блокировки. Освобождать блокировку не рекомендуется, так как блокировки, как правило, захватываются и освобождаются одной и той же нитью.

Пример:

        /* главная нить */
        pthread_mutex_t mutex;
        int     i;
        ...
        pthread_mutex_init(&mutex, NULL);    /* создание взаимной блокировки */
        for (i = 0; i < num_req; i++)        /* создание нитей в цикле */
                pthread_create(th + i, NULL, rtn, &mutex);
        ...                                  /* ожидание конца сеанса */
        pthread_mutex_destroy(&mutex);       /* удаление взаимной блокировки */
        ...

        /* нить, обрабатывающая запрос */
        ...                                  /* ожидание запроса */
        pthread_mutex_lock(&db_mutex);       /* блокировка базы данных */
        ...                                  /* обработка запроса */
        pthread_mutex_unlock(&db_mutex);     /* разблокирование базы данных */
        ...