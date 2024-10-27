## Part 1. Настройка gitlab-runner
Сначала нужно поднять виртуальную машину, а затем, подключив репозиторий gitlab, скачать оттуда gitlab-runner

```curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash```

```sudo apt-get install gitlab-runner```

C помощью команды `sudo gitlab-runner register` регистрируем ранней используя школьный токен. 

Конфиг раннера такой

![](./img/runnerconf.png)

## Part2. Сборка

В yaml файле описывается сборка, запуск Makefile для програм. Для успешной сборки нужно предварительно установить на машину с раннером зависимости в виде gcc и make

![](./img/build.png)

После этого запускается пайплайн с этой стадией

![](./img/buildsucc.png)

## Part3. Тест кодстайла

Описывается стадия проверки стиля

![](./img/style.png)

Успешно пройденный стиль

![](./img/stylesucc.png)

Заваленный стиль

![](./img/stylefail.png)

## Part4. Тесты

Описание тестов в yaml

![](./img/tests.png)

и их выполнение

![](./img/testsucc.png)

## Part 5. Деплой

Для того, чтобы по ssh перенести файлы, сначала надо соединить виртуальные машины, прописав для них адреса

![](./img/net.png)

Далее необходимо добавить пользователся gitlab-runner  в sudoers, чтобы он мог переносить файлы по ssh на другую машину командой scp

![](./img/sudo.png)

После запуска пайплайна на вторую машину перенесутся скомпилированные файлы

![](./img/delivery.png)

## Part 6. Бот

Используя бота getmyid_bot узанем свой id, чтобы доступ к нему был только у владельца.
Далее в botfather создлает бота

![](./img/botfather.png)

После запуска пайплайна получаем  уведомления

![](./img/bot.png)