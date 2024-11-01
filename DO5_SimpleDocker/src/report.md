## Part1. Готовый докер
##### Возьми официальный докер-образ с **nginx** и выкачай его при помощи `docker pull`.
##### Проверь наличие докер-образа через `docker images`.
##### Запусти докер-образ через `docker run -d [image_id|repository]`.
##### Проверь, что образ запустился через `docker ps`.
##### Посмотри информацию о контейнере через `docker inspect [container_id|container_name]`.
![](./img/1.png)

Размер, адреса, порты


![](./img/2.png)
![](./img/3.png)
![](./img/4.png)

##### Останови докер образ через `docker stop [container_id|container_name]`.
##### Проверь, что образ остановился через `docker ps`.

![](./img/5.png)

##### Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.

![](./img/7.png)

##### Проверь, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**.

![](./img/6.png)

##### Перезапусти докер контейнер через `docker restart [container_id|container_name]`.
##### Проверь любым способом, что контейнер запустился.

![](./img/8.png)

## Part 2. Операции с контейнером
##### Прочитай конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*.

![](./img/9.png)

##### Создай на локальной машине файл *nginx.conf*.
##### Настрой в нем по пути */status* отдачу страницы статуса сервера **nginx**.
##### Скопируй созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`.
##### Перезапусти **nginx** внутри докер-образа через команду *exec*.
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.

![](./img/10.png)

##### Экспортируй контейнер в файл *container.tar* через команду *export*.
##### Останови контейнер.

![](./img/11.png)

##### Удали образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры.
##### Удали остановленный контейнер.

![](./img/12.png)

##### Импортируй контейнер обратно через команду *import*.
##### Запусти импортированный контейнер.
![](./img/13.png)
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.

![](./img/14.png)
