# DO1 Report

Установка и обновления системы Linux. Основы администрирования.

## Part 1. Установка ОС

- Разбил память на директории /boot , /var, /home и /
- Выполнил команду  
![part1](./img/part1.png)

## Part 2. Создание пользователя

- Выполнил команду для создания пользователя через adduser и добавил его в группу usermod -aG adm 
![part2_1](./img/part2_1.png)

- Вывод команды cat /etc/passwd
![part2_2](./img/part2_2.png)

## Part 3. Настройка сети ОС
- Для изменения hostname можно или изменить в редакторе файл /etc/hostname
`nano /etc/hostname`
или использовать команду 
`sudo hostnamectl set-hostname NAME
` после чего сделать `sudo reboot`

- Установка часового пояса
![part3_1](./img/part3_1.png)

- С помощью команды `ip link show` или `ifconfig -a` можно получить список сетевых интерфейсов.
Интерфейс lo используется для внутренних обращений к самому устройству, и он всегда активен даже в отсутствие сетевого подключения. То есть это localhost

- С помощью команд `ifconfig` или `ip a` можно найти ip в сети с строке `inet` интерфейса enp0s3
![part3_2](./img/part3_2.png)

- Внешний и внутринний ip шлюза
![part3_3](./img/part3_3.png)

- Для смены ip, gw и dns использовалась утилита netplan с конфигурационным файлом следующего содержания
![part3_4](./img/part3_4.png)

- Потом применил `sudo netplan generate` и перезагрузил систему
Теперь параметры изменились
![part3_5](./img/part3_5.png)

- Пингую адреса,настройки рабочие
![part3_6](./img/part3_6.png) 

## Part 4. Обновление ОС
- Командой `sudo apt update && sudo apt upgrade` обновляем OC
![part4](./img/part4.png) 

## Part 5. Sudo
- sudo (SuperUser DO) - это команда в системах Unix и Unix-подобных операционных системах, которая предоставляет временные привилегии суперпользователя (root) для выполнения задач, которые обычно требуют этих привилегий. Команда sudo может использоваться для выполнения команд с правами администратора.
sudo может использоваться только пользователями, внесенными в файл /etc/sudoers. Этот файл определяет, какие пользователи или группы пользователей могут использовать sudo и с какими привилегиями.
При использовании sudo, система обычно запрашивает пароль пользователя для подтверждения своего права на выполнение команды с привилегиями администратора.

- Командой `sudo visudo` вносим изменения в файл /etc/sudoers:   
  >`%sudo   ALL=(ALL:ALL) ALL`  
`seb   ALL=(ALL:ALL) ALL`
- Меняем hostname
![part5](./img/part5.png)

## Part 6. Настройка службы времени
![part6](./img/part6.png)

## Part 7. Редакторы 
- Редакторы vim,nano,joe

![part6](./img/vim1.png)  
![part6](./img/nano1.png)  
![part6](./img/joe1.png)  
Vim - :wq  
Joe - Control+K+X  
Nano - Ctrl+S Ctrl+X

- Без сохранения

![part6](./img/vim2.png)  
![part6](./img/nano2.png)  
![part6](./img/joe2.png)  
Vim - :q!  
Joe - Control+С y   
Nano - Ctrl+X N

- Поиск слова

![part6](./img/vim3.png)
![part6](./img/nano3.png)
![part6](./img/joe3.png)
Vim - /word  
Joe - Control+K+F   
Nano - Ctrl+W

- Замена слова

![part6](./img/vim4.png)
![part6](./img/nano4.png)
![part6](./img/joe4.png)
Vim - :%s/word/new_word/gc где % - по всем строкам, g - все слова в строке, c - c подтверждением  
Joe - Control+K+F R указать новое слово   
Nano - Ctrl+\

## Part 8. Установка и базовая настройка сервиса SSHD

- Делаем `sudo apt install`
- Потом `sudo systemctl enable ssh`
- На всякий случай делаем копию конфигурации по умолчанию ` sudo cp /etc/ssh/sshd_config /etc/ssh/sshd_config.factory-defaults`
- Меняем в конфиге в строчке Port число на 2022
- Командой `ps -e | grep sshd` получаем вывод процесса ssh на экран . Флаг `-e` означает every process.
- Вывод команды `netstat -tan`
![part8](./img/part8.png)
-n - numeric, показывает численные ip адреса, вместо попыток определить их названия ; -a позволяет просмотреть сведения о состоянии всех сокетов; -t - показать tcp-соединения
- Адрес 0.0.0.0 означает все адреса на всех интерфейсах системы, то есть ,указав таки нули , показывается, что поключение може быть выполнено на любой адрес

## Part 9. Установка и использование утилит top, htop
- Вывод команды top
![part9](./img/part9.png)
uptime: 1 min  
количество авторизованных пользователей: 1 user  
общую загрузку системы: load average 0.35 0.22 0.09  
общее количество процессов: Tasks 103  
загрузку cpu: 0  
загрузку памяти: последние две строки на скриншоте  
pid процесса занимающего больше всего памяти: 1 systemd  
pid процесса, занимающего больше всего процессорного времени: 1 systemd

- Вывод команды htop, отсортированый по разным параметрам
![part9](./img/part9_htop_pid.png)
![part9](./img/part9_htop_cpu.png)
![part9](./img/part9_htop_mem.png)
![part9](./img/part9_htop_time.png)
- Нажимаем Fn+F4 и фильтруем по sshd
![part9](./img/part9_sshd.png)
- Нажимаем Fn+F3 или `/` и ищем процесс syslog
![part9](./img/part9_syslog.png)
- В настройках по кнопке F2 добавляем новые параметры отображения
![part9](./img/part9_tch.png)


## Part 10.
- Название диска : VBOX HARDDISK  
Размер 10 GiB  
20971520 секторов  
![part10](./img/part10.png)
- Команда `free -h` показывает, что swap равен нулю, так как я не указал его при создании. 
![part10](./img/part10_swap.png)

## Part 11. df
### df
 - Total 3541496 KB
 - Used 2034292 KB
 - Available 1306864 KB
 - 61%
![part9](./img/part11_1.png)

### df -Th
 - -T - тип файловой системы
 - -h - человекочитаемый формат
 - Файловая система ext4
![part11](./img/part11_2.png)

## Part 12. du
- /home
![part11](./img/part12_du_home.png)
- /home -h
![part11](./img/part12_du_home_h.png)
- /var
![part11](./img/part12_du_var.png)
- /var -h
![part11](./img/part12_varh.png)
- /var/log
![part11](./img/part12_du_log.png)
- /var/log -h
![part11](./img/part12_log_h.png)
- /var/log/*
![part11](./img/part12_du_log_all.png)
- /var/log/* -h
![part11](./img/part12_du_log_all_h.png)

## Part 13. ncdu
- /home
![part11](./img/part13_home.png)
- /var
![part11](./img/part13_var.png)
- /var/log/
![part11](./img/part13_log.png)

## Part 14. Системные журналы, логи
- С помощью команды `cat /var/log/auth.log | grep login` находим дейстивия, связанные со входом в систему.
- Посленим логинился пользователь pottslav в 14:48:15 17  февраля.
![part14](./img/part14_login.png)
- Командой `sudo systemctl restart ssd` перезапускаем, а потом в логе `systemctl` находим сообщение
![part14](./img/part14_ssh.png)

## Part 15. CRON
- Список задач cron можно узнать с помощью команды `crontab -l`
![part14](./img/part15_cron.png)
- C помощью `journalctl` смотрим лог и видим записи о выполнении заданной команды
![part14](./img/part15_journar.png)
- Команда `crontab -r` очищает задачи  
![part14](./img/part15.png)
